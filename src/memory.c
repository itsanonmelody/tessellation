#include <memory.h>

#include <stdlib.h>

static size_t memory_allocated = 0;
static size_t memory_freed = 0;

void* reallocate(void *block, size_t old_size, size_t new_size)
{
    if (new_size == 0)
    {
        free(block);
        memory_freed += old_size;
        return NULL;
    }

    int diff = new_size - old_size;
    memory_allocated += diff * (diff >= 0);
    memory_freed += -diff * (diff < 0);

    return realloc(block, new_size);
}

size_t get_memory_allocated()
{
    return memory_allocated;
}

size_t get_memory_freed()
{
    return memory_freed;
}