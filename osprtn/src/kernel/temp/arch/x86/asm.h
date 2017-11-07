#ifndef KERNEL_ARCH_X86_ASM_H
#define KERNEL_ARCH_X86_ASM_H

#define BREAKPOINT()    ({ __asm__ __volatile__ ("int $0x03": :); })
#define CLOCK_CYCLES()  ({ register u64_t __cycles; __asm__ __volatile__ ("rdtsc" : "=A" (__cycles)); __cycles; })

#define __inline_INTERRUPT_DISABLE() __asm__ __volatile__ (\
        "cli\n"\
        "\tmovl %%eax,%%eax" : : :"memory")

#define __inline_INTERRUPT_ENABLE() __asm__ __volatile__ ("sti" : : :"memory")

#define HALT() __asm__ __volatile__ ( "hlt": : :"memory")
#define SETTS() ((void)({ register u16_t __reg; __asm__ __volatile__( "smsw %w0\n\torb $8,%b0\n\tlmsw %w0": "=q" (__reg):); }))
 

#define SLDT() ({ register u16_t __ldt; __asm__ ( "sldt %w0": "=q" (__ldt) :: "memory"); __ldt; })
#define LGDT(__gdt) ((void)({__asm__ ( "lgdt (%0)" :: "r" (__gdt) : "memory"); }))
#define SGDT(__gdt) __asm__ ( "sgdt (%0)" :: "r" (__gdt) : "memory" ) 

#define LIDT(__idt) ((void)({__asm__ ( "lidt (%0)" :: "r" (__idt)); }))
#define SIDT(__idt) ((void)({void *__ptr = (__idt); __asm__ ( "sidt (%0)" :: "r" (__ptr) : "memory"); })) 

#define LOAD_PGDIR(__dir) ((void)({__asm__ ( "movl %0,%%cr3" :: "r" (__dir)); }))
#define READ_PGDIR() ({register u32_t __dir; __asm__ ( "movl %%cr3,%0" : "=q" (__dir):); __dir; })

#define LOAD_CR0(__flags) ((void)({__asm__ ( "movl %0,%%cr0" :: "r" (__flags)); }))
#define READ_CR0() ({register u32_t __flags; __asm__ ( "movl %%cr0,%0" : "=q" (__flags):); __flags; })

#define LOAD_CR4(__flags) ((void)({__asm__ ( "movl %0,%%cr4": :"r" (__flags)); }))
#define READ_CR4() ({register u32_t __flags; __asm__ ( "movl %%cr4,%0" : "=q" (__flags):); __flags; })

// аннулирование TLB для одного конкретного виртуального адреса
#define INVLPG(__p) ((void)({__asm__ ("invlpg %0": : "m" (*(char *)__p): "memory"); }))

// загрузка в регистры
#define LOAD_DS(__seg)  (({ u16_t __tmp = (__seg); __asm__ ( "movw %0,%%ds": :"rm" (__tmp)); }))
#define LOAD_ES(__seg)  (({ u16_t __tmp = (__seg); __asm__ ( "movw %0,%%es": :"rm" (__tmp)); }))
#define LOAD_FS(__seg)  (({ u16_t __tmp = (__seg); __asm__ ( "movw %0,%%fs": :"rm" (__tmp)); }))
#define LOAD_GS(__seg)  (({ u16_t __tmp = (__seg); __asm__ ( "movw %0,%%gs": :"rm" (__tmp)); }))
#define LOAD_ESP(__esp)	(({ __asm__ ( "movl %0,%%esp": :"g" (__esp)); }))

#endif /* KERNEL_ARCH_X86_ASM_H */