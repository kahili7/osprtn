#ifndef KERNEL_ARCH_X86_32_SEGDESC_H
#define KERNEL_ARCH_X86_32_SEGDESC_H

typedef enum x86_segtype
{
    code = 0xb,
    data = 0x3,
    tss  = 0x9
} x86_segtype_e;

// дескриптор сегмента
struct x86_segdesc_t { 
    union {
        u32_t raw[2];
        
        struct {
            u32_t limit_low	: 16;
            u32_t base_low	: 24;
            u32_t type		:  4;
            u32_t s		:  1;
            u32_t dpl		:  2;
            u32_t p		:  1;
            u32_t limit_high	:  4;
            u32_t avl		:  2;
            u32_t d		:  1;
            u32_t g		:  1;
            u32_t base_high	:  8;
        } d __attribute__((packed));
    } x;
} __attribute__((packed));

#define x86_segdesc_get_base(s) ((s).x.d.base_high << 24 | (s).x.d.base_low)

// установка сигмента приложения
INLINE void x86_segdesc_set_seg(struct x86_segdesc_t *desc, u32_t base, u32_t limit, int dpl, x86_segtype_e type)
{
    if (limit > (1 << 20)) 
    {
	desc->x.d.limit_low  = (limit >> 12) & 0xFFFF;
	desc->x.d.limit_high = (limit >> 28) & 0xF;
	desc->x.d.g = 1;	/* 4K granularity */
    }
    else
    {
	desc->x.d.limit_low  =  limit & 0xFFFF;
	desc->x.d.limit_high =  limit >> 16;
	desc->x.d.g = 0;	/* 1B granularity */
    }

    desc->x.d.base_low   = base & 0xFFFFFF;
    desc->x.d.base_high  = (base >> 24) & 0xFF;
    desc->x.d.type = type;
    desc->x.d.dpl = dpl;
    
    desc->x.d.p = 1;	/* присутствие сегментам в памяти */
    desc->x.d.d = 1;	/* 32-bit сегмент */
    desc->x.d.s = 1;	/* программный сегмент */
    
    /* unused fields */
    desc->x.d.avl = 0;
}

INLINE void x86_segdesc_set_sys(struct x86_segdesc_t *desc, u32_t base, u32_t limit, int dpl, x86_segtype_e type)
{
    desc->x.d.limit_low  = limit & 0xFFFF;
    desc->x.d.limit_high = limit >> 16;
    desc->x.d.base_low   = base & 0xFFFFFF;
    desc->x.d.base_high  = (base >> 24) & 0xFF;
    desc->x.d.type = type;
    desc->x.d.dpl = dpl;

    desc->x.d.p = 1;	/* присутствие сегментам в памяти */
    desc->x.d.g = 0;	/* размер в байтах*/
    desc->x.d.d = 0;	/* 16-bit сегмент */
    desc->x.d.s = 0;	/* non-system segment */
    
    /* unused fields */
    desc->x.d.avl = 0;
}

typedef enum x86_idtdesc_type
{
    interrupt = 6,
    trap = 7
} x86_idtdesc_type_e;

// дескриптор прерывания
typedef struct x86_idtdesc {
    union {
        u32_t raw[2];

        struct {
            u32_t offset_low	: 16;
            u32_t sel		: 16;
            u32_t res0		:  8;
            u32_t type		:  3;
            u32_t d		:  1;
            u32_t res1		:  1;
            u32_t dpl		:  2;
            u32_t p		:  1;
            u32_t offset_high	: 16;
        } d;
    } x;
} x86_idtdesc_t;

INLINE void x86_idtdesc_set(x86_idtdesc_t *desc, u16_t segsel, void (*address)(), int dpl, x86_idtdesc_type_e type)
{
    desc->x.d.offset_low  = ((u32_t) address) & 0xFFFF;
    desc->x.d.offset_high = ((u32_t) address >> 16) & 0xFFFF;
    desc->x.d.sel = segsel;
    desc->x.d.dpl = dpl;
    desc->x.d.type = type;
    
    desc->x.d.p = 1;	/* присутствие сегментам в памяти*/
    desc->x.d.d = 1;	/* 32-bit сегмент */

    desc->x.d.res0 = desc->x.d.res1 = 0;
}
#endif /* KERNEL_ARCH_X86_32_SEGDESC_H */