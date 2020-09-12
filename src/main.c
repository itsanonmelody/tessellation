#include <memory.h>
#include <core/log.h>

#include <time.h>
#include <stdlib.h>

int main()
{
    srand(time(NULL));
    void *block = NULL;
    size_t old_size = 0;

    for (long long i = 0; i < 500000; ++i)
    {
        size_t new_size = rand() + 1;
        reallocate(block, old_size, new_size);
        old_size = new_size;
    }

    FREE_S(block, old_size);

    LOG_INFO("Memory allocated: %zu", get_memory_allocated());
    LOG_INFO("Memory freed: %zu", get_memory_freed());

    return 0;
}