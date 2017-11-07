#include <errno-defs.h>
#include <pthread.h>

int pthread_attr_setstacklazy(pthread_attr_t *attr, int lazystate)
{
    switch(lazystate)
    {
        case PTHREAD_STACK_LAZY:
        case PTHREAD_STACK_NOTLAZY:
            break;
            
        default:
            return EINVAL;
    }
    
    attr->__flags = (attr->__flags & ~PTHREAD_NOTLAZYSTACK_MASK) | lazystate;
    return EOK;
}