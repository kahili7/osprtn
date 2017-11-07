#ifndef KERNEL_API_CPU_H
#define KERNEL_API_CPU_H

typedef u16_t cpuid_t;

typedef struct cpu {
    word_t id;
    word_t count;
    
    cpu_t descriptors[CONFIG_SMP_MAX_CPUS];
} cpu_t;

INLINE cpuid_t get_current_cpu()
{
    extern cpuid_t current_cpu;
    
    return current_cpu;
}

static cpu_t *cpu_get(cpu_t *s, cpuid_t cpuid)
{
    return &s->descriptors[cpuid];
}

static int cpu_add_cpu(cpu_t *s, word_t id)
{
    if (s->count >= CONFIG_SMP_MAX_CPUS) return 0;
    
    cpu_t *t = s->descriptors[s->count++];
    
    t->id = id;
    return 1;
}
#endif /* KERNEL_API_CPU_H */