#ifndef ARCH_X86_STRING_32_H
#define ARCH_X86_STRING_32_H

#ifdef __KERNEL__

    #define __HAVE_ARCH_STRCPY
    extern char *strcpy(char *dest, const char *src);
    
    #define __HAVE_ARCH_STRNCPY
    extern char *strncpy(char *dest, const char *src, size_t count);

    #define __HAVE_ARCH_STRCAT
    extern char *strcat(char *dest, const char *src);

    #define __HAVE_ARCH_STRNCAT
    extern char *strncat(char *dest, const char *src, size_t count);

    #define __HAVE_ARCH_STRCMP
    extern int strcmp(const char *cs, const char *ct);

    #define __HAVE_ARCH_STRNCMP
    extern int strncmp(const char *cs, const char *ct, size_t count);

    #define __HAVE_ARCH_STRCHR
    extern char *strchr(const char *s, int c);

    #define __HAVE_ARCH_STRLEN
    extern size_t strlen(const char *s);
    
    #define __HAVE_ARCH_STRNLEN
    extern size_t strnlen(const char *s, size_t count);
    
    #define __HAVE_ARCH_MEMCHR
    extern void *memchr(const void *cs, int c, size_t count);
    
    #define __HAVE_ARCH_MEMSCAN
    extern void *memscan(void *addr, int c, size_t size);
    
    static __always_inline void *__memcpy(void *to, const void *from, size_t n)
    {
        int d0, d1, d2;
        
        asm volatile("rep ; movsl\n\t"
                    "movl %4,%%ecx\n\t"
                    "andl $3,%%ecx\n\t"
                    "jz 1f\n\t"
                    "rep ; movsb\n\t"
                    "1:"
                    : "=&c" (d0), "=&D" (d1), "=&S" (d2)
                    : "0" (n / 4), "g" (n), "1" ((long)to), "2" ((long)from) : "memory");
        return to;
    }
    
    static __always_inline void *__constant_memcpy(void *to, const void *from, size_t n)
    {
            long esi, edi;
            
            if (!n) return to;

            switch (n)
            {
                case 1:
                    *(char *)to = *(char *)from;
                    return to;
                case 2:
                    *(short *)to = *(short *)from;
                    return to;
                case 4:
                    *(int *)to = *(int *)from;
                    return to;
                case 3:
                    *(short *)to = *(short *)from;
                    *((char *)to + 2) = *((char *)from + 2);
                    return to;
                case 5:
                    *(int *)to = *(int *)from;
                    *((char *)to + 4) = *((char *)from + 4);
                    return to;
                case 6:
                    *(int *)to = *(int *)from;
                    *((short *)to + 2) = *((short *)from + 2);
                    return to;
                case 8:
                    *(int *)to = *(int *)from;
                    *((int *)to + 1) = *((int *)from + 1);
                    return to;
            }

            esi = (long)from;
            edi = (long)to;
            
            if (n >= 5 * 4)
            {
                /* large block: use rep prefix */
                int ecx;
                
                asm volatile("rep ; movsl"
                            : "=&c" (ecx), "=&D" (edi), "=&S" (esi)
                            : "0" (n / 4), "1" (edi), "2" (esi) : "memory");
            }
            else
            {
                /* small block: don't clobber ecx + smaller code */
                if (n >= 4 * 4)
                    asm volatile("movsl"
                                : "=&D"(edi), "=&S"(esi)
                                : "0"(edi), "1"(esi) : "memory");
                if (n >= 3 * 4)
                    asm volatile("movsl"
                                : "=&D"(edi), "=&S"(esi)
                                : "0"(edi), "1"(esi) : "memory");
                if (n >= 2 * 4)
                    asm volatile("movsl"
                                : "=&D"(edi), "=&S"(esi)
                                : "0"(edi), "1"(esi) : "memory");
                if (n >= 1 * 4)
                    asm volatile("movsl"
                                : "=&D"(edi), "=&S"(esi)
                                : "0"(edi), "1"(esi) : "memory");
            }
            
            switch (n % 4)
            {
                    /* tail */
                case 0:
                    return to;
                case 1:
                    asm volatile("movsb"
                                : "=&D"(edi), "=&S"(esi)
                                : "0"(edi), "1"(esi) : "memory");
                    return to;
                case 2:
                    asm volatile("movsw"
                                : "=&D"(edi), "=&S"(esi)
                                : "0"(edi), "1"(esi) : "memory");
                    return to;
                default:
                    asm volatile("movsw\n\tmovsb"
                                : "=&D"(edi), "=&S"(esi)
                                : "0"(edi), "1"(esi) : "memory");
                    return to;
            }
    }
    
    #ifndef CONFIG_KMEMCHECK
        #if (__GNUC__ >= 4)
            #define memcpy(t, f, n) __builtin_memcpy(t, f, n)
        #else
            #define memcpy(t, f, n)\
                    (__builtin_constant_p((n)) ? __constant_memcpy((t), (f), (n)) : __memcpy((t), (f), (n)))
        #endif
    #else
        #define memcpy(t, f, n) __memcpy((t), (f), (n))
    #endif
#endif

#endif /* ARCH_X86_STRING_32_H */