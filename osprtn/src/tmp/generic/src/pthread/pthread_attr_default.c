#include <pthread.h>

// переменная настройки атрибутов потока по умолчанию
const pthread_attr_t pthread_attr_default = {
    PTHREAD_CREATE_JOINABLE | PTHREAD_SCOPE_SYSTEM | PTHREAD_CANCEL_DEFERRED | PTHREAD_CANCEL_ENABLE | PTHREAD_INHERIT_SCHED,
    0,							/* No size so kernel will allocate PTHREAD_STACK_MIN	*/
    0,							/* No stackaddr so kernel will allocate one */
    __my_thread_exit,			/* Exit that is always register passing */
    -1,							/* Ignored because of PTHREAD_INHERIT_SCHED */
    { -1, -1 },					/* Ignored because of PTHREAD_INHERIT_SCHED */
    PAGE_SIZE,					/* Default guardpage size should default to PAGESIZE */
    0,							/* Default stack preallocation */
};

extern void __my_thread_exit(void *);