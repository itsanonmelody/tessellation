#include <app.h>
#include <memory.h>
#include <core/log.h>
#include <graphics/shader.h>

#include <cglm/call.h>
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

    float model1[] = {
        // Location           // Color
         0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,
        -1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,
        -2.0f, 0.5f, 0.0f,    1.0f, 1.0f, 1.0f,
        -1.0f, 0.5f, 0.0f,    1.0f, 1.0f, 1.0f,
         0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,

        -0.20f, 0.05f, 0.0f,    0.2f, 0.5f, 0.8f,
        -1.00f, 0.05f, 0.0f,    0.2f, 0.5f, 0.8f,
        -1.90f, 0.50f, 0.0f,    0.2f, 0.5f, 0.8f,
        -1.10f, 0.50f, 0.0f,    0.2f, 0.5f, 0.8f,
        -0.20f, 0.95f, 0.0f,    0.2f, 0.5f, 0.8f,
        -1.00f, 0.95f, 0.0f,    0.2f, 0.5f, 0.8f
    };

    float model2[] = {
        // Location           // Color
         0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,
        -1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,
        -2.0f, 0.5f, 0.0f,    1.0f, 1.0f, 1.0f,
        -1.0f, 0.5f, 0.0f,    1.0f, 1.0f, 1.0f,
         0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,

        -0.20f, 0.05f, 0.0f,    0.8f, 0.8f, 0.2f, 
        -1.00f, 0.05f, 0.0f,    0.8f, 0.8f, 0.2f, 
        -1.90f, 0.50f, 0.0f,    0.8f, 0.8f, 0.2f, 
        -1.10f, 0.50f, 0.0f,    0.8f, 0.8f, 0.2f, 
        -0.20f, 0.95f, 0.0f,    0.8f, 0.8f, 0.2f, 
        -1.00f, 0.95f, 0.0f,    0.8f, 0.8f, 0.2f
    };

    unsigned int indices[] = {
        // Border.
        0, 1, 2,
        0, 3, 2,
        2, 3, 4,
        2, 5, 4,

        // Fill.
        6, 7, 8,
        6, 9, 8,
        8, 9, 10,
        8, 11, 10
    };

    const char *vertex_source =
        "#version 330 core\n"
        "layout(location = 0) in vec3 a_Pos;\n"
        "layout(location = 1) in vec3 a_Color;\n"
        "out vec4 color;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "  color = vec4(a_Color, 1.0);\n"
        "  gl_Position = projection * view * model * vec4(a_Pos, 1.0);\n"
        "}";
    
    const char *fragment_source =
        "#version 330 core\n"
        "in vec4 color;\n"
        "out vec4 pixel;\n"
        "void main() {\n"
        "  pixel = color;\n"
        "}";
    
    unsigned int shader_program = create_shader(vertex_source, fragment_source);

    unsigned int vao[2];
    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[0]);

    unsigned int vbo[3];
    glGenBuffers(3, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model1), model1, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(vao[1]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model2), model2, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
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

        mat4 view;
        glmc_lookat(
            (vec3){ 0.0f, 0.0f, -3.0f },
            (vec3){ 0.0f, 0.0f,  0.0f },
            (vec3){ 0.0f, 1.0f,  0.0f },
            view
        );

        glUniformMatrix4fv(
            glGetUniformLocation(shader_program, "view"),
            1,
            GL_FALSE,
            (float*)view
        );

        float aspect_ratio =
            2 * (float)app->window.data.width / (float)app->window.data.height;

        mat4 projection;
        glmc_ortho(
           -aspect_ratio, aspect_ratio,
           -2.0f, 2.0f,
            0.1f, 100.0f,
            projection
        );

        glUniformMatrix4fv(
            glGetUniformLocation(shader_program, "projection"),
            1,
            GL_FALSE,
            (float*)projection
        );

        glBindVertexArray(vao[0]);
        for (int i = 0; i < 2; i++)
        {
            float y = 1.0f - 2.0f * i;
            for (int j = 0; j < 9; j++)
            {
                float x = 5.0f - 1.0f * j;
                mat4 model;
                glmc_mat4_identity(model);
                glmc_translate(model, (vec3){ x, y, 0.0f });

                glUniformMatrix4fv(
                    glGetUniformLocation(shader_program, "model"),
                    1,
                    GL_FALSE,
                    (float*)model
                );

                glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, NULL);
            }
        }

        glBindVertexArray(vao[1]);
        for (int i = 0; i < 2; i++)
        {
            float y = 0.0f - 2.0f * i;
            for (int j = 0; j < 9; j++)
            {
                float x = 5.0f - 1.0f * j;
                mat4 model;
                glmc_mat4_identity(model);
                glmc_scale(model, (vec3){ -1.0f, 1.0f, 0.0f });
                glmc_translate(model, (vec3){ x, y, 0.0f });

                glUniformMatrix4fv(
                    glGetUniformLocation(shader_program, "model"),
                    1,
                    GL_FALSE,
                    (float*)model
                );

                glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, NULL);
            }
        }

        glfwSwapBuffers(app->window.native_window);
        glfwPollEvents();
    }

    glDeleteBuffers(3, vbo);
    glDeleteVertexArrays(2, vao);

    glDeleteProgram(shader_program);

    return 0;
}

void close_app(struct Application *app)
{
    app->running = false;
}