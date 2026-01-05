#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "mj_error.h"

int main(int argc, char *argv[]) {

    mj_execute_action_t execute_action;
    mj_error_t _err = parse_arguments(argc, argv, &execute_action);

    if (_err != MJ_OK) {
        print_error(&_err);
        return 1;
    }

    mj_executefile_t *file = NULL;

    switch (execute_action.action) {
        case MJ_ACTION_PRINT_VERSION:
            print_version();
            break;
        case MJ_ACTION_PRINT_HELP:
            print_help();
            break;
        case MJ_ACTION_EXECUTE_FILE:
            file = malloc(sizeof(mj_executefile_t));
            if (file == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                return 1;
            }

            _err = parse_file(execute_action.filename, file);

            if(_err != MJ_OK) {
                print_error(&_err);
                free_mj_executefile(file);
                free(file);
                return 1;
            }
            printf("Executing file: %s\n", file->filename);
            printf("Has BOM: %s\n", file->has_bom ? "Yes" : "No");
            printf("File Size: %zu bytes\n", file->content_length);
            printf("File content :\n%s\n", file->content);
            free_mj_executefile(file);
            free(file);
            break;
        default:
            print_help();
            break;
    }

    return 0;
}
