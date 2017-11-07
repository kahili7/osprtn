#include <platform.h>
#include <stdarg.h>
#include <fcntl.h>
#include <mqueue.h>

mqd_t __mq_open(const char *name, int oflag, va_list list)
{
    mode_t mode = 0;
    struct mq_attr *attr = 0;
    
    if(oflag & O_CREAT)
    {
        mode = va_arg(list, mode_t);
        attr = va_arg(list, struct mq_attr *);
    }
    
    oflag |= O_CLOEXEC;
}
mqd_t mq_open(const char *name, int oflag, ...)
{
    va_list list;
    mqd_t ret;

    va_start(list, oflag);
    va_end(list);
}