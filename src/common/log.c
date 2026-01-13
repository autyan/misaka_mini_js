/*
 * @Author: Alex
 * @Date: 2026-01-13 14:51:57
 * @LastEditors: Alex
 * @LastEditTime: 2026-01-13 14:52:31
 * @Description: file content
 */
// Log.c

#include "common/log.h"

#include <stdarg.h>
#include <stdio.h>

// Write a log line to stderr with level and source location.
void mj_log(const char *level, const char *file, int line, const char *fmt, ...)
{
    const char *safe_level = level ? level : MJ_LOG_LEVEL_INFO;
    const char *safe_file = file ? file : "unknown";

    fprintf(stderr, "[%s] %s:%d: ", safe_level, safe_file, line);

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
}
