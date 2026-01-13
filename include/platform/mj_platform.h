// mj_platform.h
// Cross-platform filesystem helpers used by CLI/runtime layers.

#ifndef MINIJS_PLATFORM_H
#define MINIJS_PLATFORM_H

#include <stdbool.h>
#include <stddef.h>

#include "common/mj_error.h"

// Check whether a path exists on disk.
mj_error_t mj_platform_path_exists(const char *path, bool *out_exists);

// Check whether a path is a directory.
mj_error_t mj_platform_is_directory(const char *path, bool *out_is_dir);

// Get a file size in bytes.
mj_error_t mj_platform_file_size(const char *path, unsigned long long *out_size);

// Resolve a full absolute path if possible.
mj_error_t mj_platform_get_full_path(const char *path, char *out_path, size_t out_size);

// Join two path segments into a buffer.
mj_error_t mj_platform_join_path(const char *base, const char *name,
                                 char *out_path, size_t out_size);

#endif
