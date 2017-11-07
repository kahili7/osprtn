#ifndef GENERIC_PREEMPT_H
#define GENERIC_PREEMPT_H

#include <thread-info.h>

/*
 * макросы для доступа и манипулирования preempt_count
 */

// счетчик количества вытеснений
#define preempt_count()	(current_thread_info()->preempt_count)

// добавление значения к счетчику
#define add_preempt_count(val)	do { preempt_count() += (val); } while (0)
#define sub_preempt_count(val)	do { preempt_count() -= (val); } while (0)

#define inc_preempt_count() add_preempt_count(1)
#define dec_preempt_count() sub_preempt_count(1)

#ifdef CONFIG_PREEMPT
#else
    #define preempt_check_resched()             do { } while (0)
    #define preempt_check_resched_context()     do { } while (0)
#endif

#ifdef CONFIG_PREEMPT_COUNT
    #define preempt_disable()\
            do {\
                inc_preempt_count();\
                barrier();\
            } while (0)

    #define sched_preempt_enable_no_resched()\
            do {\
                barrier();\
                dec_preempt_count();\
            } while (0)

    #define preempt_enable_no_resched() sched_preempt_enable_no_resched()

    #define preempt_enable()\
            do { \
                preempt_enable_no_resched();\
                barrier();\
                preempt_check_resched();\
            } while (0)
#else
    #define preempt_disable()                   barrier()
    #define sched_preempt_enable_no_resched()   barrier()
    #define preempt_enable_no_resched()         barrier()
    #define preempt_enable()                    barrier()
#endif
#endif /* GENERIC_PREEMPT_H */