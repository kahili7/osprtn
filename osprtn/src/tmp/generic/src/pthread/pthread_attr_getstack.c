#include <errno-defs.h>
#include <pthread.h>

int pthread_attr_getstack(const pthread_attr_t *attr, void **stackaddr, size_t *stacksize)
{
    *stackaddr = attr->__stackaddr;
    *stacksize = attr->__stacksize;
    return EOK;
}