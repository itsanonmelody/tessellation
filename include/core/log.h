#ifndef TSL_CORE_LOG_H
#define TSL_CORE_LOG_H

#include <stdio.h>

#ifdef TSL_DEBUG
    #define DEBUG_INFO(...)  core_log(stdout, LOG_LEVEL_INFO,  __VA_ARGS__)
    #define DEBUG_TRACE(...) core_log(stdout, LOG_LEVEL_TRACE, __VA_ARGS__)
    #define DEBUG_WARN(...)  core_log(stdout, LOG_LEVEL_WARN,  __VA_ARGS__)
    #define DEBUG_ERROR(...) core_log(stderr, LOG_LEVEL_ERROR, __VA_ARGS__)
    #define DEBUG_FATAL(...) core_log(stderr, LOG_LEVEL_FATAL, __VA_ARGS__)
#else
    #define DEBUG_INFO(...)
    #define DEBUG_TRACE(...)
    #define DEBUG_WARN(...)
    #define DEBUG_ERROR(...)
    #define DEBUG_FATAL(...)
#endif

#define LOG_INFO(...)  core_log(stdout, LOG_LEVEL_INFO,  __VA_ARGS__)
#define LOG_TRACE(...) core_log(stdout, LOG_LEVEL_TRACE, __VA_ARGS__)
#define LOG_WARN(...)  core_log(stdout, LOG_LEVEL_WARN,  __VA_ARGS__)
#define LOG_ERROR(...) core_log(stderr, LOG_LEVEL_ERROR, __VA_ARGS__)
#define LOG_FATAL(...) core_log(stderr, LOG_LEVEL_FATAL, __VA_ARGS__)

enum LogLevel
{
    LOG_LEVEL_INFO,
    LOG_LEVEL_TRACE,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
};

void core_log(FILE *stream, enum LogLevel level, const char *format, ...);

#endif