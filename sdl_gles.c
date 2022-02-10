/**
 * @file sdl_gles.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "sdl_gles.h"

#if LV_USE_GPU_GLES == 0
# error "LV_USE_GPU_GLES must be enabled"
#endif

#include <glad/glad.h>
/* TODO: SDL_INCLUDE_PATH */
#include <SDL2/SDL.h>

#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    SDL_Window *window;
    SDL_GLContext *context;
}monitor_t;


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void window_create(monitor_t * m);
static void monitor_sdl_gles_clean_up(void);
static void sdl_gles_event_handler(lv_timer_t * t);
static int tick_thread(void *data);

/**********************
 *  STATIC VARIABLES
 **********************/
static monitor_t monitor;
static volatile bool quit = false;


/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void sdl_gles_init(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window_create(&monitor);

    SDL_CreateThread(tick_thread, "tick", NULL);

    lv_timer_create(sdl_gles_event_handler, 10, NULL);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void sdl_gles_event_handler(lv_timer_t * t)
{
    (void)t;

    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(monitor.window);
    }

    if (quit) {
        monitor_sdl_gles_clean_up();
        exit(EXIT_SUCCESS);
    }

}

static void window_create(monitor_t *m)
{
    m->window = SDL_CreateWindow("lvgl-opengl",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_HOR_RES * SDL_ZOOM, SDL_VER_RES * SDL_ZOOM,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    m->context = SDL_GL_CreateContext(m->window);

    gladLoadGLES2Loader((GLADloadproc) SDL_GL_GetProcAddress);

    printf( "GL version : %s\n", glGetString(GL_VERSION));
    printf( "GL vendor : %s\n", glGetString(GL_VENDOR));
    printf( "GL renderer : %s\n", glGetString(GL_RENDERER));
    fflush(stdout);
}

static void monitor_sdl_gles_clean_up(void)
{
    SDL_DestroyWindow(monitor.window);
}

static int tick_thread(void *data)
{
    (void)data;

    while(!quit) {
        SDL_Delay(5);
        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }

    return 0;
}
