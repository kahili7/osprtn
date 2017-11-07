#ifndef ARCH_X86_CMPXCHG_H
#define ARCH_X86_CMPXCHG_H

#include _SOS_CPU_HDR_DIR_(alternative.h)

/*
 * определения атомарных операций
 */

#define __X86_CASE_B	1
#define __X86_CASE_W	2
#define __X86_CASE_L	4

#ifdef CONFIG_64BIT
    #define __X86_CASE_Q	8
#else
    #define __X86_CASE_Q	-1		/* sizeof will never return -1 */
#endif

// определение для описание блокирующей командой
#define __xchg_op(ptr, arg, op, lock)\
    ({\
        __typeof__ (*(ptr)) __ret = (arg);\
        switch (sizeof(*(ptr))) {\
            case __X86_CASE_B:\
                asm volatile (lock #op "b %b0, %1\n" : "+q" (__ret), "+m" (*(ptr)) : : "memory", "cc");\
                break;\
            case __X86_CASE_W:\
                asm volatile (lock #op "w %w0, %1\n" : "+r" (__ret), "+m" (*(ptr)) : : "memory", "cc");\
                break;\
            case __X86_CASE_L:\
                asm volatile (lock #op "l %0, %1\n" : "+r" (__ret), "+m" (*(ptr)) : : "memory", "cc");\
                break;\
            case __X86_CASE_Q:\
                asm volatile (lock #op "q %q0, %1\n" : "+r" (__ret), "+m" (*(ptr)) : : "memory", "cc");\
                break;\
            default:;\
        }\
        __ret;\
    })

// определение команды xchg asm без блокировки (блокировка включена в эту команду)
#define xchg(ptr, v)    __xchg_op((ptr), (v), xchg, "")

// сырое определение команды asm cmpxchg
#define __raw_cmpxchg(ptr, old, n, size, lock)\
    ({\
	__typeof__(*(ptr)) __ret = 0;\
	__typeof__(*(ptr)) __old = (old);\
	__typeof__(*(ptr)) __new = (n);\
	switch (size) {\
            case __X86_CASE_B:\
            {\
                volatile _Uint8t *__ptr = (volatile _Uint8t *)(ptr);\
                asm volatile(lock "cmpxchgb %2,%1" : "=a" (__ret), "+m" (*__ptr) : "q" (__new), "0" (__old) : "memory");\
                break;\
            }\
            case __X86_CASE_W:\
            {\
                volatile _Uint16t *__ptr = (volatile _Uint16t *)(ptr);\
                asm volatile(lock "cmpxchgw %2,%1" : "=a" (__ret), "+m" (*__ptr) : "r" (__new), "0" (__old) : "memory");\
                break;\
            }\
            case __X86_CASE_L:\
            {\
                volatile _Uint32t *__ptr = (volatile _Uint32t *)(ptr);\
                asm volatile(lock "cmpxchgl %2,%1" : "=a" (__ret), "+m" (*__ptr) : "r" (__new), "0" (__old) : "memory");\
                break;\
            }\
            case __X86_CASE_Q:\
            {\
                volatile _Uint64t *__ptr = (volatile _Uint64t *)(ptr);\
                asm volatile(lock "cmpxchgq %2,%1" : "=a" (__ret), "+m" (*__ptr) : "r" (__new), "0" (__old) : "memory");\
                break;\
            }\
            default:;\
	}\
	__ret;\
    })

#define __cmpxchg_smp(ptr, old, n, size)    __raw_cmpxchg((ptr), (old), (n), (size), LOCK_PREFIX)
#define __cmpxchg_sync(ptr, old, n, size)   __raw_cmpxchg((ptr), (old), (n), (size), "lock; ")
#define __cmpxchg_local(ptr, old, n, size)  __raw_cmpxchg((ptr), (old), (n), (size), "")

#define __HAVE_ARCH_CMPXCHG 1

#ifdef __HAVE_ARCH_CMPXCHG
#define cmpxchg_smp(ptr, old, n)      __cmpxchg_smp(ptr, old, n, sizeof(*(ptr)))
#define cmpxchg_sync(ptr, old, n)     __cmpxchg_sync(ptr, old, n, sizeof(*(ptr)))
#define cmpxchg_local(ptr, old, n)    __cmpxchg_local(ptr, old, n, sizeof(*(ptr)))
#endif

// определение команды ассемблера XADD (обмен и сложение)
#define __xadd(ptr, inc, lock)	__xchg_op((ptr), (inc), xadd, lock)

#define xadd_smp(ptr, inc)      __xadd((ptr), (inc), LOCK_PREFIX)   // блокируется, если SMP
#define xadd_sync(ptr, inc)	__xadd((ptr), (inc), "lock; ")      // всегда блокируется
#define xadd_local(ptr, inc)	__xadd((ptr), (inc), "")            // никогда не блокируется

// определение команды ассемблера ADD и изменяет флаги (сс)
#define __add(ptr, inc, lock)\
    ({\
        __typeof__ (*(ptr)) __ret = (inc);\
        switch (sizeof(*(ptr))) {\
            case __X86_CASE_B:\
                asm volatile (lock "addb %b1, %0\n" : "+m" (*(ptr)) : "qi" (inc) : "memory", "cc");\
                break;\
            case __X86_CASE_W:\
                asm volatile (lock "addw %w1, %0\n" : "+m" (*(ptr)) : "ri" (inc) : "memory", "cc");\
                break;\
            case __X86_CASE_L:					\
                asm volatile (lock "addl %1, %0\n" : "+m" (*(ptr)) : "ri" (inc) : "memory", "cc");\
                break;\
            case __X86_CASE_Q:					\
                asm volatile (lock "addq %1, %0\n" : "+m" (*(ptr)) : "ri" (inc) : "memory", "cc");\
                break;\
            default:;\
        }\
        __ret;\
    })

#define add_smp(ptr, inc)   __add((ptr), (inc), LOCK_PREFIX)
#define add_sync(ptr, inc)  __add((ptr), (inc), "lock; ")
#endif /* ARCH_X86_CMPXCHG_H */