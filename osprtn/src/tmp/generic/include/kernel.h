#ifndef GENERIC_KERNEL_H
#define GENERIC_KERNEL_H

#include <platform.h>
#include <stddef.h>
#include <bit/bitops.h>

#define __ALIGN_KERNEL(x, a)            __ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#define __ALIGN_KERNEL_MASK(x, mask)    (((x) + (mask)) & ~(mask))

// обменять два значения
#define swap(a, b) do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)

// получает смещение на элемент структуры
#define container_of(ptr, type, member) ({\
        const typeof(((type *)0)->member) *__mptr = (ptr);\
        (type *)((char *)__mptr - offsetof(type, member));})

#endif /* GENERIC_KERNEL_H */