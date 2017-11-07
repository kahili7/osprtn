#ifndef GENERIC_SYNC_SPINLOCK_DEFS_H
#define GENERIC_SYNC_SPINLOCK_DEFS_H
/*
 * определение типов блокировок
 */

#if defined(CONFIG_SMP)
    #include _SOS_CPU_HDR_DIR_(sync/spinlock-defs.h)
#else
    #include <sync/spinlock-up-defs.h>
#endif

// предварительный тип блокировки
typedef struct raw_spinlock {
    arch_spinlock_t raw_lock;
    
#ifdef CONFIG_DEBUG_SPINLOCK
    unsigned int magic, owner_cpu;
    void *owner;
#endif
} raw_spinlock_t;

#define SPINLOCK_MAGIC		0xdead4ead
#define SPINLOCK_OWNER_INIT     ((void *)-1L)

#ifdef CONFIG_DEBUG_SPINLOCK
    #define SPIN_DEBUG_INIT(lockname)\
            .magic = SPINLOCK_MAGIC,\
            .owner_cpu = -1,\
            .owner = SPINLOCK_OWNER_INIT,
#else
    #define SPIN_DEBUG_INIT(lockname)
#endif

#define __RAW_SPINLOCK_INIT(lockname)      { .raw_lock = __ARCH_SPINLOCK_UNLOCKED }
#define __RAW_SPINLOCK_UNLOCKED(lockname)  (raw_spinlock_t) __RAW_SPINLOCK_INIT(lockname)
#define DEFINE_RAW_SPINLOCK(x)              raw_spinlock_t x = __RAW_SPINLOCK_UNLOCKED(x)

// тип низкоуровневой циклической блокировки
typedef struct spinlock {
    union {
        raw_spinlock_t rlock;
    };
} spinlock_t;

#define __SPINLOCK_INIT(lockname)       { { .rlock = __RAW_SPINLOCK_INIT(lockname) } }
#define __SPINLOCK_UNLOCKED(lockname)  (spinlock_t ) __SPINLOCK_INIT(lockname)
#define DEFINE_SPINLOCK(x)              spinlock_t x = __SPINLOCK_UNLOCKED(x)

#include <sync/rwlock-defs.h>
#endif /* GENERIC_SYNC_SPINLOCK_DEFS_H */