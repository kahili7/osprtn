#ifndef KERNEL_ARCH_X86_TRAPS_H
#define KERNEL_ARCH_X86_TRAPS_H

#define X86_EXC_DIVIDE_ERROR        0
#define X86_EXC_DEBUG               1
#define X86_EXC_NMI                 2
#define X86_EXC_BREAKPOINT          3
#define X86_EXC_OVERFLOW            4
#define X86_EXC_BOUNDRANGE          5
#define X86_EXC_INVALIDOPCODE       6
#define X86_EXC_NOMATH_COPROC       7
#define X86_EXC_DOUBLEFAULT         8
#define X86_EXC_COPSEG_OVERRUN      9
#define X86_EXC_INVALID_TSS         10
#define X86_EXC_SEGMENT_NOT_PRESENT 11
#define X86_EXC_STACKSEG_FAULT      12
#define X86_EXC_GENERAL_PROTECTION  13
#define X86_EXC_PAGEFAULT           14
#define X86_EXC_RESERVED            15
#define X86_EXC_FPU_FAULT           16
#define X86_EXC_ALIGNEMENT_CHECK    17
#define X86_EXC_MACHINE_CHECK       18
#define X86_EXC_SIMD_FAULT          19

// зарезервированные исключения
#define X86_EXC_RESERVED_FIRST      20
#define X86_EXC_RESERVED_LAST       31

#endif /* KERNEL_ARCH_X86_TRAPS_H */