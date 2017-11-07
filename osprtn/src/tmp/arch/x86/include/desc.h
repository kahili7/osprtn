#ifndef ARCH_X86_DESC_H
#define ARCH_X86_DESC_H

#include "desc-defs.h"
#include "ldt.h"
#include "segment.h"

#include <smp.h>
#include <mem.h>
#include <percpu.h>

struct x86_desc_ptr_struct idt_desc;
gate_desc idt_table[];

struct x86_desc_ptr_struct debug_idt_desc;
gate_desc debug_idt_table[];

struct x86_gdt_page_struct {
    struct x86_desc_struct gdt[GDT_ENTRIES];
}__attribute__((aligned(PAGE_SIZE)));

// выравниваем переменную на границу страницы с соответствующим типом
DECLARE_PER_CPU_PAGE_ALIGNED(struct x86_gdt_page_struct, gdt_page); 

// возвращение дескриптора GDT из выбранного процессора
static inline struct x86_desc_struct *get_cpu_gdt_table(unsigned int cpu)
{
	return per_cpu(gdt_page, cpu).gdt;
}

#define PTR_LOW(x) ((unsigned long long)(x) & 0xFFFF)
#define PTR_MIDDLE(x) (((unsigned long long)(x) >> 16) & 0xFFFF)
#define PTR_HIGH(x) ((unsigned long long)(x) >> 32)

static inline void fill_ldt(struct x86_desc_struct *desc, const struct x86_user_desc *info)
{
    desc->limit0    = info->limit & 0x0ffff;
    desc->base0     = (info->base_addr & 0x0000ffff);
    desc->base1     = (info->base_addr & 0x00ff0000) >> 16;
    
    desc->type      = (info->read_exec_only ^ 1) << 1;
    desc->type      |= info->contents << 2;
    
    desc->s         = 1;
    desc->dpl       = 0x3;
    desc->p         = info->seg_not_present ^ 1;
    desc->limit1    = (info->limit & 0xf0000) >> 16;
    desc->avl       = info->useable;
    desc->d         = info->seg_32bit;
    desc->g         = info->limit_in_pages;
    desc->base2     = (info->base_addr & 0xff000000) >> 24;
    desc->l         = 0;
}

#ifdef CONFIG_X86_64
    static inline void pack_gate(gate_desc *gate, unsigned type, unsigned long func, unsigned dpl, unsigned ist, unsigned seg)
    {
        gate->offset_low	= PTR_LOW(func);
        gate->segment           = __KERNEL_CS;
        gate->ist		= ist;
        gate->p                 = 1;
        gate->dpl		= dpl;
        gate->zero0		= 0;
        gate->zero1		= 0;
        gate->type		= type;
        gate->offset_middle	= PTR_MIDDLE(func);
        gate->offset_high	= PTR_HIGH(func);
    }
#else
    static inline void pack_gate(gate_desc *gate, unsigned char type, unsigned long base, unsigned dpl, unsigned flags, unsigned short seg)
    {
        gate->a = (seg << 16) | (base & 0xffff);
        gate->b = (base & 0xffff0000) | (((0x80 | type | (dpl << 5)) & 0xff) << 8);
    }
#endif

static inline void pack_descriptor(struct x86_desc_struct *desc, unsigned long base, unsigned long limit, unsigned char type, unsigned char flags)
{
    desc->a = ((base & 0xffff) << 16) | (limit & 0xffff);
    desc->b = (base & 0xff000000) | ((base & 0xff0000) >> 16) | (limit & 0x000f0000) | ((type & 0xff) << 8) | ((flags & 0xf) << 20);
    desc->p = 1;
}

// загрузка регистра ldtr
#define load_ldt(ldt)   asm volatile("lldt %0"::"m" (ldt))

// сохранения регистра ldtr
#define store_ldt(ldt)  asm volatile("sldt %0" : "=m"(ldt))

// загрузка регистра задачи
#define load_tr(tr)     asm volatile("ltr %0"::"m" (tr))

static inline void native_load_tr(void)
{
	asm volatile("ltr %w0"::"q" (GDT_ENTRY_TSS*8));
}

// сохранение регистра задачи
#define store_tr(tr)    (tr = native_store_tr())

static inline unsigned long native_store_tr(void)
{
	unsigned long tr;

	asm volatile("str %0":"=r" (tr));

	return tr;
}

// загрузка регистра gdtr
#define load_gdt(dtr)   native_load_gdt(dtr)

static inline void native_load_gdt(const struct x86_desc_ptr_struct *dtr)
{
	asm volatile("lgdt %0"::"m" (*dtr));
}

// сохранение регистра gdtr
#define store_gdt(dtr)  native_store_gdt(dtr)

static inline void native_store_gdt(struct x86_desc_ptr_struct *dtr)
{
	asm volatile("sgdt %0":"=m" (*dtr));
}

// загрузка регистра idtr
#define load_idt(dtr)   native_load_idt(dtr)

static inline void native_load_idt(const struct x86_desc_ptr_struct *dtr)
{
	asm volatile("lidt %0"::"m" (*dtr));
}

// сохранение регистра idtr
#define store_idt(dtr)	native_store_idt(dtr)

static inline void native_store_idt(struct x86_desc_ptr_struct *dtr)
{
	asm volatile("sidt %0":"=m" (*dtr));
}

