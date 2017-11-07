#ifndef KERNEL_ARCH_X86_SEGDESC_H
#define KERNEL_ARCH_X86_SEGDESC_H

#include DIR_CPU(segdesc.h)

typedef enum x86_regtype
{
    gdtr = 0x1,
    ldtr = 0x2,
    idtr = 0x3,
    tr   = 0x4
} x86_regtype_e;
    
typedef struct x86_descreg {
    union 
    {
	struct {
	    u16_t   size;
	    word_t  addr __attribute__((packed));
	} descriptor;
	u16_t  selector;
    };
} x86_descreg_t;

void x86_descreg_init_d(x86_descreg_t *s, word_t addr, u16_t size)
{ 
    s->descriptor.addr = addr; 
    s->descriptor.size = size;  
}

void x86_descreg_init_s(x86_descreg_t *s, u16_t sel)
{
    s->selector = sel;
}

void x86_descreg_setdescreg(x86_descreg_t *s, const x86_regtype_e type)
{
    switch(type)
    {	
        case gdtr:
            __asm__ __volatile__("lgdt %0\n" : /* No Output */ : "m"(s->descriptor)); 
            break;
            
        case idtr:
            __asm__ __volatile__("lidt %0\n" : /* No Output */ : "m"(s->descriptor));
            break;
            
        default:
            break;
    }	
}

void x86_descreg_getdescreg(x86_descreg_t *s, const x86_regtype_e type)
{
    switch(type)
    {	
        case gdtr:
            __asm__ __volatile__("sgdt %0\n" : "=m"(s->descriptor));
            break;
            
        case idtr:
            __asm__ __volatile__("sidt %0\n" : "=m"(s->descriptor));
            break;
            
        default:
            break;
    }	
}

void x86_descreg_setselreg(x86_descreg_t *s, const x86_regtype_e type)
{
    switch(type)
    {	
        case ldtr:
            __asm__ __volatile__("lldt %0\n" : /* No Output */ : "m"(s->selector));
            break;
            
        case tr:
            __asm__ __volatile__("ltr %0\n"  : /* No Output */ : "m"(s->selector));
            break;
            
        default:
            break;
    }	
}

void x86_descreg_getselreg(x86_descreg_t *s, const x86_regtype_e type)
{
    switch(type)
    {	
        case ldtr:
            __asm__ __volatile__("sldt %0\n" : "=m"(s->selector));
            break;
            
        case tr:
            __asm__ __volatile__("str %0\n" : "=m"(s->selector));
            break;
            
        default:
            s->selector = 0;
            break;
    }	
}
#endif /* KERNEL_ARCH_X86_SEGDESC_H */