#include "lv_drivers/sdl/sdl_gles.h"
#include "lvgl/examples/lv_examples.h"

#define _DEFAULT_SOURCE
#include <unistd.h>

#include <stdlib.h>



static void hal_init(void)
{
    sdl_gles_init();
    static lv_disp_draw_buf_t draw_buf;
    sdl_gles_disp_draw_buf_init(&draw_buf);
    static lv_disp_drv_t disp_drv;
    sdl_gles_disp_drv_init(&disp_drv, &draw_buf);
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
}


int main()
{
    lv_init();
    hal_init();

    lv_example_btn_1();

    while (1) {
        lv_timer_handler();
        usleep(5 * 1000);
    }

    return EXIT_SUCCESS;
}
