// cli.c
// CLI parsing implementation with strict single-action semantics.

#include "cli/cli.h"

#include <string.h>

// Check whether the argument is a help flag.
static bool mj_cli_is_help(const char *arg)
{
    return arg != NULL && (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0);
}

// Check whether the argument is a version flag.
static bool mj_cli_is_version(const char *arg)
{
    return arg != NULL && (strcmp(arg, "-v") == 0 || strcmp(arg, "--version") == 0);
}

// Initialize the CLI result for predictable parsing behavior.
void mj_cli_init(mj_cli_result_t *out_result)
{
    if (out_result == NULL)
    {
        return;
    }

    out_result->command = MJ_CLI_COMMAND_NONE;
    out_result->action = MJ_CLI_ACTION_NONE;
    out_result->options.reserved = false;
    out_result->target.kind = MJ_RUN_TARGET_UNKNOWN;
    out_result->target.path = NULL;
    out_result->raw_command = NULL;
}

// Free any heap allocations owned by the result (none today).
void mj_cli_free(mj_cli_result_t *result)
{
    (void)result;
}

// Enforce strict single-action semantics when only a flag is allowed.
static mj_error_t mj_cli_error_if_extra_args(int argc)
{
    if (argc > 2)
    {
        return MJ_ERR_CLI_CONFLICT;
    }
    return MJ_OK;
}

// Parse argv into a normalized CLI result.
mj_error_t mj_cli_parse(int argc, char *const *argv, mj_cli_result_t *out_result)
{
    if (argv == NULL || out_result == NULL || argc < 1)
    {
        return MJ_INVALID_ARGUMENT;
    }

    mj_cli_init(out_result);

    if (argc == 1)
    {
        out_result->action = MJ_CLI_ACTION_PRINT_HELP;
        return MJ_OK;
    }

    const char *arg1 = argv[1];

    if (mj_cli_is_help(arg1))
    {
        mj_error_t err = mj_cli_error_if_extra_args(argc);
        if (err != MJ_OK)
        {
            return err;
        }
        out_result->action = MJ_CLI_ACTION_PRINT_HELP;
        return MJ_OK;
    }

    if (mj_cli_is_version(arg1))
    {
        mj_error_t err = mj_cli_error_if_extra_args(argc);
        if (err != MJ_OK)
        {
            return err;
        }
        out_result->action = MJ_CLI_ACTION_PRINT_VERSION;
        return MJ_OK;
    }

    out_result->raw_command = arg1;

    if (strcmp(arg1, "run") == 0)
    {
        out_result->command = MJ_CLI_COMMAND_RUN;
        if (argc < 3)
        {
            return MJ_ERR_CLI_MISSING_ARGUMENT;
        }
        if (argc > 3)
        {
            return MJ_ERR_CLI_TOO_MANY_ARGUMENTS;
        }
        out_result->target.path = argv[2];
        return MJ_OK;
    }

    out_result->command = MJ_CLI_COMMAND_UNKNOWN;
    return MJ_ERR_CLI_UNKNOWN_COMMAND;
}
