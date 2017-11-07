#ifndef GENERIC_BIT_BITOPS_H
#define GENERIC_BIT_BITOPS_H

#include <types.h>

#ifdef	__KERNEL__
    #define DIV_ROUND_UP(n, d)  (((n) + (d) - 1) / (d))

    #define BIT(nr)             (1UL << (nr))
    #define BIT_ULL(nr)		(1ULL << (nr))
    #define BIT_MASK(nr)        (1UL << ((nr) % BITS_PER_LONG))
    #define BIT_WORD(nr)        ((nr) / BITS_PER_LONG)
    #define BIT_ULL_MASK(nr)	(1ULL << ((nr) % BITS_PER_LONG_LONG))
    #define BIT_ULL_WORD(nr)	((nr) / BITS_PER_LONG_LONG)
    #define BITS_PER_BYTE	8
    #define BITS_TO_LONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#endif

#include _SOS_CPU_HDR_DIR_(bit/bitops.h)

// 64 bit
static inline _Uint64t rol64(_Uint64t word, unsigned int shift)
{
    return (word << shift) | (word >> (64 - shift));
}

static inline _Uint64t ror64(_Uint64t word, unsigned int shift)
{
    return (word >> shift) | (word << (64 - shift));
}

// 32 bit
static inline _Uint32t rol32(_Uint32t word, unsigned int shift)
{
    return (word << shift) | (word >> (32 - shift));
}

static inline _Uint32t ror32(_Uint32t word, unsigned int shift)
{
    return (word >> shift) | (word << (32 - shift));
}

// 16 bit
static inline _Uint16t rol16(_Uint16t word, unsigned int shift)
{
    return (word << shift) | (word >> (16 - shift));
}

static inline _Uint16t ror16(_Uint16t word, unsigned int shift)
{
    return (word >> shift) | (word << (16 - shift));
}

// 8 bit
static inline _Uint8t rol8(_Uint8t word, unsigned int shift)
{
    return (word << shift) | (word >> (8 - shift));
}

static inline _Uint8t ror8(_Uint8t word, unsigned int shift)
{
    return (word >> shift) | (word << (8 - shift));
}

// знаковые 32 bit
static inline _Int32t sign_extend32(_Uint32t value, int index)
{
    _Uint8t shift = 31 - index;
    
    return (_Int32t)(value << shift) >> shift;
}
#endif /* GENERIC_BIT_BITOPS_H */