#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "lvgl/lvgl.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static SDL_Window *window;
static SDL_GLContext context;
static bool quit = false;



#define SCR_WIDTH 800
#define SCR_HEIGHT 600


static void init_gl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to init SDL.");
        exit(EXIT_FAILURE);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);




    window = SDL_CreateWindow("lvgl-opengl",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);



    if (window == NULL) {
        fprintf(stderr, "Failed to create a SDL window.\n");
        exit(EXIT_FAILURE);
    }

    context = SDL_GL_CreateContext(window);

    if (context == NULL) {
        fprintf(stderr, "Failed to create a GL context.\n");
        exit(EXIT_FAILURE);
    }


    if (!gladLoadGLES2Loader((GLADloadproc) SDL_GL_GetProcAddress)) {
        fprintf(stderr, "Failed to init GLAD.\n");
        exit(EXIT_FAILURE);
    }

    printf( "GL version : %s\n", glGetString(GL_VERSION));
    printf( "GL vendor : %s\n", glGetString(GL_VENDOR));
    printf( "GL renderer : %s\n", glGetString(GL_RENDERER));
    fflush(stdout);

}

static void init_lvgl() {
    lv_init();
    init_tmp_driver();
   // lv_obj_t * btn = lv_btn_create(lv_scr_act());
#if 0
    lv_obj_set_pos(btn, 10, 10);
    lv_obj_set_size(btn, 120, 50);
#endif
}

static void main_loop() {
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }
}

static void destroy() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}



int main()
{
    init_gl();
    init_lvgl();
    main_loop();
    destroy();

    return EXIT_SUCCESS;
}
