#include "lv_drivers/glfw/glfw_gles.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"

#define _DEFAULT_SOURCE
#include <unistd.h>

#include <stdlib.h>



static void hal_init(void)
{
    glfw_gles_init();
    static lv_disp_draw_buf_t draw_buf;
    glfw_gles_disp_draw_buf_init(&draw_buf);
    static lv_disp_drv_t disp_drv;
    glfw_gles_disp_drv_init(&disp_drv, &draw_buf);
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

    lv_theme_t * th = lv_theme_default_init(disp, lv_palette_main(LV_PALETTE_BLUE),
                                            lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);
    lv_disp_set_theme(disp, th);

    lv_group_t * g = lv_group_create();
    lv_group_set_default(g);
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1);
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;
    indev_drv_1.read_cb = glfw_gles_mouse_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);
#if 0
    static lv_indev_drv_t indev_drv_2;
    lv_indev_drv_init(&indev_drv_2); /*Basic initialization*/
    indev_drv_2.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_2.read_cb = sdl_gles_keyboard_read;
    lv_indev_t *kb_indev = lv_indev_drv_register(&indev_drv_2);
    lv_indev_set_group(kb_indev, g);
#endif 
}


int main()
{
    lv_init();
    hal_init();


    lv_demo_widgets();


    while (1) {
        lv_timer_handler();
        usleep(5 * 1000);
    }

    return EXIT_SUCCESS;
}
