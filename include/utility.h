// utility.h

#ifndef UTILITY_H
#define UTILITY_H

#include "mj_error.h"
#include "minijs.h"

void print_version();
void print_help();
mj_error_t parse_arguments(const int argc, char * const *argv, mj_execute_action_t *out_action);
mj_error_t parse_file(const char *filename, mj_executefile_t *file);

#endif