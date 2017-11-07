#ifndef GENERIC_BIT_BITMAP_H
#define GENERIC_BIT_BITMAP_H

#include <types.h>
#include <bit/bitops.h>
#include <string.h>
#include <kernel.h>
/*
 * функции для работы с бит-массивами 
 */

#define BITMAP_FIRST_WORD_MASK(start)   (~0UL << ((start) % BITS_PER_LONG))
#define BITMAP_LAST_WORD_MASK(nbits)    (((nbits) % BITS_PER_LONG) ? (1UL<<((nbits) % BITS_PER_LONG))-1 : ~0UL)
#define small_const_nbits(nbits)        (__builtin_constant_p(nbits) && (nbits) <= BITS_PER_LONG)

// проверка массива бит на равенство 0
extern int __bitmap_empty(const unsigned long *bitmap, int bits);

static inline int bitmap_empty(const unsigned long *src, int nbits)
{
    if (small_const_nbits(nbits))
        return !(*src & BITMAP_LAST_WORD_MASK(nbits));
    else
        return __bitmap_empty(src, nbits);
}

// проверка массива бит на равенство 1
extern int __bitmap_full(const unsigned long *bitmap, int bits);

static inline int bitmap_full(const unsigned long *src, int nbits)
{
    if (small_const_nbits(nbits))
        return ! (~(*src) & BITMAP_LAST_WORD_MASK(nbits));
    else
        return __bitmap_full(src, nbits);
}

// проверка массива двух массивов на равенство
extern int __bitmap_equal(const unsigned long *bitmap1, const unsigned long *bitmap2, int bits);

static inline int bitmap_equal(const unsigned long *src1, const unsigned long *src2, int nbits)
{
    if (small_const_nbits(nbits))
        return ! ((*src1 ^ *src2) & BITMAP_LAST_WORD_MASK(nbits));
    else
        return __bitmap_equal(src1, src2, nbits);
}

// объединение массивов
extern void __bitmap_complement(unsigned long *dst, const unsigned long *src, int bits);

static inline void bitmap_complement(unsigned long *dst, const unsigned long *src, int nbits)
{
    if (small_const_nbits(nbits))
        *dst = ~(*src) & BITMAP_LAST_WORD_MASK(nbits);
    else
        __bitmap_complement(dst, src, nbits);
}

// сдвиг вправо
extern void __bitmap_shift_right(unsigned long *dst, const unsigned long *src, int shift, int bits);

static inline void bitmap_shift_right(unsigned long *dst, const unsigned long *src, int n, int nbits)
{
    if (small_const_nbits(nbits))
        *dst = *src >> n;
    else
        __bitmap_shift_right(dst, src, n, nbits);
}

// сдвиг влево
extern void __bitmap_shift_left(unsigned long *dst, const unsigned long *src, int shift, int bits);

static inline void bitmap_shift_left(unsigned long *dst, const unsigned long *src, int n, int nbits)
{
    if (small_const_nbits(nbits))
        *dst = (*src << n) & BITMAP_LAST_WORD_MASK(nbits);
    else
        __bitmap_shift_left(dst, src, n, nbits);
}
#endif /* GENERIC_BIT_BITMAP_H */