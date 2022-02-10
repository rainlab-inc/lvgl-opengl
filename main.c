#include "sdl_gles.h"

#define _DEFAULT_SOURCE
#include <unistd.h>

#include <stdlib.h>



static void hal_init(void)
{
    sdl_gles_init();
}


int main()
{
    lv_init();
    hal_init();

    while (1) {
        lv_timer_handler();
        usleep(5 * 1000);
    }

    return EXIT_SUCCESS;
}
