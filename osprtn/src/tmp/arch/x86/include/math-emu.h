#ifndef ARCH_X86_MATH_EMU_H
#define ARCH_X86_MATH_EMU_H

#include _SOS_CPU_HDR_DIR_(ptrace.h)

/* 
 * эмуляция структуры данных сохраняемых в стеке для 80386/80486
 */
struct math_emu_info_struct {
    long __eip;
    union {
        struct pt_regs *regs;
            //struct kernel_vm86_regs *vm86;
    };
};
#endif /* ARCH_X86_MATH_EMU_H */