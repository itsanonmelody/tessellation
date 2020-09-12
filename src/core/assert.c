#include <util.h>
#include <core/assert.h>

#include <stdio.h>
#include <signal.h>
#include <stdarg.h>

#define TIME_BUFFER_SIZE 25
#define DEBUG_BREAK() raise(SIGTRAP)

void core_assert(bool condition, const char *format, ...)
{
    if (condition)
        return;
    
    char time[TIME_BUFFER_SIZE];
    get_time(time, TIME_BUFFER_SIZE, "%a %d %b %Y %H:%M:%S");
    fprintf(stderr, "[%s] ASSERT | ", time);

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");
    DEBUG_BREAK();
}