// main.c
// Process entry point wiring CLI to the application flow.

#include <signal.h>

#include "app/app.h"

int main(int argc, char *argv[])
{
    signal(SIGINT, mj_app_on_signal);

    mj_error_t err = mj_app_run(argc, argv);
    return err == MJ_OK ? 0 : 1;
}
