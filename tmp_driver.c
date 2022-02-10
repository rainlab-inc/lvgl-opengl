#include "lvgl/lvgl.h"
#include "common.h"


#if 0
void my_disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
{
    int32_t x, y;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
           // color_p++;
        }
    }

    lv_disp_flush_ready(disp);         /* Indicate you are ready with the flushing*/
}
#endif



void init_tmp_driver() {
#if 0
    static lv_disp_draw_buf_t draw_buf;

    lv_disp_draw_buf_init(&draw_buf, buf1, buf2,  DISP_HOR_RES * DISP_VER_RES);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = DISP_HOR_RES;
    disp_drv.ver_res = DISP_VER_RES;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

   // lv_disp_t * disp = lv_disp_drv_register(&disp_drv);
#endif
}
