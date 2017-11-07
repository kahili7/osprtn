#include <errno-defs.h>
#include <pthread.h>

int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate)
{
    *detachstate = (int)(attr->__flags & PTHREAD_DETACHSTATE_MASK);
    return EOK;
}