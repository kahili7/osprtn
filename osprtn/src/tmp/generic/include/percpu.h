#ifndef GENERIC_PERCPU_H
#define GENERIC_PERCPU_H
/*
 * определяет на каком процессоре будет находится переменная
 */

#include <stddef.h>
#include <preempt.h>
#include _SOS_CPU_HDR_DIR_(percpu.h)

// получение / сохрание переменной
#define get_cpu_var(var)\
        (*({\
            preempt_disable();\
            &__get_cpu_var(var);\
        }))

#define put_cpu_var(var)\
        do {\
            (void)&(var);\
            preempt_enable();\
        } while (0)

// получение / сохрание указателя
#define get_cpu_ptr(var)\
        ({\
            preempt_disable();\
            this_cpu_ptr(var);\
        })

#define put_cpu_ptr(var)\
        do {\
            (void)(var);\
            preempt_enable();\
        } while (0)

#endif /* GENERIC_PERCPU_H */