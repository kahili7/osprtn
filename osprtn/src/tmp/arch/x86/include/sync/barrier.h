#ifndef ARCH_X86_BARRIER_H
#define ARCH_X86_BARRIER_H

#include _SOS_CPU_HDR_DIR_(alternative.h)
#include _SOS_CPU_HDR_DIR_(nops.h)

/*
 * барьер процессора
 */
#ifdef CONFIG_X86_32
    #define mb()    alternative("lock; addl $0,0(%%esp)", "mfence", X86_FEATURE_XMM2)
    #define rmb()   alternative("lock; addl $0,0(%%esp)", "lfence", X86_FEATURE_XMM2)
    #define wmb()   alternative("lock; addl $0,0(%%esp)", "sfence", X86_FEATURE_XMM)
#else
    #define mb()    asm volatile("mfence":::"memory")       // загрузка и восстановление памяти
    #define rmb()   asm volatile("lfence":::"memory")       // загрузка из память
    #define wmb()   asm volatile("sfence" ::: "memory")     // сохранение в память
#endif

#define read_barrier_depends()  do { } while (0)

#ifdef CONFIG_SMP
    #define smp_mb()	mb()
    #ifdef CONFIG_X86_PPRO_FENCE
    # define smp_rmb()	rmb()
    #else
    # define smp_rmb()	barrier()
    #endif
    #ifdef CONFIG_X86_OOSTORE
    # define smp_wmb() 	wmb()
    #else
    # define smp_wmb()	barrier()
    #endif
    #define smp_read_barrier_depends()	read_barrier_depends()
    #define set_mb(var, value) do { (void)xchg(&var, value); } while (0)
#else
    #define smp_mb()    barrier()
    #define smp_rmb()	barrier()
    #define smp_wmb()	barrier()
    #define smp_read_barrier_depends()  do { } while (0)
    #define set_mb(var, value)          do { var = value; barrier(); } while (0)
#endif

#define smp_mb__before_atomic() barrier()
#define smp_mb__after_atomic()  barrier()

// барьер для регистра TSC
static __always_inline void rdtsc_barrier(void)
{
    alternative(ASM_NOP3, "mfence", X86_FEATURE_MFENCE_RDTSC);
    alternative(ASM_NOP3, "lfence", X86_FEATURE_LFENCE_RDTSC);
}
#endif /* ARCH_X86_BARRIER_H */

