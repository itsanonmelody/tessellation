#include <app.h>
#include <memory.h>
#include <core/log.h>
#include <graphics/shader.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_TITLE "Tessellation"

struct Application* get_app_instance()
{
    static struct Application app;
    return &app;
}

static void glfw_error_callback(int error_code, const char *description)
{
    LOG_ERROR("GLFW Error(%d): %s", error_code, description);
}

static void window_resize_callback(GLFWwindow *window, int width, int height)
{
    struct WindowData *data = (struct WindowData*)glfwGetWindowUserPointer(window);
    data->width = width;
    data->height = height;
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static bool init_window(struct Window *window)
{

    GLFWmonitor *primary_monitor = glfwGetPrimaryMonitor();
    if (primary_monitor == NULL)
    {
        LOG_ERROR("Failed to get primary monitor information!");
        return false;
    }

    const GLFWvidmode *video_mode = glfwGetVideoMode(primary_monitor);
    if (video_mode == NULL)
    {
        LOG_ERROR("Failed to get video mode!");
        return false;
    }

    window->data.title = WINDOW_TITLE;
    window->data.width = (unsigned int)(0.6f * video_mode->width);
    window->data.height = (unsigned int)(0.6f * video_mode->height);

    LOG_TRACE("Creating window %s (%u, %u)", window->data.title, window->data.width, window->data.height);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window->native_window = glfwCreateWindow(
        window->data.width,
        window->data.height,
        window->data.title,
        NULL,
        NULL
    );

    if (window->native_window == NULL)
    {
        LOG_ERROR("Failed to create window!");
        return false;
    }
    glfwMakeContextCurrent(window->native_window);
    glfwSetWindowAspectRatio(window->native_window, video_mode->width, video_mode->height);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("Failed to load Glad!");
        return false;
    }

    glfwSetWindowUserPointer(window->native_window, &window->data);
    glfwSetWindowSizeCallback(window->native_window, window_resize_callback);
    glfwSetFramebufferSizeCallback(window->native_window, framebuffer_size_callback);

    return true;
}

bool init_app(struct Application *app)
{
    LOG_TRACE("Initialising application...");

    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
        LOG_ERROR("Failed to initialise GLFW!");
        return false;
    }

    if (!init_window(&app->window))
    {
        LOG_ERROR("Failed to initialize window!");
        return false;
    }

    app->running = false;
    return true;
}

void destroy_app(struct Application *app)
{
    LOG_TRACE("Cleaning up application...");
    LOG_INFO("Memory allocated: %zu", get_memory_allocated());
    LOG_INFO("Memory freed: %zu", get_memory_freed());

    glfwDestroyWindow(app->window.native_window);
    glfwTerminate();
}

int run_app(struct Application *app)
{
    LOG_TRACE("Running application...");
    app->running = true;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 3, 2
    };

    const char *vertex_source =
        "#version 330 core\n"
        "layout(location = 0) in vec3 a_Pos;\n"
        "void main() {\n"
        "  gl_Position = vec4(a_Pos, 1.0);\n"
        "}";
    
    const char *fragment_source =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main() {\n"
        "  color = vec4(0.8, 0.3, 0.5, 1.0);\n"
        "}";
    
    unsigned int shader_program = create_shader(vertex_source, fragment_source);

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo[2];
    glGenBuffers(2, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    while (app->running)
    {
        if (glfwWindowShouldClose(app->window.native_window))
        {
            close_app(app);
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        glfwSwapBuffers(app->window.native_window);
        glfwPollEvents();
    }

    glDeleteBuffers(2, vbo);
    glDeleteVertexArrays(1, &vao);

    glDeleteProgram(shader_program);

    return 0;
}

void close_app(struct Application *app)
{
    app->running = false;
}