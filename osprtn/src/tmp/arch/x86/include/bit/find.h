#ifndef ARCH_X86_BIT_FIND_H
#define ARCH_X86_BIT_FIND_H

// найти следующий набор бит в области памяти
#ifndef find_next_bit
    extern unsigned long find_next_bit(const unsigned long *addr, unsigned long size, unsigned long offset);
#endif

// найти ближайшие сброшенные биты в области памяти
#ifndef find_next_zero_bit
    extern unsigned long find_next_zero_bit(const unsigned long *addr, unsigned long size, unsigned long offset);
#endif
    
#define find_first_bit(addr, size)          find_next_bit((addr), (size), 0)
#define find_first_zero_bit(addr, size)     find_next_zero_bit((addr), (size), 0)
#endif /* ARCH_X86_BIT_FIND_H */