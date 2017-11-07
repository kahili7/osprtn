#include <errno.h>
#include <pthread.h>
#include <sys/proton.h>

int pthread_attr_init(pthread_attr_t *attr)
{
    static long pagesize;
    int ret;

    *attr = pthread_attr_default;
    
    if((ret = ptn_SchedGet_r(0, 0, (struct sched_param *)&attr->__param)) < 0) return -ret;
    
    attr->__policy = ret;

    if(pagesize == 0)
    {
        ret = errno;
        
        if((pagesize = sysconf(_SC_PAGESIZE)) == -1) errno = ret;
    }

    attr->__guardsize = pagesize <= 0 ? 0 : pagesize;
    return EOK;
}

