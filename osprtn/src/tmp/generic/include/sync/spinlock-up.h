#ifndef GENERIC_SYNC_SPINLOCK_UP_H
#define GENERIC_SYNC_SPINLOCK_UP_H

#ifndef GENERIC_SYNC_SPINLOCK_UP_H
    #error "please don't include this file directly"
#endif

#include _SOS_CPU_HDR_DIR_(processor.h)

/*
 * версия для отладки блокировок
 * 0 - заблокировано
 * 1 - разблокировано
 */

#ifdef CONFIG_DEBUG_SPINLOCK
    #define arch_spin_is_locked(x)  ((x)->slock == 0)

    // установка блокировки
    static inline void arch_spin_lock(arch_spinlock_t *lock)
    {
        lock->slock = 0;
        barrier();
    }

    // установка блокировки и возвращение регистров флагов
    static inline void arch_spin_lock_flags(arch_spinlock_t *lock, unsigned long flags)
    {
        local_irq_save(flags);
        lock->slock = 0;
        barrier();
    }

    // попытка установки блокировки
    static inline int arch_spin_trylock(arch_spinlock_t *lock)
    {
        char oldval = lock->slock;

        lock->slock = 0;
        barrier();

        return oldval > 0;
    }

    // снятие блокировки
    static inline void arch_spin_unlock(arch_spinlock_t *lock)
    {
        barrier();
        lock->slock = 1;
    }

    #define arch_read_lock(lock)        do { barrier(); (void)(lock); } while (0)
    #define arch_write_lock(lock)       do { barrier(); (void)(lock); } while (0)
    #define arch_read_trylock(lock)     ({ barrier(); (void)(lock); 1; })
    #define arch_write_trylock(lock)    ({ barrier(); (void)(lock); 1; })
    #define arch_read_unlock(lock)      do { barrier(); (void)(lock); } while (0)
    #define arch_write_unlock(lock)     do { barrier(); (void)(lock); } while (0)

#else

    #define arch_spin_is_locked(lock)           ((void)(lock), 0)
    #define arch_spin_lock(lock)                do { barrier(); (void)(lock); } while (0)
    #define arch_spin_lock_flags(lock, flags)	do { barrier(); (void)(lock); } while (0)
    #define arch_spin_unlock(lock)              do { barrier(); (void)(lock); } while (0)
    #define arch_spin_trylock(lock)             ({ barrier(); (void)(lock); 1; })
#endif

#define arch_spin_is_contended(lock)	(((void)(lock), 0))
#define arch_read_can_lock(lock)	(((void)(lock), 1))
#define arch_write_can_lock(lock)       (((void)(lock), 1))
#define arch_spin_unlock_wait(lock)     do { cpu_relax(); } while (arch_spin_is_locked(lock))

// программная блокировка
#define __LOCK(lock)                        do { preempt_disable(); __acquire(lock); (void)(lock); } while (0)
    
// блокировка прерываний + программная
#define __LOCK_IRQ(lock)                    do { local_irq_disable(); __LOCK(lock); } while (0)
    
// блокировка прерываний с сохранением флагов + программная
#define __LOCK_IRQSAVE(lock, flags)         do { local_irq_save(flags); __LOCK(lock); } while (0)

// программная разблокировка
#define __UNLOCK(lock)                      do { preempt_enable(); __release(lock); (void)(lock); } while (0)
    
// разблокировка прерываний + программная    
#define __UNLOCK_IRQ(lock)                  do { local_irq_enable(); __UNLOCK(lock); } while (0)

// разблокировка прерываний с сохранением флагов + программная
#define __UNLOCK_IRQRESTORE(lock, flags)    do { local_irq_restore_flags(flags); __UNLOCK(lock); } while (0)
    
// блокировка    
#define _raw_spin_lock(lock)			__LOCK(lock)
#define _raw_read_lock(lock)			__LOCK(lock)
#define _raw_write_lock(lock)			__LOCK(lock)
    
#define _raw_spin_lock_irq(lock)		__LOCK_IRQ(lock)
#define _raw_read_lock_irq(lock)		__LOCK_IRQ(lock)
#define _raw_write_lock_irq(lock)		__LOCK_IRQ(lock)
    
#define _raw_spin_lock_irqsave(lock, flags)	__LOCK_IRQSAVE(lock, flags)
#define _raw_read_lock_irqsave(lock, flags)	__LOCK_IRQSAVE(lock, flags)
#define _raw_write_lock_irqsave(lock, flags)	__LOCK_IRQSAVE(lock, flags)
    
#define _raw_spin_trylock(lock)			({ __LOCK(lock); 1; })
#define _raw_read_trylock(lock)			({ __LOCK(lock); 1; })
#define _raw_write_trylock(lock)		({ __LOCK(lock); 1; })

// разблокировка
#define _raw_spin_unlock(lock)			__UNLOCK(lock)
#define _raw_read_unlock(lock)			__UNLOCK(lock)
#define _raw_write_unlock(lock)			__UNLOCK(lock)

#define _raw_spin_unlock_irq(lock)		__UNLOCK_IRQ(lock)
#define _raw_read_unlock_irq(lock)		__UNLOCK_IRQ(lock)
#define _raw_write_unlock_irq(lock)		__UNLOCK_IRQ(lock)

#define _raw_spin_unlock_irqrestore(lock, flags)    __UNLOCK_IRQRESTORE(lock, flags)
#define _raw_read_unlock_irqrestore(lock, flags)    __UNLOCK_IRQRESTORE(lock, flags)
#define _raw_write_unlock_irqrestore(lock, flags)   __UNLOCK_IRQRESTORE(lock, flags)    
#endif /* GENERIC_SYNC_SPINLOCK_UP_H */