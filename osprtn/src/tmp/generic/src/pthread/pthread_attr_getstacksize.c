#include <errno-defs.h>
#include <pthread.h>

int pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize)
{
    *stacksize = attr->__stacksize;
    return EOK;
}