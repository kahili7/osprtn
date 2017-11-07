#include <errno-defs.h>
#include <pthread.h>

int pthread_attr_getstackaddr(const pthread_attr_t *attr, void **stackaddr)
{
    *stackaddr = attr->__stackaddr;
    return EOK;
}