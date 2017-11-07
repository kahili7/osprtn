#ifndef KERNEL_GENERIC_TYPES_H
#define KERNEL_GENERIC_TYPES_H

#if !defined(ASSEMBLY)
    #include DIR_ARCH(types.h)

    #if defined(CONFIG_IS_32BIT)
        #define SIZE_T unsigned int
    #else
        #define SIZE_T long unsigned int
    #endif

    typedef SIZE_T  size_t;
    
    // тип для хранения адреса
    typedef void*   addr_t;
    
    // тип используется для конвертации адреса в INT
    typedef word_t  addr_word_t;
    
    // добавить смещение к адресу
    INLINE addr_t addr_offset(addr_t addr, word_t off)
    {
        return (addr_t)((word_t)addr + off);
    }
    
    // применение маски к адресу
    INLINE addr_t addr_mask (addr_t addr, word_t mask)
    {
        return (addr_t) ((word_t) addr & mask);
    }
    
    // выравнивание вниз
    INLINE addr_t addr_align (addr_t addr, word_t align)
    {
        return addr_mask(addr, ~(align - 1));
    }
    
    // выравнивание вверх
    INLINE addr_t addr_align_up (addr_t addr, word_t align)
    {
        return addr_mask(addr_offset(addr, align - 1), ~(align - 1));
    }
    
    #ifndef NULL
        #define NULL 0
    #endif

    #define OFFSET_OF(t, f) (size_t)(&((t *)0)->f)
    #define OFFSET64_OF(t, f) (u64_t)(&((t *)0)->f)
#endif
#endif /* KERNEL_GENERIC_TYPES_H */