#ifndef LIB_C_ALLOCA_H
#define LIB_C_ALLOCA_H

#define __ALLOCA_ALIGN(s)   (((s) + (sizeof(_Uint64t) - 1)) & ~(sizeof(_Uint64t) - 1))

extern size_t __stackavail();

#define _alloca(s)  __builtin_alloca(s)
#define alloca(s)   (((__ALLOCA_ALIGN(s) + 128) < __stackavail()) ? _alloca(s) : 0)

#endif /* LIB_C_ALLOCA_H */