#ifndef KERNEL_ARCH_X86_IOPORT_H
#define KERNEL_ARCH_X86_IOPORT_H

// запись в порта
INLINE void out_u8(const u16_t port, const u8_t val)
{
    __asm__ __volatile__("outb  %1, %0\n" : : "dN"(port), "a"(val));
}

// чтение из порта
INLINE u8_t in_u8(const u16_t port)
{
    u8_t tmp;

    __asm__ __volatile__("inb %1, %0\n" : "=a"(tmp) : "dN"(port));
    return tmp;
}

// запись в порта
INLINE void out_u16(const u16_t port, const u16_t val)
{
    __asm__ __volatile__("outw  %1, %0\n" : : "dN"(port), "a"(val));
}

// чтение из порта
INLINE u16_t in_u16(const u16_t port)
{
    u16_t tmp;

    __asm__ __volatile__("inw %1, %0\n" : "=a"(tmp) : "dN"(port));
    return tmp;
}

// запись в порта
INLINE void out_u32(const u16_t port, const u32_t val)
{
    __asm__ __volatile__("outl  %1, %0\n" : : "dN"(port), "a"(val));
}

// чтение из порта
INLINE u32_t in_u32(const u16_t port)
{
    u32_t tmp;

    __asm__ __volatile__("inl %1, %0\n" : "=a"(tmp) : "dN"(port));
    return tmp;
}
#endif /* KERNEL_ARCH_X86_IOPORT_H */
