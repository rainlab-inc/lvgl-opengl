/**
 * @file sdl_gles.h
 *
 */

#ifndef SDL_GLES_H
#define SDL_GLES_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************
 *      INCLUDES
 *********************/
#if 0
#ifndef LV_DRV_NO_CONF
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_drv_conf.h"
#else
#include "../../lv_drv_conf.h"
#endif
#endif
#endif
#define SDL_HOR_RES 800
#define SDL_VER_RES 600
#define SDL_ZOOM 1
#define LV_USE_GPU_GLES 1

#if LV_USE_GPU_GLES

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void sdl_gles_init(void);

void sdl_gles_disp_draw_buf_init(lv_disp_draw_buf_t *draw_buf);

void sdl_gles_disp_drv_init(lv_disp_draw_buf_t *draw_buf);

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_GPU_GLES */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* SDL_GLES_H */