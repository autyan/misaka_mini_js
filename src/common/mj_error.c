// mj_error.c
// Error message formatting for CLI and runtime errors.

#include "common/mj_error.h"

#include "common/console.h"
#include <stddef.h>

void print_error(const mj_error_t *err) {
    if (err == NULL) {
        mj_console_errorln("Unknown error occurred.");
        return;
    }

    switch (*err) {
        case MJ_OK:
            mj_console_errorln("No error.");
            break;
        case MJ_ERR_UNKOWN:
            mj_console_errorln("Unknown error occurred.");
            break;
        case MJ_INVALID_ARGUMENT:
            mj_console_errorln("Invalid argument provided.");
            break;
        case MJ_ERR_CLI_UNKNOWN_COMMAND:
            mj_console_errorln("Unknown command.");
            break;
        case MJ_ERR_CLI_MISSING_ARGUMENT:
            mj_console_errorln("Missing required argument.");
            break;
        case MJ_ERR_CLI_TOO_MANY_ARGUMENTS:
            mj_console_errorln("Too many arguments provided.");
            break;
        case MJ_ERR_CLI_CONFLICT:
            mj_console_errorln("Conflicting arguments provided.");
            break;
        case MJ_ERR_FILE_NOT_FOUND:
            mj_console_errorln("File not found error.");
            break;
        case MJ_ERR_FILE_READ:
            mj_console_errorln("File read error.");
            break;
        case MJ_ERR_PATH_TOO_LONG:
            mj_console_errorln("Path too long.");
            break;
        case MJ_ERR_UNSUPPORTED_ENCODING:
            mj_console_errorln("Unsupported source encoding.");
            break;
        case MJ_ERR_PROJECT_ENTRY_NOT_FOUND:
            mj_console_errorln("Project entry not found.");
            break;
        default:
            mj_console_errorln("Unrecognized error code: %d", *err);
            break;
    }
}
