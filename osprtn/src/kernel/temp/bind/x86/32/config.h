#ifndef KERNEL_BIND_X86_32_CONFIG_H
#define KERNEL_BIND_X86_32_CONFIG_H

#include DIR_ARCH(x86.h)
#include DIR_BIND_CPU(offsets.h)

#if defined(CONFIG_X_X86_HVM)
#include DIR_BIND_CPU(hvm-config.h)
#else

/*
 * виртуальное адресное пространство
 */

// пользовательское пространство
#define USER_AREA_START		__UL(0x00000000)
#define USER_AREA_END		__UL(0xC0000000)                    // 31,30 bits = 1
#define USER_AREA_SIZE		(USER_AREA_END - USER_AREA_START)


#endif


#define IDT_SIZE    256     // размер таблицы прерываний
#define GDT_SIZE    16      // размер таблицы глобальных дескрипторов


// сегментные регистры
#define X86_KERNEL_CS      0x80
#define X86_KERNEL_DS      0x27
#define X86_KERNEL_SS      0x88

#define X86_USER_CS         0x1F
#define X86_USER_DS         0x27
#define X86_USER_SS         0x27
#endif /* KERNEL_BIND_X86_32_CONFIG_H */