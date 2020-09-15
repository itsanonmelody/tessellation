#include <common.h>
#include <core/log.h>
#include <graphics/shader.h>

#include <glad/glad.h>

unsigned int create_shader(const char *vertex_source, const char *fragment_source)
{
    unsigned int shader_program = glCreateProgram();
    
    unsigned int shaders[2];
    shaders[0] = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaders[0], 1, &vertex_source, NULL);
    glCompileShader(shaders[0]);

    int success;
    glGetShaderiv(shaders[0], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        int info_log_length;
        glGetShaderiv(shaders[0], GL_INFO_LOG_LENGTH, &info_log_length);

        // info_log_length is decremented once to remove the newline at the end.
        char info_log[--info_log_length];
        glGetShaderInfoLog(shaders[0], info_log_length, NULL, info_log);

        LOG_ERROR("Failed to compile vertex shader:");
        LOG_ERROR("    %s", info_log);
    }

    shaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaders[1], 1, &fragment_source, NULL);
    glCompileShader(shaders[1]);

    glGetShaderiv(shaders[1], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        int info_log_length;
        glGetShaderiv(shaders[1], GL_INFO_LOG_LENGTH, &info_log_length);

        // info_log_length is decremented once to remove the newline at the end.
        char info_log[--info_log_length];
        glGetShaderInfoLog(shaders[1], info_log_length, NULL, info_log);

        LOG_ERROR("Failed to compile fragment shader:");
        LOG_ERROR("    %s", info_log);
    }

    glAttachShader(shader_program, shaders[0]);
    glAttachShader(shader_program, shaders[1]);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        int info_log_length;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &info_log_length);

        // info_log_length is decremented once to remove the newline at the end.
        char info_log[--info_log_length];
        glGetProgramInfoLog(shader_program, info_log_length, NULL, info_log);

        LOG_ERROR("Failed to link shaders:");
        LOG_ERROR("    %s", info_log);
    }

    glDetachShader(shader_program, shaders[1]);
    glDeleteShader(shaders[1]);

    glDetachShader(shader_program, shaders[0]);
    glDeleteShader(shaders[0]);

    return shader_program;
}