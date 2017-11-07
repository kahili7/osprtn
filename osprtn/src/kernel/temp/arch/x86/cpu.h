#ifndef KERNEL_ARCH_X86_CPU_H
#define KERNEL_ARCH_X86_CPU_H

// инструкция cpuid
INLINE void x86_cpuid(word_t index, u32_t* eax, u32_t* ebx, u32_t* ecx, u32_t* edx)
{
    __asm__ ("cpuid" : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx) : "a" (index));
}

#include DIR_CPU(cpu.h)

INLINE void x86_pause()
{
    __asm__ __volatile__ ("pause");
}

// чтение из счетчиков мониторинга производительности
INLINE u64_t x86_rdpmc(const int ctrsel)
{
    u32_t eax, edx;

    __asm__ __volatile__ ("rdpmc" : "=a" (eax), "=d" (edx) : "c" (ctrsel));
    return (((u64_t)edx) << 32) | (u64_t)eax;
}

// чтение из регистра счета времени
INLINE u64_t x86_rdtsc(void)
{
    u32_t eax, edx;

    __asm__ __volatile__ ("rdtsc" : "=a" (eax), "=d" (edx));
    return (((u64_t)edx) << 32) | (u64_t)eax;
}

// чтение из особого регистра модели
INLINE u64_t x86_rdmsr(const u32_t reg)
{
    u32_t eax, edx;

    __asm__ __volatile__ ("rdmsr" : "=a" (eax), "=d" (edx) : "c" (reg));
    return (((u64_t)edx) << 32) | (u64_t)eax;
}

// записать в особый регистр модели
INLINE void x86_wrmsr(const u32_t reg, const u64_t val)
{
    __asm__ __volatile__ ("wrmsr" : : "a" ((u32_t) val), "d" ((u32_t) (val >> 32)), "c" (reg));
}

INLINE void x86_settsc(const u64_t val)
{
    x86_wrmsr(0x10, val);
}

// записать обратно и аннулировать КЭШ
INLINE void x86_wbinvd(void)
{
    __asm__ __volatile__("wbinvd\n" : : : "memory");
}

// cканирование битов вперед
INLINE int x86_lsb (word_t w) __attribute__ ((const));
INLINE int x86_lsb (word_t w)
{
    int bitnum;
    
    __asm__ ("bsf %1, %0" : "=r" (bitnum) : "rm" (w));
    return bitnum;
}

#define lsb(w) x86_lsb(w)

// обратное сканирование битов
INLINE int x86_msb (word_t w) __attribute__ ((const));
INLINE int x86_msb (word_t w)
{
    int bitnum;
    
    __asm__ ("bsr %1, %0" : "=r" (bitnum) : "rm" (w));
    return bitnum;
}

#define msb(w) x86_msb(w)

// содержит системные флаги управления, управляющие поведением и состоянием процессора
// чтение регистра CR0
INLINE word_t x86_cr0_read(void)
{
    word_t tmp;
    
    __asm__ __volatile__ ("mov %%cr0, %0\n" : "=r"(tmp));
    return tmp;
}

// установка регистра CR0
INLINE void x86_cr0_set(const word_t val)
{
    word_t tmp;
    
    __asm__ __volatile__ ("mov %%cr0, %0\n"
                          "or %1, %0\n"
                          "mov %0, %%cr0\n" : "=r"(tmp) : "ri"(val));
}

// установка маски регистра CR0
INLINE void x86_cr0_mask(const word_t val)
{
    word_t tmp;
    
    __asm__ __volatile__ ("mov %%cr0, %0\n"
                          "and %1, %0\n"
                          "mov %0, %%cr0\n" : "=r"(tmp) : "ri"(~val));
}

// содержит линейный адрес команды, вызвавшей страничное нарушение
// чтение CR2
INLINE u32_t x86_cr2_read(void)
{
    u32_t tmp;
    
    __asm__ __volatile__ ("movl %%cr2, %0\n" : "=r"(tmp));
    return tmp;
}

