#include <util.h>

#include <time.h>

void get_time(char *buffer, int max_size, const char *format)
{
    time_t t = time(NULL);
    strftime(buffer, max_size, format, localtime(&t));
}