#ifndef LIB_C_STDDEF_H
#define LIB_C_STDDEF_H

#undef NULL
#define NULL ((void *)0)

enum {
    false = 0,
    true = 1
};

#undef offsetof
#ifdef __compiler_offsetof
    #define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
    #define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#endif /* LIB_C_STDDEF_H */