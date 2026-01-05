#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "minijs.h"
#include "mj_error.h"
#include "utility.h"

mj_error_t parse_arguments(const int argc, char *const *argv, mj_execute_action_t *out_action)
{
    if (out_action == NULL)
    {
        return MJ_INVALID_ARGUMENT;
    }

    char **start = (char **)argv;
    char **end = start + argc;

    // escape first element
    start += 1;

    // no arguments, print help
    if (start == end)
    {
        print_help();

        return MJ_OK;
    }

    out_action->action = MJ_ACTION_NONE;
    out_action->filename = NULL;

    while (start < end)
    {
        if (strcmp(*start, "-v") == 0 || strcmp(*start, "--version") == 0)
        {
            out_action->action = MJ_ACTION_PRINT_VERSION;
            return MJ_OK;
        }
        else if (strcmp(*start, "-h") == 0 || strcmp(*start, "--help") == 0)
        {
            out_action->action = MJ_ACTION_PRINT_HELP;
            return MJ_OK;
        }
        else
        {
            // assume it's a filename
            out_action->action = MJ_ACTION_EXECUTE_FILE;
            out_action->filename = *start;
            return MJ_OK;
        }
        start += 1;
    }

    return MJ_OK;
}

mj_error_t parse_file(const char *filename, mj_executefile_t *out_file)
{
    if (out_file == NULL)
    {
        return MJ_INVALID_ARGUMENT;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return MJ_ERR_FILE_NOT_FOUND;
    }
    
    size_t file_size = 0;
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    init_mj_executefile(out_file, strlen(filename) + 1, file_size + 1);
    fseek(file, 0, SEEK_SET);
    size_t read_size = fread(out_file->content, 1, file_size, file);
    if (read_size != file_size)
    {
        free_mj_executefile(out_file);
        fclose(file);
        return MJ_ERR_FILE_READ;
    }
    fclose(file);

    strcpy(out_file->filename,filename);
    out_file->content_length = file_size;
    out_file->has_bom = false; // BOM detection can be added here
    return MJ_OK;
}

void print_version()
{
    printf("MiniJS version: %s\n", MINIJS_VERSION);
}

void print_help()
{
    printf("MiniJS - A minimal JavaScript interpreter\n");
    printf("Usage: minijs [options]\n");
    printf("Options:\n");
    printf("  -v, --version     Show version information\n");
    printf("  -h, --help        Show this help message\n");
    printf(" filename           Parse and execute a js file\n");
}