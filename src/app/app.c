// app.c
// Application-level flow orchestrating CLI parse and command execution.

#include "app/app.h"

#include <signal.h>
#include <stdbool.h>

#include "cli/cli.h"
#include "common/console.h"
#include "common/version.h"
#include "platform/mj_platform.h"
#include "runtime/runtime.h"

// Flag updated by signal handler to request a clean exit path.
static volatile sig_atomic_t g_app_exit_requested = 0;

// SIGINT handler that only flips an atomic flag.
void mj_app_on_signal(int signum)
{
    (void)signum;
    g_app_exit_requested = 1;
}

// Query whether a shutdown has been requested.
static bool mj_app_should_exit(void)
{
    return g_app_exit_requested != 0;
}

// Display version information to the CLI user.
static void mj_app_print_version(void)
{
    mj_console_println("MiniJS version: %s", MINIJS_VERSION);
}

// Display usage information for the CLI.
static void mj_app_print_help(void)
{
    mj_console_println("MiniJS - A minimal JavaScript interpreter");
    mj_console_println("Usage:");
    mj_console_println("  minijs run <file-or-directory>");
    mj_console_println("  minijs --help | -h");
    mj_console_println("  minijs --version | -v");
}

// Execute the run command against a file or directory target.
static mj_error_t mj_app_run_target(const char *path, mj_run_target_kind_t *out_kind)
{
    if (path == NULL || *path == '\0')
    {
        return MJ_INVALID_ARGUMENT;
    }

    if (mj_app_should_exit())
    {
        return MJ_OK;
    }

    bool is_dir = false;
    mj_error_t err = mj_platform_is_directory(path, &is_dir);
    if (err != MJ_OK)
    {
        return err;
    }

    if (is_dir)
    {
        if (out_kind != NULL)
        {
            *out_kind = MJ_RUN_TARGET_PROJECT;
        }
        char resolved_path[4096];
        if (mj_platform_get_full_path(path, resolved_path, sizeof(resolved_path)) == MJ_OK)
        {
            mj_console_println("Directory: %s", resolved_path);
        }
        else
        {
            mj_console_println("Directory: %s", path);
        }
        return mj_runtime_run_project(path);
    }

    if (out_kind != NULL)
    {
        *out_kind = MJ_RUN_TARGET_FILE;
    }
    mj_console_println("File: %s", path);
    unsigned long long file_size = 0;
    if (mj_platform_file_size(path, &file_size) == MJ_OK)
    {
        mj_console_println("Size: %llu bytes", file_size);
    }
    return mj_runtime_run_file(path);
}

// Application entry point used by main.
mj_error_t mj_app_run(int argc, char *const *argv)
{
    if (mj_app_should_exit())
    {
        return MJ_OK;
    }

    mj_cli_result_t cli;
    mj_cli_init(&cli);

    mj_error_t err = mj_cli_parse(argc, argv, &cli);
    if (err != MJ_OK)
    {
        print_error(&err);
        mj_app_print_help();
        mj_cli_free(&cli);
        return err;
    }

    if (cli.action == MJ_CLI_ACTION_PRINT_HELP)
    {
        mj_app_print_help();
        mj_cli_free(&cli);
        return MJ_OK;
    }

    if (cli.action == MJ_CLI_ACTION_PRINT_VERSION)
    {
        mj_app_print_version();
        mj_cli_free(&cli);
        return MJ_OK;
    }

    if (cli.command == MJ_CLI_COMMAND_RUN)
    {
        mj_run_target_kind_t kind = MJ_RUN_TARGET_UNKNOWN;
        err = mj_app_run_target(cli.target.path, &kind);
        cli.target.kind = kind;
        if (err != MJ_OK)
        {
            print_error(&err);
        }
        mj_cli_free(&cli);
        return err;
    }

    if (cli.command == MJ_CLI_COMMAND_UNKNOWN)
    {
        mj_console_errorln("Unknown command: %s", cli.raw_command ? cli.raw_command : "null");
        mj_app_print_help();
        mj_cli_free(&cli);
        return MJ_ERR_CLI_UNKNOWN_COMMAND;
    }

    mj_app_print_help();
    mj_cli_free(&cli);
    return MJ_OK;
}
