#ifndef KERNEL_MEMMGR_MM_INTERNAL_H
#define KERNEL_MEMMGR_MM_INTERNAL_H

#ifndef EXTERN
    #define EXTERN  extern
#endif

#define VA_INVALID              ((uintptr_t)-1)     // недействительный виртуальный адрес

#define ADDR_OFFSET_BITS	12
#define ADDR_OFFSET_MASK	((1 << ADDR_OFFSET_BITS)-1)
#define ADDR_OFFSET(a)		((uintptr_t)(a) & ADDR_OFFSET_MASK)
#define ADDR_PAGE(a)		((a) & ~ADDR_OFFSET_MASK)

#include MM_DIR_ARCH(cpu_mm_internal.h)

struct memmgr_rwlock {
    u32_t lock;
};

EXTERN struct palloc_restrict   *restrict_proc;     // ограничение для процесса
EXTERN struct palloc_restrict	*restrict_user;     // ограничение для юзера
EXTERN struct palloc_restrict	*restrict_user_paddr64;

EXTERN paddr_t			last_paddr;         // последний физический адрес
EXTERN uintptr_t		va_rover;

#include MM_DIR(mm_flags.h)
EXTERN unsigned			mm_flags;           // флаги менеджера памяти


#include <palloc.h>

#endif /* KERNEL_MEMMGR_MM_INTERNAL_H */