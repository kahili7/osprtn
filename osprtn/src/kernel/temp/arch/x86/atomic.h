#ifndef KERNEL_ARCH_X86_ATOMIC_H
#define KERNEL_ARCH_X86_ATOMIC_H

#ifdef CONFIG_SMP
    #define X86_LOCK "lock;"
#else
    #define X86_LOCK
#endif

// определение атомарных операций, для подсчета ресурсов
typedef struct atomic {
    word_t val;
} atomic_t;

void atomic_init(atomic_t *v, word_t val)
{
    v->val = val;
}

#define INIT_ATOMIC(v, val) atomic_init(name, val);

// добавить значение
word_t atomic_add(atomic_t *v)
{
    __asm__ __volatile__(X86_LOCK "add $1,%0" : "=m" (v->val));
    return v->val;
}

//отнять значение
word_t atomic_sub(atomic_t *v)
{
    __asm__ __volatile__(X86_LOCK "sub $1,%0" : "=m" (v->val));
    return v->val;
}

int atomic_cmpxchg(atomic_t *v, word_t old_val, word_t new_val)
{
    int result;
    
    __asm__ __volatile__ (X86_LOCK "cmpxchg %1, %2\n\t"
                                   "setz %0\n\t" : "=a" (result) : "r" (new_val), "m"(v->val), "0" (old_val) : "memory");
    
    return (result);
}
#endif /* KERNEL_ARCH_X86_ATOMIC_H */