#ifndef ARCH_X86_SEGMENT_H
#define ARCH_X86_SEGMENT_H

#include <stdint.h>

#ifdef CONFIG_X86_32
#define GDT_ENTRIES 32

#define GDT_ENTRY_TLS_MIN	6
#define GDT_ENTRY_TLS_MAX 	(GDT_ENTRY_TLS_MIN + GDT_ENTRY_TLS_ENTRIES - 1)

#define GDT_ENTRY_KERNEL_BASE       (12)

#define GDT_ENTRY_KERNEL_CS     (GDT_ENTRY_KERNEL_BASE + 0)
#define GDT_ENTRY_KERNEL_DS     (GDT_ENTRY_KERNEL_BASE + 1)
#define GDT_ENTRY_DEFAULT_USER_CS   14
#define GDT_ENTRY_DEFAULT_USER_DS   15
#define GDT_ENTRY_TSS           (GDT_ENTRY_KERNEL_BASE + 4)
#define GDT_ENTRY_LDT           (GDT_ENTRY_KERNEL_BASE + 5)
#else
#define GDT_ENTRIES 16

#define GDT_ENTRY_KERNEL32_CS       1
#define GDT_ENTRY_KERNEL_CS         2
#define GDT_ENTRY_KERNEL_DS         3
#define GDT_ENTRY_DEFAULT_USER32_CS 4
#define GDT_ENTRY_DEFAULT_USER_DS   5
#define GDT_ENTRY_DEFAULT_USER_CS   6

#define GDT_ENTRY_TSS 8
#define GDT_ENTRY_LDT 10
#define GDT_ENTRY_TLS_MIN 12
#define GDT_ENTRY_TLS_MAX 14
#define GDT_ENTRY_PER_CPU 15

#define __KERNEL32_CS   (GDT_ENTRY_KERNEL32_CS * 8)
#define __USER32_CS     (GDT_ENTRY_DEFAULT_USER32_CS * 8 + 3)
#define __USER32_DS     (GDT_ENTRY_DEFAULT_USER_DS * 8 + 3)

#endif /* CONFIG_X86_32 */

#define __KERNEL_CS	(GDT_ENTRY_KERNEL_CS * 8)
#define __KERNEL_DS	(GDT_ENTRY_KERNEL_DS * 8)
#define __USER_DS	(GDT_ENTRY_DEFAULT_USER_DS * 8 + 3)
#define __USER_CS	(GDT_ENTRY_DEFAULT_USER_CS * 8 + 3)

// уровень привилегий пользователя
#define USER_RPL    0x3

// LDT сегмент TI флаг установлен. GDT очищен
#define SEGMENT_LDT 0x4
#define SEGMENT_GDT 0x0

// нижние два бита селектора отдай кольцо уровень привилегий
#define SEGMENT_RPL_MASK    0x3
#define SEGMENT_TI_MASK     0x4

// количество прерываний
#define IDT_ENTRIES 256
#define NUM_EXCEPTION_VECTORS 32

// размер GDT таблицы
#define GDT_SIZE                (GDT_ENTRIES * 8)

// размер TLS таблицы в таблице GDT
#define GDT_ENTRY_TLS_ENTRIES   3
#define TLS_SIZE                (GDT_ENTRY_TLS_ENTRIES * 8)
#endif /* ARCH_X86_SEGMENT_H */