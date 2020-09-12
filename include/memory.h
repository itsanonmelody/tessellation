#ifndef TSL_MEMORY_H
#define TSL_MEMORY_H

#include <common.h>

#define ALLOC(type) \
    (type*)reallocate(NULL, 0, sizeof(type))

#define FREE(block, type) \
    reallocate((block), sizeof(type), 0)

#define FREE_S(block, size) \
    reallocate((block), (size), 0)

void* reallocate(void *block, size_t old_size, size_t new_size);
size_t get_memory_allocated();
size_t get_memory_freed();

#endif