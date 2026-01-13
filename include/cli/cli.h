// cli.h
// CLI parsing contracts for the minijs executable.

#ifndef MINIJS_CLI_H
#define MINIJS_CLI_H

#include <stdbool.h>

#include "common/mj_error.h"

// High-level command requested by the user.
typedef enum {
    MJ_CLI_COMMAND_NONE = 0,
    MJ_CLI_COMMAND_RUN,
    MJ_CLI_COMMAND_UNKNOWN
} mj_cli_command_t;

// Side-effect actions that do not require normal command execution.
typedef enum {
    MJ_CLI_ACTION_NONE = 0,
    MJ_CLI_ACTION_PRINT_HELP,
    MJ_CLI_ACTION_PRINT_VERSION
} mj_cli_action_t;

// Placeholder for future options. Kept as a distinct struct for lifecycle clarity.
typedef struct {
    bool reserved;
} mj_cli_options_t;

// Target selection for the run command.
typedef enum {
    MJ_RUN_TARGET_UNKNOWN = 0,
    MJ_RUN_TARGET_FILE,
    MJ_RUN_TARGET_PROJECT
} mj_run_target_kind_t;

// High-level run target derived from CLI arguments.
typedef struct {
    mj_run_target_kind_t kind;
    const char *path;
} mj_run_target_t;

// Result of parsing CLI arguments. Fields reference argv memory.
typedef struct {
    mj_cli_command_t command;
    mj_cli_action_t action;
    mj_cli_options_t options;
    // Run target derived from CLI input.
    mj_run_target_t target;
    // Original command string for error reporting.
    const char *raw_command;
} mj_cli_result_t;

// Initialize a CLI result object with safe defaults.
void mj_cli_init(mj_cli_result_t *out_result);

// Release resources owned by the CLI result (none today, but kept for future growth).
void mj_cli_free(mj_cli_result_t *result);

// Parse CLI arguments with strict "single action" semantics.
mj_error_t mj_cli_parse(int argc, char *const *argv, mj_cli_result_t *out_result);

#endif
