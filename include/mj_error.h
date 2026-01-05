// mj_error.h

#ifndef MJ_ERROR_H
#define MJ_ERROR_H

typedef enum {
    MJ_OK = 0,

    /* general errors*/
    MJ_ERR_UNKOWN = 1000,
    MJ_INVALID_ARGUMENT = 1001,

    /* io errors */
    MJ_ERR_FILE_NOT_FOUND = 2000,
    MJ_ERR_FILE_READ = 2001,
} mj_error_t;

void print_error(const mj_error_t * err);

#endif