// запись CR2
INLINE void x86_cr2_write(const u32_t val)
{
    __asm__ __volatile__ ("movl %0, %%cr2\n" : : "r"(val));
}

// содержит физический адрес начала каталога страниц
// чтение CR3
INLINE word_t x86_cr3_read(void)
{
    word_t tmp;
    __asm__ __volatile__ ("mov %%cr3, %0\n" : "=r"(tmp));
    return tmp;
}

// запись CR3
INLINE void x86_cr3_write(const word_t val)
{
    __asm__ __volatile__ ("mov %0, %%cr3\n" : : "r"(val));
}

// обеспечивает включение/выключение поддержки самых разнообразных режимов и дополнительных возможностей процессора
// чтение CR4
INLINE word_t x86_cr4_read(void)
{
    word_t tmp;
    
    __asm__ __volatile__ ("mov  %%cr4, %0\n" : "=r"(tmp));
    return tmp;
}

// запись CR4
INLINE void x86_cr4_write(const word_t val)
{
    __asm__ __volatile__ ("mov  %0, %%cr4\n" : : "r"(val));
}

// установка регистра CR4
INLINE void x86_cr4_set(const word_t val)
{
    word_t tmp;
    
    __asm__ __volatile__ ("mov %%cr4, %0\n"
                          "or %1, %0\n"
                          "mov %0, %%cr4\n" : "=r"(tmp) : "ri"(val));
}

// установка маски регистра CR4
INLINE void x86_cr4_mask(const word_t val)
{
    word_t tmp;
    
    __asm__ __volatile__ ("mov %%cr4, %0\n"
                          "and %1, %0\n"
                          "mov %0, %%cr4\n" : "=r"(tmp) : "ri"(~val));
}

// отладочные регистры
#define X86_GET_DR(num, reg)     __asm__ __volatile__ (""#num", %0" : "=r"(reg));
#define X86_SET_DR(num, reg)     __asm__ __volatile__ ("mov %0, %%db"#num : : "r"(reg));

// чтение регистров DR%
INLINE word_t x86_dr_read(word_t dr)
{
    word_t val = 0;
    if (dr==0) X86_GET_DR(0, val);
    if (dr==1) X86_GET_DR(1, val);
    if (dr==2) X86_GET_DR(2, val);
    if (dr==3) X86_GET_DR(3, val);
    if (dr==6) X86_GET_DR(6, val);
    if (dr==7) X86_GET_DR(7, val);
    return val;
}

// запись регистров DR%
INLINE void x86_dr_write(word_t dr, word_t val)
{
    if (dr==0) X86_SET_DR(0, val);
    if (dr==1) X86_SET_DR(1, val);
    if (dr==2) X86_SET_DR(2, val);
    if (dr==3) X86_SET_DR(3, val);
    if (dr==6) X86_SET_DR(6, val);
    if (dr==7) X86_SET_DR(7, val);
}

// включить прерывания
INLINE void x86_enable_interrupts(void)
{
    __asm__ __volatile__ ("sti\n":);
}

// выключить прерывания
INLINE void x86_disable_interrupts(void)
{
    __asm__ __volatile__ ("cli\n":);
}

// засыпание компьютера
INLINE void x86_sleep(void)
{
    __asm__ __volatile__("sti\n"
                         "hlt\n"
                         "cli\n" : : : "memory");
}

// непрерывное засыпание компьютера
INLINE void x86_sleep_uninterruptible(void)
{
    __asm__ __volatile__("pushf\n\t"
                         "cli\n\t"
                         "hlt\n\t"
                         "popf\n\t" : : : "memory");
}

INLINE void x86_wait_cycles(u64_t cycles)
{
    u64_t now = x86_rdtsc();
    u64_t then = now;
    
    do 
        then = x86_rdtsc();
    while (then < now + cycles);
    
}

// сброс элемента TLB
INLINE void x86_invlpg (word_t addr)
{
    __asm__ __volatile__ ("invlpg (%0)\n" : : "r" (addr));
}
#endif /* KERNEL_ARCH_X86_CPU_H */