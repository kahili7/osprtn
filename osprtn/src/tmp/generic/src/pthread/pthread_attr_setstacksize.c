#include <errno-defs.h>
#include <limits.h>
#include <pthread.h>

int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize)
{
    if (stacksize != 0 && stacksize < PTHREAD_STACK_MIN) return(EINVAL);

    attr->__stacksize = stacksize;
    return EOK;
}