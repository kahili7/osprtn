#define __KERNEL__
#include <export.h>
#include <thread-info.h>
#include <string.h>
#include <bit/bitmap.h>
#include <bit/bitops.h>

// проверка массива бит на равенство 0
int __bitmap_empty(const unsigned long *bitmap, int bits)
{
    int k, lim = bits / BITS_PER_LONG;
    
    for (k = 0; k < lim; ++k)
    {
        if (bitmap[k]) return 0;

        if (bits % BITS_PER_LONG)
            if (bitmap[k] & BITMAP_LAST_WORD_MASK(bits))
                return 0;
    }
    
    return 1;
}
EXPORT_SYMBOL(__bitmap_empty);

int __bitmap_full(const unsigned long *bitmap, int bits)
{
    int k, lim = bits / BITS_PER_LONG;
    
    for (k = 0; k < lim; ++k)
    {
        if (~bitmap[k]) return 0;

        if (bits % BITS_PER_LONG)
            if (~bitmap[k] & BITMAP_LAST_WORD_MASK(bits))
                return 0;
    }
    
    return 1;
}
EXPORT_SYMBOL(__bitmap_full);

int __bitmap_equal(const unsigned long *bitmap1, const unsigned long *bitmap2, int bits)
{
    int k, lim = bits / BITS_PER_LONG;
    
    for (k = 0; k < lim; ++k)
    {
        if (bitmap1[k] != bitmap2[k]) return 0;

        if (bits % BITS_PER_LONG)
            if ((bitmap1[k] ^ bitmap2[k]) & BITMAP_LAST_WORD_MASK(bits))
                return 0;
    }
    
    return 1;
}
EXPORT_SYMBOL(__bitmap_equal);

void __bitmap_complement(unsigned long *dst, const unsigned long *src, int bits)
{
    int k, lim = bits / BITS_PER_LONG;
    
    for (k = 0; k < lim; ++k)
    {
        dst[k] = ~src[k];

        if (bits % BITS_PER_LONG)
            dst[k] = ~src[k] & BITMAP_LAST_WORD_MASK(bits);
    }
}
EXPORT_SYMBOL(__bitmap_complement);

void __bitmap_shift_right(unsigned long *dst, const unsigned long *src, int shift, int bits)
{
    int k;
    int lim = BITS_TO_LONGS(bits);
    int left = bits % BITS_PER_LONG;
    int off = shift / BITS_PER_LONG;
    int rem = shift % BITS_PER_LONG;
    unsigned long mask = (1UL << left) - 1;
    
    for (k = 0; off + k < lim; ++k)
    {
        unsigned long upper, lower;

        if (!rem || off + k + 1 >= lim) upper = 0;
        else
        {
            upper = src[off + k + 1];
            
            if (off + k + 1 == lim - 1 && left) upper &= mask;
        }
        
        lower = src[off + k];
        
        if (left && off + k == lim - 1) lower &= mask;
        
        dst[k] = upper << (BITS_PER_LONG - rem) | lower >> rem;
        
        if (left && k == lim - 1) dst[k] &= mask;
    }
    
    if (off) memset(&dst[lim - off], 0, off * sizeof(unsigned long));
}
EXPORT_SYMBOL(__bitmap_shift_right);

void __bitmap_shift_left(unsigned long *dst, const unsigned long *src, int shift, int bits)
{
    int k;
    int lim = BITS_TO_LONGS(bits);
    int left = bits % BITS_PER_LONG;
    int off = shift / BITS_PER_LONG;
    int rem = shift % BITS_PER_LONG;
    
    for (k = lim - off - 1; k >= 0; --k)
    {
        unsigned long upper, lower;
        
        if (rem && k > 0) lower = src[k - 1];
        else lower = 0;
        
        upper = src[k];
        
        if (left && k == lim - 1) upper &= (1UL << left) - 1;
        
        dst[k + off] = lower  >> (BITS_PER_LONG - rem) | upper << rem;
        
        if (left && k + off == lim - 1) dst[k + off] &= (1UL << left) - 1;
    }
    
    if (off) memset(dst, 0, off*sizeof(unsigned long));
}
EXPORT_SYMBOL(__bitmap_shift_left);