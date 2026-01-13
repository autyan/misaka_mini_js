// runtime.c
// Placeholder runtime implementation. No execution yet.

#include "runtime/runtime.h"

#include <stdbool.h>

#include "common/console.h"
#include "common/utility.h"
#include "platform/mj_platform.h"

// Execute a single source file by opening a stream and validating encoding.
mj_error_t mj_runtime_run_file(const char *target_path)
{
    if (target_path == NULL || *target_path == '\0')
    {
        return MJ_INVALID_ARGUMENT;
    }

    mj_stream_t stream = {0};
    mj_stream_encoding_t encoding = MJ_STREAM_ENCODING_UNKNOWN;
    bool has_bom = false;

    mj_error_t err = open_stream_with_encoding(target_path, &stream, &encoding, &has_bom);
    if (err != MJ_OK)
    {
        return err;
    }

    if (encoding != MJ_STREAM_ENCODING_UTF8)
    {
        mj_stream_close(&stream);
        return MJ_ERR_UNSUPPORTED_ENCODING;
    }

    mj_console_println("Encoding: UTF-8%s", has_bom ? " (BOM)" : "");
    mj_stream_close(&stream);
    return MJ_OK;
}

static mj_error_t mj_runtime_find_project_entry(const char *project_path, char *out_path, size_t out_size)
{
    if (project_path == NULL || out_path == NULL || out_size == 0)
    {
        return MJ_INVALID_ARGUMENT;
    }

    const char *candidates[] = {"main.js", "index.js"};
    for (size_t i = 0; i < sizeof(candidates) / sizeof(candidates[0]); ++i)
    {
        mj_error_t err = mj_platform_join_path(project_path, candidates[i], out_path, out_size);
        if (err != MJ_OK)
        {
            return err;
        }

        bool exists = false;
        err = mj_platform_path_exists(out_path, &exists);
        if (err != MJ_OK)
        {
            return err;
        }
        if (exists)
        {
            return MJ_OK;
        }
    }

    return MJ_ERR_PROJECT_ENTRY_NOT_FOUND;
}

// Execute a project directory by resolving an entry file and running it.
mj_error_t mj_runtime_run_project(const char *target_path)
{
    if (target_path == NULL || *target_path == '\0')
    {
        return MJ_INVALID_ARGUMENT;
    }

    char entry_path[4096];
    mj_error_t err = mj_runtime_find_project_entry(target_path, entry_path, sizeof(entry_path));
    if (err != MJ_OK)
    {
        return err;
    }

    mj_console_println("Project entry: %s", entry_path);
    return mj_runtime_run_file(entry_path);
}
