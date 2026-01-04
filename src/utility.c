#include <string.h>
#include <stdio.h>
#include "minijs.h"

void print_help();

void parse_arguments(char *arg) {
    if (strcmp(arg, "-v") == 0 || strcmp(arg, "--version") == 0) {
        // Handle version argument
        printf("MiniJS version: %s\n", minijs_version);
        return;
    }

    if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
        // Handle help argument
        print_help();
        return;
    }

    print_help();

    return;
}

void print_help() {
    printf("MiniJS - A minimal JavaScript interpreter\n");
    printf("Usage: minijs [options]\n");
    printf("Options:\n");
    printf("  -v, --version     Show version information\n");
    printf("  -h, --help        Show this help message\n");
}