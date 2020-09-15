#ifndef TSL_APP_H
#define TSL_APP_H

#include <common.h>
#include <core/window.h>

struct Application
{
    bool running;
    struct Window window;
};

struct Application* get_app_instance();
bool init_app(struct Application *app);
void destroy_app(struct Application *app);
int run_app(struct Application *app);
void close_app(struct Application *app);

#endif