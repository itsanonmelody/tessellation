#include <core/assert.h>
#include <core/log.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

int main()
{
    DEBUG_INFO("DEBUG INFO");
    DEBUG_TRACE("DEBUG TRACE");
    DEBUG_WARN("DEBUG WARN");
    DEBUG_ERROR("DEBUG ERROR");
    DEBUG_FATAL("DEBUG FATAL");

    LOG_INFO("LOG INFO");
    LOG_TRACE("LOG TRACE");
    LOG_WARN("LOG WARN");
    LOG_ERROR("LOG ERROR");
    LOG_FATAL("LOG FATAL");

    ASSERT(false, "ASSERT");

    glfwInit();
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello, World!", NULL, NULL);
    if (window == NULL)
    {
        LOG_ERROR("Failed to create window!");

        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("Failed to load Glad!");

        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }
    glViewport(0, 0, 800, 600);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.8f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}