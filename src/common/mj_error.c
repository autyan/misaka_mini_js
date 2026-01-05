#include "mj_error.h"
#include <stdio.h>

void print_error(const mj_error_t *err) {
    if (err == NULL) {
        printf("Unknown error occurred.\n");
        return;
    }

    switch (*err) {
        case MJ_OK:
            fprintf(stderr, "No error.\n");
            break;
        case MJ_ERR_UNKOWN:
            fprintf(stderr, "Unknown error occurred.\n");
            break;
        case MJ_INVALID_ARGUMENT:
            fprintf(stderr, "Invalid argument provided.\n");
            break;
        case MJ_ERR_FILE_NOT_FOUND:
            fprintf(stderr, "File not found error.\n");
            break;
        case MJ_ERR_FILE_READ:
            fprintf(stderr, "File read error.\n");
            break;
        default:
            fprintf(stderr, "Unrecognized error code: %d\n", *err);
            break;
    }
}