#ifndef GENERIC_SYNC_BIT_SPINLOCK_H
#define GENERIC_SYNC_BIT_SPINLOCK_H

#include <preempt.h>
#include <atomic.h>
#include <bug.h>

// установить бит блокировки
static inline void bit_spin_lock(int bitnum, unsigned long *addr)
{
    preempt_disable();
    
    #if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
        while (unlikely(test_and_set_bit_lock(bitnum, addr)))
        {
            preempt_enable();
            
            do {
                cpu_relax();
            } while (test_bit(bitnum, addr));
            
            preempt_disable();
        }
    #endif

    __acquire(bitlock);
}

// сбросить бит блокировки
static inline void __bit_spin_unlock(int bitnum, unsigned long *addr)
{
    #ifdef CONFIG_DEBUG_SPINLOCK
            BUG_ON(!test_bit(bitnum, addr));
    #endif
    #if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
        __clear_bit_unlock(bitnum, addr);
    #endif

    preempt_enable();
    __release(bitlock);
}

// проверить установлен бит блокировки
static inline int bit_spin_is_locked(int bitnum, unsigned long *addr)
{
    #if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
        return test_bit(bitnum, addr);
    #elif defined CONFIG_PREEMPT_COUNT
        return preempt_count();
    #else
        return 1;
    #endif
}
#endif /* GENERIC_SYNC_BIT_SPINLOCK_H */