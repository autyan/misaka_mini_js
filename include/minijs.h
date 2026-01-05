//minijs.h

#ifndef MINIJS_H
#define MINIJS_H

#include <stdbool.h>
#include <stddef.h>

#define MINIJS_VERSION "0.1.0"

typedef enum {
    MJ_ACTION_NONE = 0,
    MJ_ACTION_PRINT_VERSION,
    MJ_ACTION_PRINT_HELP,
    MJ_ACTION_EXECUTE_FILE
} mj_action_t;

typedef struct {

    mj_action_t action;

    char *filename;

} mj_execute_action_t;

typedef struct {
    char *filename;
    char *content;
    size_t content_length;
    bool has_bom;
} mj_executefile_t;

void init_mj_executefile(mj_executefile_t *file, size_t filename_size, size_t content_size);
void free_mj_executefile(mj_executefile_t *file);

#endif