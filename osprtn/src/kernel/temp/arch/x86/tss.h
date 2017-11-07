#ifndef KERNEL_ARCH_X86_TSS_H
#define KERNEL_ARCH_X86_TSS_H

#if defined(CONFIG_X86_IO_FLEXPAGES)
    #define X86_IOPERMBITMAP_BITS          (1 << 16)
    #define X86_IOPERMBITMAP_ALIGNMENT     __attribute__((aligned(4096)));
#else
    #define X86_IOPERMBITMAP_BITS 0
    #define X86_IOPERMBITMAP_ALIGNMENT
#endif

#define IOPERMBITMAP_SIZE		(X86_IOPERMBITMAP_BITS / 8)

typedef struct x86_tss {
    u32_t	reserved0;
    u64_t	sp[3] __attribute__((packed));	      
    u64_t	reserved1;
    u64_t	ist[7] __attribute__((packed));	      
    u64_t	reserved2;
    u16_t	reserved3;
    u16_t	iopbm_offset;    
    u8_t	io_bitmap[IOPERMBITMAP_SIZE] X86_IOPERMBITMAP_ALIGNMENT;
    u8_t	stopper;
} x86_tss_t __attribute__((packed));

INLINE void x86_tss_setup(x86_tss_t *s, u16_t ss0)
{
    s->iopbm_offset = (u16_t)OFFSET64_OF(x86_tss_t, io_bitmap);
    s->stopper = 0xff;
}

INLINE void x86_tss_set_sp0(x86_tss_t *s, u64_t sp0)
{
    s->sp[0] = sp0;
}

INLINE u64_t x86_tss_get_sp0(x86_tss_t *s)
{
    return s->sp[0];
}

INLINE addr_t x86_tss_get_io_bitmap(x86_tss_t *s)
{
    return (addr_t) s->io_bitmap;
}

extern x86_tss_t tss;
#endif /* KERNEL_ARCH_X86_TSS_H */