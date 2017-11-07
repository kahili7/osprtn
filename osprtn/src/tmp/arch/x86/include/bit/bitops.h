#ifndef ARCH_X86_BIT_BITOPS_H
#define ARCH_X86_BIT_BITOPS_H

#include _SOS_CPU_HDR_DIR_(sync/barrier.h)

// чтение и заапись операнда из памяти
#define BITOP_ADDR(x)       "+m" (*(volatile long *) (x))
#define ADDR                BITOP_ADDR(addr)

// проверяет является ли переменная - константой
#define IS_IMMEDIATE(nr)    (__builtin_constant_p(nr))

#define CONST_MASK_ADDR(nr, addr)   BITOP_ADDR((void *)(addr) + ((nr) >> 3))
#define CONST_MASK(nr)              (1 << ((nr) & 7))

// атомарно устанавливается бит в памяти
static __always_inline void set_bit(unsigned int nr, volatile unsigned long *addr)
{
    if (IS_IMMEDIATE(nr))
    {
        asm volatile(LOCK_PREFIX "orb %1,%0"
            : CONST_MASK_ADDR(nr, addr)
            : "iq" ((_Uint8t)CONST_MASK(nr)) : "memory");
    } 
    else
    {
        asm volatile(LOCK_PREFIX "bts %1,%0" : BITOP_ADDR(addr) : "Ir" (nr) : "memory");
    }
}

// установка бита
static inline void __set_bit(int nr, volatile unsigned long *addr)
{
    asm volatile("bts %1,%0" : ADDR : "Ir" (nr) : "memory");
}

// атомарно очистить бит в памяти
static __always_inline void clear_bit(int nr, volatile unsigned long *addr)
{
    if (IS_IMMEDIATE(nr))
    {
        asm volatile(LOCK_PREFIX "andb %1,%0"
            : CONST_MASK_ADDR(nr, addr)
            : "iq" ((_Uint8t)~CONST_MASK(nr)));
    }
    else
    {
        asm volatile(LOCK_PREFIX "btr %1,%0" : BITOP_ADDR(addr) : "Ir" (nr));
    }
}

// очистка бита
static inline void __clear_bit(int nr, volatile unsigned long *addr)
{
    asm volatile("btr %1,%0" : ADDR : "Ir" (nr));
}

// атомарно очистить бит в памяти, барьер компилятора
static inline void clear_bit_unlock(unsigned nr, volatile unsigned long *addr)
{
    barrier();
    clear_bit(nr, addr);
}

// очистка бита, барьер компилятора
static inline void __clear_bit_unlock(unsigned nr, volatile unsigned long *addr)
{
    barrier();
    __clear_bit(nr, addr);
}

// атомарно изменить бит в памяти
static inline void change_bit(int nr, volatile unsigned long *addr)
{
    if (IS_IMMEDIATE(nr))
    {
        asm volatile(LOCK_PREFIX "xorb %1,%0"
            : CONST_MASK_ADDR(nr, addr)
            : "iq" ((_Uint8t)CONST_MASK(nr)));
    }
    else
    {
        asm volatile(LOCK_PREFIX "btc %1,%0" : BITOP_ADDR(addr) : "Ir" (nr));
    }
}

// изменение бита
static inline void __change_bit(int nr, volatile unsigned long *addr)
{
    asm volatile("btc %1,%0" : ADDR : "Ir" (nr));
}

// атомарно изменить бит в памяти, барьер компилятора
static inline void change_bit_unlock(unsigned nr, volatile unsigned long *addr)
{
    barrier();
    change_bit(nr, addr);
}

// изменение бита, барьер компилятора
static inline void __change_bit_unlock(unsigned nr, volatile unsigned long *addr)
{
    barrier();
    __change_bit(nr, addr);
}

// атомарно установить бит и вернуть его старое значение
static inline int test_and_set_bit(int nr, volatile unsigned long *addr)
{
    int oldbit;

    asm volatile(LOCK_PREFIX "bts %2,%1\n\t"
        "sbb %0,%0" : "=r" (oldbit), ADDR : "Ir" (nr) : "memory");

    return oldbit;
}

static __always_inline int test_and_set_bit_lock(int nr, volatile unsigned long *addr)
{
    return test_and_set_bit(nr, addr);
}

// установить бит и вернуть его старое значение (обычное)
static inline int __test_and_set_bit(int nr, volatile unsigned long *addr)
{
    int oldbit;

    asm volatile("bts %2,%1\n\t"
        "sbb %0,%0" : "=r" (oldbit), ADDR : "Ir" (nr));
    
    return oldbit;
}

// атомарно сбросить бит и вернуть его старое значение
static inline int test_and_clear_bit(int nr, volatile unsigned long *addr)
{
    int oldbit;

    asm volatile(LOCK_PREFIX "btr %2,%1\n\t"
        "sbb %0,%0" : "=r" (oldbit), ADDR : "Ir" (nr) : "memory");

    return oldbit;
}

// сбросить бит и вернуть его старое значение (обычное)
static inline int __test_and_clear_bit(int nr, volatile unsigned long *addr)
{
    int oldbit;

    asm volatile("btr %2,%1\n\t"
        "sbb %0,%0" : "=r" (oldbit), ADDR : "Ir" (nr));
    
    return oldbit;
}

// атомарно изменить бит и вернуть его старое значение
static inline int test_and_change_bit(int nr, volatile unsigned long *addr)
{
    int oldbit;

    asm volatile(LOCK_PREFIX "btc %2,%1\n\t"
        "sbb %0,%0" : "=r" (oldbit), ADDR : "Ir" (nr) : "memory");

    return oldbit;
}

// изменить бит и вернуть его старое значение (обычное)
static inline int __test_and_change_bit(int nr, volatile unsigned long *addr)
{
    int oldbit;

    asm volatile("btc %2,%1\n\t"
        "sbb %0,%0" : "=r" (oldbit), ADDR : "Ir" (nr) : "memory");

    return oldbit;
}

// протестировать текущий бит
static __always_inline int constant_test_bit(unsigned int nr, const volatile unsigned long *addr)
{
    return ((1UL << (nr % BITS_PER_LONG)) & (addr[nr / BITS_PER_LONG])) != 0;
}

// проверка состояния бита
static inline int variable_test_bit(int nr, volatile const unsigned long *addr)
{
    int oldbit;

    asm volatile("bt %2,%1\n\t"
        "sbb %0,%0" : "=r" (oldbit) : "m" (*(unsigned long *)addr), "Ir" (nr));

    return oldbit;
}

// проверка бита
#define test_bit(nr, addr)  (__builtin_constant_p((nr)) ? constant_test_bit((nr), (addr)) : variable_test_bit((nr), (addr)))

#include _SOS_CPU_HDR_DIR_(bit/find.h)
#endif /* ARCH_X86_BIT_BITOPS_H */