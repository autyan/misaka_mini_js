// console.h
// Minimal stdout/stderr wrapper for user-facing CLI messages.

#ifndef MINIJS_CONSOLE_H
#define MINIJS_CONSOLE_H

// Print a formatted message to stdout.
void mj_console_print(const char *fmt, ...);

// Print a formatted message to stdout with a newline.
void mj_console_println(const char *fmt, ...);

// Print a formatted message to stderr with a newline.
void mj_console_errorln(const char *fmt, ...);

#endif
