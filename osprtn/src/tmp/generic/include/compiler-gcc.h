#ifndef GENERIC_COMPILER_GCC_H
#define GENERIC_COMPILER_GCC_H

#ifdef CONFIG_64BIT
    #define BITS_PER_LONG 64
#else
    #define BITS_PER_LONG 32
#endif /* CONFIG_64BIT */

#ifndef BITS_PER_LONG_LONG
    #define BITS_PER_LONG_LONG 64
#endif

typedef signed char _Int8t;
typedef unsigned char _Uint8t;

typedef signed long long _Int64t;
typedef unsigned long long _Uint64t;

#if BITS_PER_LONG == 64
    typedef signed short _Int16t;
    typedef unsigned short _Uint16t;

    typedef signed int _Int32t;
    typedef unsigned int _Uint32t;

    typedef _Int64t _Intptrt;
    typedef _Uint64t _Uintptrt;
#elif BITS_PER_LONG == 32
    typedef signed int _Int16t;
    typedef unsigned int _Uint16t;

    typedef signed long _Int32t;
    typedef unsigned long _Uint32t;

    typedef _Int32t _Intptrt;
    typedef _Uint32t _Uintptrt;
#else
    typedef signed short _Int16t;
    typedef unsigned short _Uint16t;
    
    typedef signed long _Int32t;
    typedef unsigned long _Uint32t;
    
    typedef _Int16t _Intptrt;
    typedef _Uint16t _Uintptrt;
#endif
    
typedef _Uint64t _Paddr64t;
typedef _Uint32t _Paddr32t;
    
#endif /* GENERIC_COMPILER_GCC_H */