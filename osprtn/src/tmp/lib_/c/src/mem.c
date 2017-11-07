#include <mem.h>
#include <stdint.h>

// заполнить блок памяти с постоянным значением
void *memset(void *dest, int b, size_t n)
{
    char *pb;
    unsigned long *pw;
    size_t word_size;
    size_t n_words;
    unsigned long pattern;
    size_t i;
    size_t fill;

    word_size = sizeof(unsigned long);
    fill = word_size - ((uintptr_t)dest & (word_size - 1));
    
    if (fill > n) fill = n;

    pb = dest;
    i = fill;
    
    while (i-- != 0)
    {
        *pb++ = b;
    }
    
    n -= fill;
    
    if (n == 0) return dest;

    n_words = n / word_size;
    n = n % word_size;
    pw = (unsigned long *)pb;
    pattern = 0;
    i = word_size;
    
    while (i-- != 0)
    {
        pattern = (pattern << 8) | (uint8_t) b;
    }

    i = n_words;
    
    while (i-- != 0)
    {
        *pw++ = pattern;
    }
    
    pb = (char *) pw;
    i = n;
    
    while (i-- != 0)
    {
        *pb++ = b;
    }
    
    return dest;
} 

struct along {
    unsigned long n;
} __attribute__((packed));

static void *unaligned_memcpy(void *dst, const void *src, size_t n)
{
    size_t i, j;
    struct along *adst = dst;
    const struct along *asrc = src;

    for (i = 0; i < n / sizeof(unsigned long); i++)
        adst[i].n = asrc[i].n;

    for (j = 0; j < n % sizeof(unsigned long); j++)
        ((unsigned char *) (((unsigned long *)dst) + i))[j] = ((unsigned char *) (((unsigned long *)src) + i))[j];

    return (char *)dst;
}

void *memcpy(void *dst, const void *src, size_t n)
{
    size_t i;
    size_t mod, fill;
    size_t word_size;
    size_t n_words;

    const unsigned long *srcw;
    unsigned long *dstw;
    const uint8_t *srcb;
    uint8_t *dstb;

    word_size = sizeof(unsigned long);

    if (((uintptr_t)dst & (word_size - 1)) != ((uintptr_t)src & (word_size - 1)))
    {
        return unaligned_memcpy(dst, src, n);
    }

    mod = (uintptr_t)dst & (word_size - 1);
    fill = word_size - mod;
    
    if (fill > n) fill = n;

    srcb = src;
    dstb = dst;
    i = fill;
    
    while (i-- != 0)
    {
        *dstb++ = *srcb++;
    }

    n -= fill;
    
    if (n == 0) return dst;

    dstw = (unsigned long *)dstb;
    srcw = (const unsigned long *)srcb;

    n_words = n / word_size;	/* Number of whole words to copy. */
    n -= n_words * word_size;	/* Remaining bytes at the end. */
    i = n_words;
    
    while (i-- != 0)
    {
        *dstw++ = *srcw++;
    }

    srcb = (const uint8_t *)srcw;
    dstb = (uint8_t *)dstw;
    i = n;
    
    while (i-- != 0)
    {
        *dstb++ = *srcb++;
    }
    
    return dst;
}

void *memmove(void *dst, const void *src, size_t n)
{
    const uint8_t *sp;
    uint8_t *dp;

    if (src == dst) return dst;

    if (dst >= src + n || src >= dst + n)
    {	
        return memcpy(dst, src, n);
    }
    
    if (src > dst)
    {
        sp = src;
        dp = dst;

        while (n-- != 0)
        {
            *dp++ = *sp++;
        }
    } 
    else
    {
        sp = src + (n - 1);
        dp = dst + (n - 1);

        while (n-- != 0)
        {
            *dp-- = *sp--;
        }
    }

    return dst;
}

int bcmp(const char *s1, const char *s2, size_t len)
{
    for (; len && *s1++ == *s2++; len--);
    
    return len;
}