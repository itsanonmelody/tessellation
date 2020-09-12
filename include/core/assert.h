#ifndef TSL_CORE_ASSERT_H
#define TSL_CORE_ASSERT_H

#include <common.h>

#ifdef TSL_DEBUG
    #define ASSERT(condition, ...) core_assert(condition, __VA_ARGS__)
    void core_assert(bool condition, const char *format, ...);
#else
    #define ASSERT(condition, ...)
#endif

#endif