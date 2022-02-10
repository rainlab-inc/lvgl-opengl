#include "gl.h"

#include <stdio.h>
#include <stdlib.h>

static GLuint shader_create(GLenum type, const char *src) {
    GLint success = 0;

    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        GLint info_log_len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_len);

        char *info_log = malloc(info_log_len+1);
        info_log[info_log_len] = '\0';

        glGetShaderInfoLog(shader, info_log_len, NULL, info_log);
        fprintf(stderr, "Failed to compile shader : %s", info_log);
        free(info_log);
    }

    return shader;
}


GLuint gl_shader_program_create(const char *vertex_src,
                                const char *fragment_src) {
    GLuint vertex = shader_create(GL_VERTEX_SHADER, vertex_src);
    GLuint fragment = shader_create(GL_FRAGMENT_SHADER, fragment_src);
    GLuint program = glCreateProgram();

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}



GLuint gl_texture_create(int width, int height, GLubyte *pixels) {
    GLuint tex_id;
    glGenTextures ( 1, &tex_id );
    glBindTexture ( GL_TEXTURE_2D, tex_id );

    glTexImage2D (
        GL_TEXTURE_2D,
        0,  //  Level
        GL_RGB,
        width,  //  Width
        height,  //  Height
        0,  //  Format
        GL_RGB,
        GL_UNSIGNED_BYTE,
        pixels
    );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    return tex_id;
}
