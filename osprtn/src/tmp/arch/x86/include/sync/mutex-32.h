#ifndef ARCH_X86_SYNC_MUTEX_32_H
#define ARCH_X86_SYNC_MUTEX_32_H

#include _SOS_CPU_HDR_DIR_(alternative.h)

// блокировка с помощью мютекса
#define __mutex_fastpath_lock(count, fail_fn)\
        do {\
            unsigned int dummy;\
            typecheck(atomic_t *, count);\
            typecheck_fn(void (*)(atomic_t *), fail_fn);\
            \
            asm volatile(LOCK_PREFIX " decl (%%eax)\n"\
                         " jns 1f\n"\
                         " call " #fail_fn "\n"\
                         "1:\n"\
                         : "=a" (dummy)\
                         : "a" (count)\
                         : "memory", "ecx", "edx");\
        } while (0)

static inline int __mutex_fastpath_lock_retval(atomic_t *count)
{
    if (unlikely(atomic_dec_return(count) < 0)) return -1;
    else return 0;
}

// разблокировка мютекса
#define __mutex_fastpath_unlock(count, fail_fn)\
        do {\
            unsigned int dummy;\
            typecheck(atomic_t *, count);\
            typecheck_fn(void (*)(atomic_t *), fail_fn);\
            \
            asm volatile(LOCK_PREFIX " incl (%%eax)\n"\
                         " jg 1f\n"\
                         " call " #fail_fn "\n"\
                         "1:\n"\
                         : "=a" (dummy)\
                         : "a" (count)\
                         : "memory", "ecx", "edx");\
        } while (0)

#define __mutex_slowpath_needs_to_unlock()  1

// попытка заблокировать мютекс
static inline int __mutex_fastpath_trylock(atomic_t *count, int (*fail_fn)(atomic_t *))
{
    #ifdef __HAVE_ARCH_CMPXCHG
        if (likely(atomic_cmpxchg(count, 1, 0) == 1)) return 1;
        return 0;
    #else
        return fail_fn(count);
    #endif
}
#endif /* ARCH_X86_SYNC_MUTEX_32_H */