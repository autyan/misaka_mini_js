// app.h
// Application entry points and lifecycle for minijs.

#ifndef MINIJS_APP_H
#define MINIJS_APP_H

#include "common/mj_error.h"

// Run the application once using CLI arguments.
mj_error_t mj_app_run(int argc, char *const *argv);

// Signal hook to request a graceful exit (safe for SIGINT handler).
void mj_app_on_signal(int signum);

#endif
