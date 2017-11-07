#include <errno-defs.h>
#include <limits.h>
#include <pthread.h>

int pthread_attr_setstack(pthread_attr_t *attr, void *stackaddr, size_t stacksize)
{
    if (stacksize != 0 && stacksize < PTHREAD_STACK_MIN) return(EINVAL);
    
    attr->__stackaddr = stackaddr;
    attr->__stacksize = stacksize;
    return EOK;
}