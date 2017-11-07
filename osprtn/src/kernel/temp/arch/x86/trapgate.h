#ifndef KERNEL_ARCH_X86_TRAPGATE_H
#define KERNEL_ARCH_X86_TRAPGATE_H

#include DIR_CPU(trapgate.h)

typedef struct x86_exceptionframe {
    x86_exceptionregs_t *eregs;
    
#if defined(CONFIG_DEBUG)
    const char      *name[num_regs];
    const word_t    dbgreg[num_dbgregs];
#endif
} x86_exceptionframe_t;
#endif /* KERNEL_ARCH_X86_TRAPGATE_H */