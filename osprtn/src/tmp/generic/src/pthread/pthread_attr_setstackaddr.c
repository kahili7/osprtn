#include <errno-defs.h>
#include <pthread.h>

int pthread_attr_setstackaddr(pthread_attr_t *attr, void *stackaddr)
{
    attr->__stackaddr = stackaddr;
    return EOK;
}