// установка дескриптора задачи
static inline void set_tss_ldt_descriptor(void *d, unsigned long addr, unsigned type, unsigned size)
{
#ifdef CONFIG_X86_64
    struct x86_ldt_tss_struct64 *desc = d;

    memset(desc, 0, sizeof(*desc));

    desc->limit0    = size & 0xFFFF;
    desc->base0     = PTR_LOW(addr);
    desc->base1     = PTR_MIDDLE(addr) & 0xFF;
    desc->type      = type;
    desc->p         = 1;
    desc->limit1    = (size >> 16) & 0xF;
    desc->base2     = (PTR_MIDDLE(addr) >> 8) & 0xFF;
    desc->base3     = PTR_HIGH(addr);
#else
    pack_descriptor((struct x86_desc_struct *)d, addr, size, 0x80 | type, 0);
#endif
}

// вставить запись (дескриптор LDT || TSS) в таблицу GDT
#define write_gdt_entry(dt, entry, desc, type)	native_write_gdt_entry(dt, entry, desc, type)

static inline void native_write_gdt_entry(struct x86_desc_struct *gdt, int entry, const void *desc, int type)
{
    unsigned int size;

    switch (type) 
    {
        case DESC_TSS:	size = sizeof(tss_desc);break;
        case DESC_LDT:	size = sizeof(ldt_desc);break;
        default:	size = sizeof(*gdt);break;
    }

    memcpy(&gdt[entry], desc, size);
}

// вставить запись (дескриптор GATE) в таблицу IDT
#define write_idt_entry(dt, entry, g)   native_write_idt_entry(dt, entry, g)

static inline void native_write_idt_entry(gate_desc *idt, int entry, const gate_desc *gate)
{
	memcpy(&idt[entry], gate, sizeof(*gate));
}

// вставить запись (дескриптор) в таблицу LDT
#define write_ldt_entry(dt, entry, desc)    native_write_ldt_entry(dt, entry, desc)

static inline void native_write_ldt_entry(struct x86_desc_struct *ldt, int entry, const void *desc)
{
	memcpy(&ldt[entry], desc, 8);
}

// пустая запись в LDT
#define _LDT_empty(info)				\
	((info)->base_addr		== 0	&&	\
	 (info)->limit			== 0	&&	\
	 (info)->contents		== 0	&&	\
	 (info)->read_exec_only		== 1	&&	\
	 (info)->seg_32bit		== 0	&&	\
	 (info)->limit_in_pages		== 0	&&	\
	 (info)->seg_not_present	== 1	&&	\
	 (info)->useable		== 0)

#ifdef CONFIG_X86_64
    #define LDT_empty(info) (_LDT_empty(info) && ((info)->lm == 0))
#else
    #define LDT_empty(info) (_LDT_empty(info))
#endif


#define load_tr_desc()  native_load_tr_desc()


// установка TSS дескриптора
#define set_tss_desc(cpu, addr) __set_tss_desc(cpu, GDT_ENTRY_TSS, addr) 

static inline void __set_tss_desc(unsigned cpu, unsigned int entry, void *addr)
{
    struct x86_desc_struct *d = get_cpu_gdt_table(cpu);
    tss_desc tss;

    set_tss_ldt_descriptor(&tss, (unsigned long)addr, DESC_TSS, IO_BITMAP_OFFSET + IO_BITMAP_BYTES + sizeof(unsigned long) - 1);
    write_gdt_entry(d, entry, &tss, DESC_TSS);
}

// установка LDT как запись в таблицу GDT
#define set_ldt native_set_ldt

static inline void native_set_ldt(const void *addr, unsigned int entries)
{
    // likely
    if(entries == 0)
    {
        asm volatile("lldt %w0"::"q" (0));
    }
    else
    {
        unsigned cpu = smp_processor_id();
        ldt_desc ldt;

        set_tss_ldt_descriptor(&ldt, (unsigned long)addr, DESC_LDT, entries * LDT_ENTRY_SIZE - 1);
        write_gdt_entry(get_cpu_gdt_table(cpu), GDT_ENTRY_LDT, &ldt, DESC_LDT);
        asm volatile("lldt %w0"::"q" (GDT_ENTRY_LDT*8));
    }
}

// загрузка TLS в таблицу GDT
#define load_tls(t, cpu)    native_load_tls(t, cpu) 

static inline void native_load_tls(struct thread_struct *t, unsigned int cpu)
{
    unsigned int i;
    struct x86_desc_struct *gdt = get_cpu_gdt_table(cpu);

    for(i = 0; i < GDT_ENTRY_TLS_ENTRIES; i++)
    {
        gdt[GDT_ENTRY_TLS_MIN + i] = t->tls_array[i];
    }
}

// возврат базы дескриптора
static inline unsigned long get_desc_base(const struct x86_desc_struct *desc)
{
    return (unsigned)(desc->base0 | ((desc->base1) << 16) | ((desc->base2) << 24));
}

// установка базы дескриптора
static inline void set_desc_base(struct x86_desc_struct *desc, unsigned long base)
{
    desc->base0 = base & 0xffff;
    desc->base1 = (base >> 16) & 0xff;
    desc->base2 = (base >> 24) & 0xff;
}

// возврат смещения дескриптора
static inline unsigned long get_desc_limit(const struct x86_desc_struct *desc)
{
	return desc->limit0 | (desc->limit1 << 16);
}

// установка смещения дескриптора
static inline void set_desc_limit(struct x86_desc_struct *desc, unsigned long limit)
{
	desc->limit0 = limit & 0xffff;
	desc->limit1 = (limit >> 16) & 0xf;
}

#endif /* ARCH_X86_DESC_H */