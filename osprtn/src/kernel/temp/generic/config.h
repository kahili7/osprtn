#ifndef KERNEL_GENERIC_CONFIG_H
#define KERNEL_GENERIC_CONFIG_H

#include DIR_API(config.h)

#if defined(CONFIG_SMP)
    #define CONFIG_SMP_MAX_CPUS		CONFIG_SMP_MAX_PROCS
#else
    #define CONFIG_SMP_MAX_CPUS		1
#endif

#endif /* KERNEL_GENERIC_CONFIG_H */