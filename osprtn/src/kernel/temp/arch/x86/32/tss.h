#ifndef KERNEL_ARCH_X86_32_TSS_H
#define KERNEL_ARCH_X86_32_TSS_H

#if defined(CONFIG_X86_IO_FLEXPAGES)
    #define X86_X32_IOPERMBITMAP_BITS          (1 << 16)
    #define X86_X32_IOPERMBITMAP_ALIGNMENT     __attribute__((aligned(4096)));
#else
    #define X86_X32_IOPERMBITMAP_BITS 0
    #define X86_X32_IOPERMBITMAP_ALIGNMENT
#endif

#define IOPERMBITMAP_SIZE   (X86_X32_IOPERMBITMAP_BITS / 8)

typedef struct x86_x32_tss {
    u32_t	link;
    u32_t	esp0, ss0;
    u32_t	esp1, ss1;
    u32_t	esp2, ss2;
    u32_t	cr3;
    u32_t	eip, eflags;
    u32_t	eax, ecx, edx, ebx, esp, ebp, esi, edi;
    u32_t	es, cs, ss, ds, fs, gs;
    u32_t	ldt;
    u16_t	trace;
    u16_t	iopbm_offset;
    u8_t	io_bitmap[IOPERMBITMAP_SIZE] X86_X32_IOPERMBITMAP_ALIGNMENT;
    u8_t	stopper;
} x86_x32_tss_t;

INLINE void x86_x32_tss_set_esp0(x86_x32_tss_t *s, u32_t esp)
{
    s->esp0 = esp;
}

INLINE u32_t x86_x32_tss_get_esp0(x86_x32_tss_t *s)
{
    return s->esp0;
}

INLINE void x86_x32_tss_setup(x86_x32_tss_t *s, u16_t ss0)
{
    s->ss0 = ss0;
    s->iopbm_offset = (u16_t)OFFSET_OF(x86_x32_tss_t, io_bitmap);
    s->stopper = 0xff;
}

INLINE addr_t x86_x32_tss_get_io_bitmap(x86_x32_tss_t *s)
{
    return (addr_t)s->io_bitmap;
}

extern x86_x32_tss_t *tss;
#endif /* KERNEL_ARCH_X86_32_TSS_H */