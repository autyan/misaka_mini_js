#include <stdio.h>
#include "utility.h"

int main(int argc, char *argv[]) {
    char **start = argv;
    char **end = start + argc;
    start += 1;
    if (start == end) {
        // No arguments provided, show help
        parse_arguments("-h");
        return 0;
    }
    while (start < end) {
        parse_arguments(*start);
        start++;
    }
    return 0;
}