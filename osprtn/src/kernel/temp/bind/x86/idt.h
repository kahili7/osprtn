#ifndef KERNEL_BIND_X86_IDT_H
#define KERNEL_BIND_X86_IDT_H

#include <debug.h>
#include DIR_ARCH(segdesc.h)
#include DIR_BIND_CPU(config.h)

typedef enum x86_idt_type 
{
    idt_interrupt = 0,
    idt_syscall = 1,
    idt_trap = 2
} x86_idt_type_e;

typedef struct {
    x86_idtdesc_t descriptors[IDT_SIZE];    // размер таблицы прерываний
} idt_t;

INLINE x86_idtdesc_t idt_get_descriptor(idt_t *s, word_t index)
{
    //ASSERT(index < IDT_SIZE);
    return s->descriptors[index];
}

extern idt_t *idt;
#endif /* KERNEL_BIND_X86_IDT_H */