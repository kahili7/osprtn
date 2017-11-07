#include DIR_ARCH(traps.h)
#include DIR_ARCH(segdesc.h)

#include DIR_BIND_ARCH(idt.h)

void SECTION(".init.system") idt_init_gate(idt_t *s, word_t index, x86_idt_type_e type, void (*address)())
{
    //ASSERT(index < IDT_SIZE);
    
    switch (type)
    {
        case idt_interrupt:
            x86_idtdesc_set(s->descriptors[index], X86_KERNEL_CS, address, x86_idt_type_e.idt_interrupt, 0);
            break;
            
        case idt_syscall:
            x86_idtdesc_set(s->descriptors[index], X86_KERNEL_CS, address, x86_idt_type_e.idt_interrupt, 3);
            break;
            
        case idt_trap:
            x86_idtdesc_set(s->descriptors[index], X86_KERNEL_CS, address, x86_idt_type_e.idt_trap, 0);
            break;
    }
}