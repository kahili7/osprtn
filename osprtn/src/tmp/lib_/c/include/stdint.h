#ifndef LIB_C_STDINT_H
#define LIB_C_STDINT_H

#include "platform.h"

typedef _Int8t      int8_t;
typedef _Uint8t     uint8_t;
typedef _Int16t     int16_t;
typedef _Uint16t    uint16_t;
typedef _Int32t     int32_t;
typedef _Uint32t    uint32_t;
typedef _Int64t     int64_t;
typedef _Uint64t    uint64_t;

#if defined(__INTPTR_T)
    typedef __INTPTR_T  intptr_t;
    #undef __INTPTR_T
#else
    typedef _Intptrt  intptr_t;
#endif

typedef _Uintptrt   uintptr_t;

#endif /* LIB_C_STDINT_H */