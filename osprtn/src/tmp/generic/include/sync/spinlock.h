#ifndef GENERIC_SYNC_SPINLOCK_H
#define GENERIC_SYNC_SPINLOCK_H

#include <typecheck.h>
#include <preempt.h>
#include _SOS_CPU_HDR_DIR_(sync/barrier.h)

#include <sync/spinlock-defs.h>

#ifdef CONFIG_SMP
    #include _SOS_CPU_HDR_DIR_(sync/spinlock.h)
#else
    #include <sync/spinlock-up.h>
#endif

// сырые функции блокировок
#ifdef CONFIG_DEBUG_SPINLOCK
#else
    #define raw_spin_lock_init(lock)    do { *(lock) = __RAW_SPINLOCK_UNLOCKED(lock); } while (0)
#endif

#define raw_spin_is_locked(lock)	arch_spin_is_locked(&(lock)->raw_lock)
#define raw_spin_unlock_wait(lock)	arch_spin_unlock_wait(&(lock)->raw_lock)

#ifdef arch_spin_is_contended
    #define raw_spin_is_contended(lock)	arch_spin_is_contended(&(lock)->raw_lock)
#else
    #define raw_spin_is_contended(lock)	(((void)(lock), 0))
#endif

#ifdef CONFIG_DEBUG_SPINLOCK
#else
    static inline void do_raw_spin_lock(raw_spinlock_t *lock) __acquires(lock)
    {
        __acquire(lock);
        arch_spin_lock(&lock->raw_lock);
    }

    static inline void do_raw_spin_lock_flags(raw_spinlock_t *lock, unsigned long *flags) __acquires(lock)
    {
        __acquire(lock);
        arch_spin_lock_flags(&lock->raw_lock, *flags);
    }

    static inline int do_raw_spin_trylock(raw_spinlock_t *lock)
    {
        return arch_spin_trylock(&(lock)->raw_lock);
    }

    static inline void do_raw_spin_unlock(raw_spinlock_t *lock) __releases(lock)
    {
        arch_spin_unlock(&lock->raw_lock);
        __release(lock);
    }
#endif

#define raw_spin_trylock(lock)	__cond_lock(lock, _raw_spin_trylock(lock))
#define raw_spin_lock(lock)	_raw_spin_lock(lock)

#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
#else
    #define raw_spin_lock_irqsave(lock, flags)\
            do {\
                typecheck(unsigned long, flags);\
                _raw_spin_lock_irqsave(lock, flags);\
            } while (0)

    #define raw_spin_lock_irqsave_nested(lock, flags, subclass) raw_spin_lock_irqsave(lock, flags)
#endif

#define raw_spin_lock_irq(lock)		_raw_spin_lock_irq(lock)
#define raw_spin_lock_bh(lock)		_raw_spin_lock_bh(lock)
    
#define raw_spin_unlock(lock)		_raw_spin_unlock(lock)
#define raw_spin_unlock_irq(lock)	_raw_spin_unlock_irq(lock)
#define raw_spin_unlock_irqrestore(lock, flags)\
	do {\
            typecheck(unsigned long, flags);\
            _raw_spin_unlock_irqrestore(lock, flags);\
	} while (0)
#define raw_spin_unlock_bh(lock)	_raw_spin_unlock_bh(lock)
    
#define raw_spin_trylock_bh(lock)   __cond_lock(lock, _raw_spin_trylock_bh(lock))
#define raw_spin_trylock_irq(lock)\
        ({\
            local_irq_disable();\
            raw_spin_trylock(lock) ? 1 : ({ local_irq_enable(); 0;  });\
        })
#define raw_spin_trylock_irqsave(lock, flags)\
        ({\
            local_irq_save(flags);\
            raw_spin_trylock(lock) ? 1 : ({ local_irq_restore(flags); 0; });\
        })
    
#define raw_spin_can_lock(lock)     (!raw_spin_is_locked(lock))
    
//#include <sync/rwlock.h>
    
#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
    #include <sync/spinlock-smp.h>
#endif

static inline raw_spinlock_t *spinlock_check(spinlock_t *lock)
{
    return &lock->rlock;
}

// блокировка
#define spin_lock_init(_lock)\
        do {\
            spinlock_check(_lock);\
            raw_spin_lock_init(&(_lock)->rlock);\
        } while (0)

static inline void spin_lock(spinlock_t *lock)
{
    raw_spin_lock(&lock->rlock);
}

static inline void spin_lock_irq(spinlock_t *lock)
{
    raw_spin_lock_irq(&lock->rlock);
}

#define spin_lock_irqsave(lock, flags)\
        do {\
            raw_spin_lock_irqsave(spinlock_check(lock), flags);\
        } while (0)

static inline int spin_trylock(spinlock_t *lock)
{
    return raw_spin_trylock(&lock->rlock);
}

#define spin_trylock_irqsave(lock, flags)   ({ raw_spin_trylock_irqsave(spinlock_check(lock), flags); })

// разблокировка
static inline void spin_unlock(spinlock_t *lock)
{
    raw_spin_unlock(&lock->rlock);
}

static inline void spin_unlock_irq(spinlock_t *lock)
{
    raw_spin_unlock_irq(&lock->rlock);
}

static inline void spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags)
{
    raw_spin_unlock_irqrestore(&lock->rlock, flags);
}

static inline void spin_unlock_wait(spinlock_t *lock)
{
    raw_spin_unlock_wait(&lock->rlock);
}

// проверки
static inline int spin_is_locked(spinlock_t *lock)
{
    return raw_spin_is_locked(&lock->rlock);
}

static inline int spin_is_contended(spinlock_t *lock)
{
    return raw_spin_is_contended(&lock->rlock);
}

static inline int spin_can_lock(spinlock_t *lock)
{
    return raw_spin_can_lock(&lock->rlock);
}

#include <sync/atomic.h>
#endif /* GENERIC_SYNC_SPINLOCK_H */