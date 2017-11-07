#include <sys/thread-storage.h>

struct _thread_local_storage * __tls(void)
{
    return(current_tls());
}