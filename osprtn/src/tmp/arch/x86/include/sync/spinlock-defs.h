#ifndef ARCH_X86_SYNC_SPINLOCK_DEFS_H
#define ARCH_X86_SYNC_SPINLOCK_DEFS_H
/*
 * архитектурное определение типов блокировок
 */

#define __TICKET_LOCK_INC       1
#define TICKET_SLOWPATH_FLAG    ((__ticket_t)0)

#if (CONFIG_NR_CPUS < (256 / __TICKET_LOCK_INC))
    typedef _Uint8t  __ticket_t;
    typedef _Uint16t __ticketpair_t;
#else
    typedef _Uint16t __ticket_t;
    typedef _Uint32t __ticketpair_t;
#endif

#define TICKET_LOCK_INC ((__ticket_t)__TICKET_LOCK_INC)
#define TICKET_SHIFT    (sizeof(__ticket_t) * 8)

#ifdef CONFIG_QUEUED_SPINLOCKS
    #include <asm-generic/qspinlock_types.h>
#else    
    typedef struct arch_spinlock {
        union {
            __ticketpair_t head_tail;

            struct __raw_tickets {
                __ticket_t head;
                __ticket_t tail;
            } tickets;
        };
    } arch_spinlock_t;

    #define __ARCH_SPINLOCK_UNLOCKED   { { 0 } }
#endif
    
#include _SOS_CPU_HDR_DIR_(sync/rwlock.h) //sync
#endif /* ARCH_X86_SYNC_SPINLOCK_DEFS_H */