#include <app.h>
#include <core/log.h>

#include <stdlib.h>

int main()
{
    struct Application *app = get_app_instance();
    if (!init_app(app))
    {
        LOG_FATAL("Failed to initialise application!");
        destroy_app(app);
        exit(1);
    }

    int status = run_app(app);
    destroy_app(app);

    return status;
}