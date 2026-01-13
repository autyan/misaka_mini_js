// runtime.h
// Placeholder runtime interface for executing scripts and event loops.

#ifndef MINIJS_RUNTIME_H
#define MINIJS_RUNTIME_H

#include "common/mj_error.h"

// Execute a single script file.
mj_error_t mj_runtime_run_file(const char *target_path);

// Execute a project directory.
mj_error_t mj_runtime_run_project(const char *target_path);

#endif
