#include <util.h>
#include <core/log.h>

#include <stdarg.h>

#define TIME_BUFFER_SIZE 25

static const char* log_levels[] = {
    "INFO",
    "TRACE",
    "WARN",
    "ERROR",
    "FATAL"
};

void core_log(FILE *stream, enum LogLevel level, const char *format, ...)
{
    char time[TIME_BUFFER_SIZE];
    get_time(time, TIME_BUFFER_SIZE, "%a %d %b %Y %H:%M:%S");
    fprintf(stream, "[%s] %-6s | ", time, log_levels[level]);

    va_list args;
    va_start(args, format);
    vfprintf(stream, format, args);
    va_end(args);

    fprintf(stream, "\n");
}