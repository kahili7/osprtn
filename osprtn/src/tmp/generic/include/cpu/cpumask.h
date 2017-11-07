#ifndef GENERIC_CPU_CPUMASK_H
#define GENERIC_CPU_CPUMASK_H

#include <kernel.h>
#include <bit/bitmap.h>
#include <bug.h>
/*
 * предоставляет доступ к установленным процессорам
 */

typedef struct cpumask_struct { 
    DECLARE_BITMAP(bits, NR_CPUS);
} cpumask_t;

#define cpumask_bits(maskp) ((maskp)->bits)

// количество CPU
#if NR_CPUS == 1
    #define nr_cpu_ids		1
#else
    extern int nr_cpu_ids;
#endif

// маска CPU
#ifdef CONFIG_CPUMASK_OFFSTACK
    #define nr_cpumask_bits	nr_cpu_ids
#else
    #define nr_cpumask_bits	NR_CPUS
#endif

// доступен для вычислений
#define cpu_possible_mask   ((const struct cpumask_struct *)&__cpu_possible_mask)
extern struct cpumask_struct __cpu_possible_mask;

// вычисляет
#define cpu_present_mask    ((const struct cpumask_struct *)&__cpu_present_mask)
extern struct cpumask_struct __cpu_present_mask;

// доступен для планировщика
#define cpu_online_mask     ((const struct cpumask_struct *)&__cpu_online_mask)
extern struct cpumask_struct __cpu_online_mask;

// доступен для миграции
#define cpu_active_mask     ((const struct cpumask_struct *)&__cpu_active_mask)
extern struct cpumask_struct __cpu_active_mask;


#if NR_CPUS > 1
    #define num_online_cpus()       cpumask_weight(cpu_online_mask)
    #define num_possible_cpus()     cpumask_weight(cpu_possible_mask)
    #define num_present_cpus()      cpumask_weight(cpu_present_mask)
    #define num_active_cpus()       cpumask_weight(cpu_active_mask)
    #define cpu_online(cpu)         cpumask_test_cpu((cpu), cpu_online_mask)
    #define cpu_possible(cpu)       cpumask_test_cpu((cpu), cpu_possible_mask)
    #define cpu_present(cpu)        cpumask_test_cpu((cpu), cpu_present_mask)
    #define cpu_active(cpu)         cpumask_test_cpu((cpu), cpu_active_mask)
#else
    #define num_online_cpus()       1U
    #define num_possible_cpus()     1U
    #define num_present_cpus()      1U
    #define num_active_cpus()       1U
    #define cpu_online(cpu)         ((cpu) == 0)
    #define cpu_possible(cpu)       ((cpu) == 0)
    #define cpu_present(cpu)        ((cpu) == 0)
    #define cpu_active(cpu)         ((cpu) == 0)
#endif


static inline unsigned int cpumask_check(unsigned int cpu)
{
#ifdef CONFIG_DEBUG_PER_CPU_MAPS
	WARN_ON_ONCE(cpu >= nr_cpumask_bits);
#endif /* CONFIG_DEBUG_PER_CPU_MAPS */
    return cpu;
}

#if NR_CPUS == 1
    static inline unsigned int cpumask_next(int n, const struct cpumask_struct *srcp)
    {
        return n + 1;
    }

    static inline unsigned int cpumask_next_zero(int n, const struct cpumask_struct *srcp)
    {
        return n + 1;
    }

    static inline unsigned int cpumask_next_and(int n, const struct cpumask_struct *srcp, const struct cpumask_struct *andp)
    {
        return n + 1;
    }

    static inline unsigned int cpumask_any_but(const struct cpumask_struct *mask, unsigned int cpu)
    {
        return 1;
    }

    static inline unsigned int cpumask_local_spread(unsigned int i, int node)
    {
        return 0;
    }
    
    #define for_each_cpu(cpu, mask)             for ((cpu) = 0; (cpu) < 1; (cpu)++, (void)mask)
    #define for_each_cpu_not(cpu, mask)         for ((cpu) = 0; (cpu) < 1; (cpu)++, (void)mask)
    #define for_each_cpu_and(cpu, mask, and)    for ((cpu) = 0; (cpu) < 1; (cpu)++, (void)mask, (void)and)
#else
    // возвращает первый CPU
    static inline unsigned int cpumask_first(const struct cpumask_struct *srcp)
    {
        return find_first_bit(cpumask_bits(srcp), nr_cpumask_bits);
    }
    
    // возвращает следующий CPU
    static inline unsigned int cpumask_next(int n, const struct cpumask_struct *srcp)
    {
        if (n != -1) cpumask_check(n);
        
        return find_next_bit(cpumask_bits(srcp), nr_cpumask_bits, n + 1);
    }
    
    // возвращает следующий не установленный CPU
    static inline unsigned int cpumask_next_zero(int n, const struct cpumask_struct *srcp)
    {
        if (n != -1) cpumask_check(n);
        
        return find_next_zero_bit(cpumask_bits(srcp), nr_cpumask_bits, n + 1);
    }

    int cpumask_next_and(int n, const struct cpumask_struct *, const struct cpumask_struct *);
    int cpumask_any_but(const struct cpumask_struct *mask, unsigned int cpu);
    unsigned int cpumask_local_spread(unsigned int i, int node);
    
    #define for_each_cpu(cpu, mask)             for ((cpu) = -1; (cpu) = cpumask_next((cpu), (mask)), (cpu) < nr_cpu_ids;)
    #define for_each_cpu_not(cpu, mask)         for ((cpu) = -1; (cpu) = cpumask_next_zero((cpu), (mask)), (cpu) < nr_cpu_ids;)
    #define for_each_cpu_and(cpu, mask, and)    for ((cpu) = -1; (cpu) = cpumask_next_and((cpu), (mask), (and)), (cpu) < nr_cpu_ids;)
#endif

#define CPU_BITS_NONE   { [0 ... BITS_TO_LONGS(NR_CPUS)-1] = 0UL }
#define CPU_BITS_CPU0   { [0] =  1UL }

// установка процессора в cpumask
static inline void cpumask_set_cpu(unsigned int cpu, struct cpumask_struct *dstp)
{
    set_bit(cpumask_check(cpu), cpumask_bits(dstp));
}

// очистка процессора в cpumask
static inline void cpumask_clear_cpu(int cpu, struct cpumask_struct *dstp)
{
    clear_bit(cpumask_check(cpu), cpumask_bits(dstp));
}

// тест процессора в cpumask
static inline int cpumask_test_cpu(int cpu, const struct cpumask_struct *cpumask)
{
    return test_bit(cpumask_check(cpu), cpumask_bits((cpumask)));
}

// тест и установка процессора в cpumask
static inline int cpumask_test_and_set_cpu(int cpu, struct cpumask_struct *cpumask)
{
    return test_and_set_bit(cpumask_check(cpu), cpumask_bits(cpumask));
}

// тест и очистка процессора в cpumask
static inline int cpumask_test_and_clear_cpu(int cpu, struct cpumask_struct *cpumask)
{
    return test_and_clear_bit(cpumask_check(cpu), cpumask_bits(cpumask));
}
#endif /* GENERIC_CPU_CPUMASK_H */