#ifndef ARCH_X86_ATOMIC_H
#define ARCH_X86_ATOMIC_H

#include <compiler.h>
#include <types.h>
#include _SOS_CPU_HDR_DIR_(processor.h)
#include _SOS_CPU_HDR_DIR_(sync/cmpxchg.h)
#include _SOS_CPU_HDR_DIR_(sync/barrier.h)

/*
 * определение атомарных операций, для подсчета ресурсов
 */

// чтение
static inline int atomic_read(const atomic_t *v)
{
    return (*(volatile int *)&(v)->counter);
}

// установить значение
static inline void atomic_set(atomic_t *v, int i)
{
    v->counter = i;
}

// добавить значение
static inline void atomic_add(int i, atomic_t *v)
{
    asm volatile(LOCK_PREFIX "addl %1,%0" : "+m" (v->counter) : "ir" (i));
}

// вычесть значение
static inline void atomic_sub(int i, atomic_t *v)
{
    asm volatile(LOCK_PREFIX "subl %1,%0" : "+m" (v->counter) : "ir" (i));
}

// вычесть значение, если результат 0 возвратить 1
static inline int atomic_sub_and_test(int i, atomic_t *v)
{
    unsigned char c;

    asm volatile(LOCK_PREFIX "subl %2,%0; sete %1" : "+m" (v->counter), "=qm" (c) : "ir" (i) : "memory");
    return c;
}

// увеличить на 1
static inline void atomic_inc(atomic_t *v)
{
    asm volatile(LOCK_PREFIX "incl %0" : "+m" (v->counter));
}

// увеличить значение на 1, если результат 0 возвратить 1
static inline int atomic_inc_and_test(atomic_t *v)
{
    unsigned char c;

    asm volatile(LOCK_PREFIX "incl %0; sete %1" : "+m" (v->counter), "=qm" (c) : : "memory");
    return c != 0;
}

// уменьшить на 1
static inline void atomic_dec(atomic_t *v)
{
    asm volatile(LOCK_PREFIX "decl %0" : "+m" (v->counter));
}


// уменьшить значение на 1, если результат 0 возвратить 1
static inline int atomic_dec_and_test(atomic_t *v)
{
    unsigned char c;

    asm volatile(LOCK_PREFIX "decl %0; sete %1" : "+m" (v->counter), "=qm" (c) : : "memory");
    return c != 0;
}

// добавить значение и проверить на знак
static inline int atomic_add_negative(int i, atomic_t *v)
{
    unsigned char c;

    asm volatile(LOCK_PREFIX "addl %2,%0; sets %1" : "+m" (v->counter), "=qm" (c) : "ir" (i) : "memory");
    return c;
}

// авто добавляет v + i, затем i + v
#define atomic_inc_return(v)  (atomic_add_return(1, v))

static inline int atomic_add_return(int i, atomic_t *v)
{
    return i + xadd_smp(&v->counter, i);
}

// авто вычитает v - i, затем i - v
#define atomic_dec_return(v)  (atomic_sub_return(1, v))

static inline int atomic_sub_return(int i, atomic_t *v)
{
    return atomic_add_return(-i, v);
}

static inline int atomic_cmpxchg(atomic_t *v, int old, int n)
{
    return cmpxchg_smp(&v->counter, old, n);
}

static inline int atomic_xchg(atomic_t *v, int n)
{
    return xchg(&v->counter, n);
}
#endif /* ARCH_X86_ATOMIC_H */