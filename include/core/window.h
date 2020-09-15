#ifndef TSL_CORE_WINDOW_H
#define TSL_CORE_WINDOW_H

struct GLFWwindow;

struct WindowData
{
    const char *title;
    unsigned int width;
    unsigned int height;
};

struct Window
{
    struct GLFWwindow *native_window;
    struct WindowData data;
};

#endif