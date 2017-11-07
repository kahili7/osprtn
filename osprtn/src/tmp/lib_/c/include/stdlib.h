#ifndef LIB_C_STDLIB_H
#define LIB_C_STDLIB_H

#if !defined(__max)
    #define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#if !defined(max) && !defined(__cplusplus)
    #define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#if !defined(__min)
    #define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#if !defined(min) && !defined(__cplusplus)
    #define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#endif /* LIB_C_STDLIB_H */