// console.c
// Minimal stdout/stderr helpers for user-facing CLI messages.

#include "common/console.h"

#include <stdarg.h>
#include <stdio.h>

// Write a formatted message to stdout without forcing a newline.
void mj_console_print(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
}

// Write a formatted message to stdout with a newline.
void mj_console_println(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);

    fputc('\n', stdout);
}

// Write a formatted message to stderr with a newline.
void mj_console_errorln(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
}
