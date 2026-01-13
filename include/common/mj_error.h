// mj_error.h

#ifndef MJ_ERROR_H
#define MJ_ERROR_H

typedef enum {
    MJ_OK = 0,

    /* general errors */
    MJ_ERR_UNKOWN = 1000,
    MJ_INVALID_ARGUMENT = 1001,

    /* cli errors */
    MJ_ERR_CLI_UNKNOWN_COMMAND = 1100,
    MJ_ERR_CLI_MISSING_ARGUMENT = 1101,
    MJ_ERR_CLI_TOO_MANY_ARGUMENTS = 1102,
    MJ_ERR_CLI_CONFLICT = 1103,

    /* io errors */
    MJ_ERR_FILE_NOT_FOUND = 2000,
    MJ_ERR_FILE_READ = 2001,
    MJ_ERR_PATH_TOO_LONG = 2002,

    /* runtime errors */
    MJ_ERR_UNSUPPORTED_ENCODING = 3000,
    MJ_ERR_PROJECT_ENTRY_NOT_FOUND = 3001,
} mj_error_t;

void print_error(const mj_error_t * err);

#endif
