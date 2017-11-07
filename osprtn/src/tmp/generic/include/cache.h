#ifndef GENERIC_CACHE_H
#define GENERIC_CACHE_H

#include _SOS_CPU_HDR_DIR_(cache.h)

/*
 * выравнивание на границу кэша
 */

#ifndef SMP_CACHE_BYTES
    #define SMP_CACHE_BYTES L1_CACHE_BYTES
#endif

#ifndef ____cacheline_aligned
    #define ____cacheline_aligned __attribute__((__aligned__(SMP_CACHE_BYTES)))
#endif

#ifndef ____cacheline_aligned_in_smp
    #ifdef CONFIG_SMP
        #define ____cacheline_aligned_in_smp ____cacheline_aligned
    #else
        #define ____cacheline_aligned_in_smp
    #endif /* CONFIG_SMP */
#endif
 
#endif /* GENERIC_CACHE_H */