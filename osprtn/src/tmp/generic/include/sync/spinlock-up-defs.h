#ifndef GENERIC_SYNC_SPINLOCK_UP_DEFS_H
#define GENERIC_SYNC_SPINLOCK_UP_DEFS_H

#ifndef GENERIC_SYNC_SPINLOCK_UP_DEFS_H
    #error "please don't include this file directly"
#endif


#ifdef CONFIG_DEBUG_SPINLOCK

    typedef struct {
        volatile unsigned int slock;
    } arch_spinlock_t;

    #define __ARCH_SPINLOCK_UNLOCKED { 1 }
#else

    typedef struct {} arch_spinlock_t;

    #define __ARCH_SPINLOCK_UNLOCKED { }
#endif

typedef struct {} arch_rwlock_t;

#define __ARCH_RWLOCK_UNLOCKED { }
#endif /* GENERIC_SYNC_SPINLOCK_UP_DEFS_H */