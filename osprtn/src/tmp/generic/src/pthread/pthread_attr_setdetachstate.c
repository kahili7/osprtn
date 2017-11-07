#include <errno-defs.h>
#include <pthread.h>

int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate)
{
    if(detachstate != PTHREAD_CREATE_DETACHED && detachstate != PTHREAD_CREATE_JOINABLE) return EINVAL;
 
    attr->__flags = (attr->__flags & ~PTHREAD_DETACHSTATE_MASK) | detachstate;
    return EOK;
}