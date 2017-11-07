#ifndef ARCH_X86_UACCESS_H
#define ARCH_X86_UACCESS_H

//#include <platform.h>
#include <thread-info.h>
#include _SOS_CPU_HDR_DIR_(page.h)

/*
 * доступ к адресному пространству пользователя
 */

// привести к типу сегмент
#define MAKE_MM_SEG(s)	((mm_segment_t) { (s) })
#define KERNEL_DS	MAKE_MM_SEG(-1UL)
#define USER_DS 	MAKE_MM_SEG(TASK_SIZE_MAX)

#define get_ds()	(KERNEL_DS)
#define get_fs()	(current_thread_info()->addr_limit)
#define set_fs(x)	(current_thread_info()->addr_limit = (x))

#define segment_eq(a, b)    ((a).seg == (b).seg)

// максимальный адрес пользовательского сегмента
#define user_addr_max()     (current_thread_info()->addr_limit.seg)

// проверка адреса сегмента меньше максимального 
#define __addr_ok(addr)     ((unsigned long __force)(addr) < user_addr_max())

// проверить, является ли блок памяти является допустимым пространством пользователя адрес.
// возвращает 0, если диапазон является допустимым, ненулевое значение в противном случае.
#define __range_not_ok(addr, size, limit)\
        ({\
            unsigned long flag, roksum;\
            __chk_user_ptr(addr);\
            asm("add %3,%1; sbb %0,%0; cmp %1,%4; sbb $0,%0"\
                : "=&r" (flag), "=r" (roksum)\
                : "1" (addr), "g" ((long)(size)), "rm" (limit));\
            flag;\
        })

// проверяет, является ли указатель пространства пользователя действителен
#define access_ok(type, addr, size) (likely(__range_not_ok(addr, size, user_addr_max()) == 0))

#endif /* ARCH_X86_UACCESS_H */