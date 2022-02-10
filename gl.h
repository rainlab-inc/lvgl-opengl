#ifndef GL_H
#define GL_H

#include <glad/glad.h>



GLuint gl_shader_program_create(const char *vertex_src,
                                const char *fragment_src);


#endif /* GL_H */
