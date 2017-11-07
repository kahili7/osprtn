#ifndef KERNEL_ARCH_X86_32_TYPES_H
#define KERNEL_ARCH_X86_32_TYPES_H

// беззнаковые
typedef unsigned int __attribute__((__mode__(__DI__)))  u64_t;
typedef unsigned int                                    u32_t;
typedef unsigned short                                  u16_t;
typedef unsigned char                                   u8_t;
typedef u32_t                                           uintptr_t;

// знаковые
typedef signed int __attribute__((__mode__(__DI__)))    s64_t;
typedef signed int                                      s32_t;
typedef signed short                                    s16_t;
typedef signed char                                     s8_t;
typedef s32_t                                           iintptr_t;

// беззнаковое машинное слово
typedef u32_t                                           word_t;
#endif /* KERNEL_ARCH_X86_32_TYPES_H */