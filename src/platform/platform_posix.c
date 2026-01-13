// platform_posix.c
// POSIX filesystem helpers.

#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

#include "platform/mj_platform.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

mj_error_t mj_platform_path_exists(const char *path, bool *out_exists)
{
    if (path == NULL || out_exists == NULL)
    {
        return MJ_INVALID_ARGUMENT;
    }

    struct stat info;
    *out_exists = (stat(path, &info) == 0);
    return MJ_OK;
}

mj_error_t mj_platform_is_directory(const char *path, bool *out_is_dir)
{
    if (path == NULL || out_is_dir == NULL)
    {
        return MJ_INVALID_ARGUMENT;
    }

    struct stat info;
    if (stat(path, &info) != 0)
    {
        return MJ_ERR_FILE_NOT_FOUND;
    }

    *out_is_dir = S_ISDIR(info.st_mode);
    return MJ_OK;
}

mj_error_t mj_platform_file_size(const char *path, unsigned long long *out_size)
{
    if (path == NULL || out_size == NULL)
    {
        return MJ_INVALID_ARGUMENT;
    }

    struct stat info;
    if (stat(path, &info) != 0)
    {
        return MJ_ERR_FILE_NOT_FOUND;
    }

    *out_size = (unsigned long long)info.st_size;
    return MJ_OK;
}

mj_error_t mj_platform_get_full_path(const char *path, char *out_path, size_t out_size)
{
    if (path == NULL || out_path == NULL || out_size == 0)
    {
        return MJ_INVALID_ARGUMENT;
    }

    if (realpath(path, out_path) == NULL)
    {
        return MJ_ERR_FILE_NOT_FOUND;
    }

    if (strlen(out_path) + 1 > out_size)
    {
        return MJ_ERR_PATH_TOO_LONG;
    }

    return MJ_OK;
}

mj_error_t mj_platform_join_path(const char *base, const char *name,
                                 char *out_path, size_t out_size)
{
    if (base == NULL || name == NULL || out_path == NULL || out_size == 0)
    {
        return MJ_INVALID_ARGUMENT;
    }

    const char *separator = "/";
    size_t base_len = strlen(base);
    bool needs_sep = (base_len > 0 && base[base_len - 1] != '/');

    int written = snprintf(out_path, out_size, "%s%s%s",
                           base, needs_sep ? separator : "", name);
    if (written < 0 || (size_t)written >= out_size)
    {
        return MJ_ERR_PATH_TOO_LONG;
    }

    return MJ_OK;
}
