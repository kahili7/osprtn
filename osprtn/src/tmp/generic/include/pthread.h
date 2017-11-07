#ifndef GENERIC_PTHREAD_H
#define GENERIC_PTHREAD_H

#include <platform.h>

// --определение типов--

// тип дескриптора потока
#if defined(_PTHREAD_T)
    typedef _PTHREAD_T pthread_t;
    #undef _PTHREAD_T
#endif

#if defined(_PTHREAD_ATTR_T)
    typedef _PTHREAD_ATTR_T pthread_attr_t;
    #undef _PTHREAD_ATTR_T
#endif

#if defined(_SCHED_PARAM_T)
    typedef _SCHED_PARAM_T sched_param_t;
    #undef _SCHED_PARAM_T
#endif

// тип переменной состояния
#ifndef _PTHREAD_COND_T
#define _PTHREAD_COND_T struct _pthread_cond {\
            struct {\
                _Uint8t     __pthread_cond_flag[4];\
                _Uint16t    __pthread_cond_type;\
                _Uint16t    __pthread_cond_magic;\
            } __pthread_cond_flags;\
        }
    
    typedef _PTHREAD_COND_T pthread_cond_t;
#undef _PTHREAD_COND_T
#endif
    
// тип переменной состояния
#ifndef _PTHREAD_CONDATTR_T
#define _PTHREAD_CONDATTR_T struct _pthread_condattr {\
        }
    
    typedef _PTHREAD_CONDATTR_T pthread_condattr_t;
#endif

// маска
#define PTHREAD_DETACHSTATE_MASK    0x01

// создается поток и вызывается функция pthread_join
#define PTHREAD_CREATE_JOINABLE     0x00

// открепление атрибутов от всех потоков
#define PTHREAD_CREATE_DETACHED     0x01


// маска 
#define PTHREAD_INHERITSCHED_MASK   0x02
    
// планирования потоков наследуются от создающего потока
#define PTHREAD_INHERIT_SCHED       0x00
    
// атрибуты планирования потоков устанавливаются равным и соответствующим значениям, содержащимся в объекте атрибутов, заданном параметром attr
#define PTHREAD_EXPLICIT_SCHED      0x02

    
// маска
#define PTHREAD_CONTENTIONSCOPE_MASK    0x04
    
// установить область диспетчирования для системы
#define PTHREAD_SCOPE_SYSTEM		0x00
    
// установить область деспетчирования для потока
#define PTHREAD_SCOPE_PROCESS		0x04

    
// маска    
#define PTHREAD_CSTATE_MASK		0x10
    
// включить завершение потока
#define PTHREAD_CANCEL_ENABLE		0x00
    
// выключить завершение потока    
#define PTHREAD_CANCEL_DISABLE		0x10

    
// маска 
#define PTHREAD_CTYPE_MASK		0x20
    
// если включена отмена, отмена запросов находятся в состоянии ожидания до тех пор, пока точка отмены
#define PTHREAD_CANCEL_DEFERRED		0x00
    
// если отмена включена, новых или ожидающих отмена запросов может быть выполнена сразу
#define PTHREAD_CANCEL_ASYNCHRONOUS	0x20
    
    
#define PTHREAD_CANCEL_PENDING		0x40
    
    
#define PTHREAD_NOTLAZYSTACK_MASK   0x80 
#define PTHREAD_STACK_LAZY          0x00
#define PTHREAD_STACK_NOTLAZY       0x80

extern int pthread_attr_init(pthread_attr_t *__attr);


// получить и установить адрес стека
extern int pthread_attr_getstackaddr(const pthread_attr_t *__addr, void **__stackaddr);
extern int pthread_attr_setstackaddr(pthread_attr_t *__attr, void *__stackaddr);

// получить и установить размер стека
extern int pthread_attr_getstacksize(const pthread_attr_t *__attr, size_t *__stacksize);
extern int pthread_attr_setstacksize(pthread_attr_t *__attr, size_t __stacksize);

// получить и установить флаг состояния стека
extern int pthread_attr_getstacklazy(const pthread_attr_t *__attr, int *lazystate);
extern int pthread_attr_setstacklazy(pthread_attr_t *__attr, int lazystate);

// получить и установить стек
extern int pthread_attr_getstack(const pthread_attr_t *__attr, void **__stackaddr, size_t *__stacksize);
extern int pthread_attr_setstack(pthread_attr_t *__attr, void *__stackaddr, size_t __stacksize);

extern int pthread_attr_getdetachstate(const pthread_attr_t *__attr, int *__detachstate);
extern int pthread_attr_setdetachstate(pthread_attr_t *__attr, int __detachstate);

#endif /* GENERIC_PTHREAD_H */