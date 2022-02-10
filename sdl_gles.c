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
#include "gl.h"

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

    GLuint program;
    GLint position_location;

    GLuint framebuffer_program;
    GLuint framebuffer;
    GLuint framebuffer_texture;
    GLint framebuffer_position_location;
    GLint framebuffer_uv_location;

}monitor_t;


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void window_create(monitor_t * m);
static void monitor_sdl_gles_clean_up(void);
static void sdl_gles_event_handler(lv_timer_t * t);
static void mouse_handler(SDL_Event *event);
static int tick_thread(void *data);

/**********************
 *  STATIC VARIABLES
 **********************/
static monitor_t monitor;
static volatile bool quit = false;

static bool left_button_down = false;
static int16_t last_x = 0;
static int16_t last_y = 0;

static char triangle_vertex_shader_str[] =
    "attribute vec3 a_position;   \n"
    "void main()                  \n"
    "{                            \n"
    "   gl_Position = vec4(a_position,1.0); \n"
    "}                            \n";

static char triangle_fragment_shader_str[] =
    "precision mediump float;                            \n"
    "void main()                                         \n"
    "{                                                   \n"
    "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);          \n"
    "}                                                   \n";

static char framebuffer_vertex_shader_str[] =
    "attribute vec2 a_position;   \n"
    "attribute vec2 a_texcoord;   \n"
    "varying vec2 v_texcoord;     \n"
    "void main()                  \n"
    "{                            \n"
    "   gl_Position = vec4(a_position.x, a_position.y, 0.0, 1.0); \n"
    "   v_texcoord = a_texcoord;  \n"
    "}                            \n";

static char framebuffer_fragment_shader_str[] =
    "precision mediump float;                            \n"
    "varying vec2 v_texcoord;                            \n"
    "uniform sampler2D s_texture;                        \n"
    "void main()                                         \n"
    "{                                                   \n"
    "  gl_FragColor = texture2D(s_texture, v_texcoord );\n"
    "}                                                   \n";


static GLfloat vertices[] = {
    0.0f, 0.0f, 0.0f, // left
    1.0f, 0.0f, 0.0f, // right
    1.0f, 1.0f, 0.0f  // top
};

static GLfloat framebuffer_vertices[] = {
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};

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
            mouse_handler(&event);
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        /* RENDER */
        glBindFramebuffer(GL_FRAMEBUFFER, monitor.framebuffer);
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(monitor.program);
        glVertexAttribPointer(monitor.position_location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), vertices);
        glEnableVertexAttribArray(monitor.position_location);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(monitor.framebuffer_program);
        glBindTexture(GL_TEXTURE_2D, monitor.framebuffer_texture);

        glVertexAttribPointer(monitor.framebuffer_position_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), framebuffer_vertices);
        glEnableVertexAttribArray(monitor.framebuffer_position_location);
        glVertexAttribPointer(monitor.framebuffer_uv_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), &framebuffer_vertices[2]);
        glEnableVertexAttribArray(monitor.framebuffer_uv_location);
        glDrawArrays(GL_TRIANGLES, 0, 6);


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

    m->program = gl_shader_program_create(triangle_vertex_shader_str, triangle_fragment_shader_str);

    glUseProgram(m->program);
    m->position_location = glGetAttribLocation(m->program, "a_position");



    m->framebuffer_program = gl_shader_program_create(framebuffer_vertex_shader_str, framebuffer_fragment_shader_str);

    glUseProgram(m->framebuffer_program);
    m->framebuffer_position_location = glGetAttribLocation(m->framebuffer_program, "a_position");
    m->framebuffer_uv_location = glGetAttribLocation(m->framebuffer_program, "a_texcoord");


    glGenFramebuffers(1, &m->framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m->framebuffer);

    glGenTextures(1, &m->framebuffer_texture);
    glBindTexture(GL_TEXTURE_2D, m->framebuffer_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SDL_HOR_RES, SDL_VER_RES, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m->framebuffer_texture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

static void mouse_handler(SDL_Event *event)
{
    switch(event->type) {
        case SDL_MOUSEBUTTONUP:
            if(event->button.button == SDL_BUTTON_LEFT)
                left_button_down = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event->button.button == SDL_BUTTON_LEFT) {
                left_button_down = true;
                last_x = event->motion.x / SDL_ZOOM;
                last_y = event->motion.y / SDL_ZOOM;
            }
            break;
        case SDL_MOUSEMOTION:
            last_x = event->motion.x / SDL_ZOOM;
            last_y = event->motion.y / SDL_ZOOM;
            break;

        case SDL_FINGERUP:
            left_button_down = false;
            last_x = LV_HOR_RES * event->tfinger.x / SDL_ZOOM;
            last_y = LV_VER_RES * event->tfinger.y / SDL_ZOOM;
            break;
        case SDL_FINGERDOWN:
            left_button_down = true;
            last_x = LV_HOR_RES * event->tfinger.x / SDL_ZOOM;
            last_y = LV_VER_RES * event->tfinger.y / SDL_ZOOM;
            break;
        case SDL_FINGERMOTION:
            last_x = LV_HOR_RES * event->tfinger.x / SDL_ZOOM;
            last_y = LV_VER_RES * event->tfinger.y / SDL_ZOOM;
            break;
    }
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
