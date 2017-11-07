#include <errno-defs.h>
#include <pthread.h>

int pthread_attr_getstacklazy(const pthread_attr_t *attr, int *lazystate)
{
    *lazystate = (int)(attr->__flags & PTHREAD_NOTLAZYSTACK_MASK);
    return EOK;
}