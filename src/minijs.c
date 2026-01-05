#include <stdlib.h>
#include "minijs.h"

void init_mj_executefile(mj_executefile_t *file, size_t filename_size, size_t content_size)
{
    if (file == NULL)
    {
        return;
    }
    file->filename = malloc(filename_size);
    file->content = malloc(content_size);
    file->content_length = 0;
    file->has_bom = false;
}

void free_mj_executefile(mj_executefile_t *file)
{
    if (file == NULL)
    {
        return;
    }
    free(file->filename);
    free(file->content);
}