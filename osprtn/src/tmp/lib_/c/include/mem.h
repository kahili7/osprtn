#ifndef LIB_C_MEM_H
#define LIB_C_MEM_H
#include "platform.h"
#include <types.h>

#define bzero(ptr, len)  memset((ptr), 0, (len))

extern void *memset(void *, int, size_t);
extern void *memcpy(void *, const void *, size_t);
extern void *memmove(void *, const void *, size_t);

extern int bcmp(const char *, const char *, size_t);

#endif /* LIB_C_MEM_H */