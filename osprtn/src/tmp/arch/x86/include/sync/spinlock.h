#ifndef ARCH_X86_SYNC_SPINLOCK_H
#define ARCH_X86_SYNC_SPINLOCK_H

#include <atomic.h>
#include <bug.h>
#include _SOS_CPU_HDR_DIR_(page.h)
#include _SOS_CPU_HDR_DIR_(processor.h)
#include _SOS_CPU_HDR_DIR_(bitops.h)

// проверка на блокировку
static __always_inline int arch_spin_value_unlocked(arch_spinlock_t lock)
{
    return lock.tickets.head == lock.tickets.tail;
}

// регистр ax/DI 
#ifdef CONFIG_X86_32
    #define LOCK_PTR_REG "a"
#else
    #define LOCK_PTR_REG "D"
#endif

#if defined(CONFIG_X86_32) && (defined(CONFIG_X86_OOSTORE) || defined(CONFIG_X86_PPRO_FENCE))
    #define UNLOCK_LOCK_PREFIX LOCK_PREFIX
#else
    #define UNLOCK_LOCK_PREFIX
#endif

// порог блокировок
#define SPIN_THRESHOLD  (1 << 15)

static __always_inline void __ticket_lock_spinning(arch_spinlock_t *lock, __ticket_t ticket)
{
}

static inline void __ticket_unlock_kick(arch_spinlock_t *lock, __ticket_t ticket)
{
}

// аппаратная блокировка
static __always_inline void arch_spin_lock(arch_spinlock_t *lock)
{
    register struct __raw_tickets inc = { .tail = TICKET_LOCK_INC };

    inc = xadd_smp(&lock->tickets, inc);
    
    if (likely(inc.head == inc.tail)) goto out;

    inc.tail &= ~TICKET_SLOWPATH_FLAG;
    
    for (;;)
    {
        unsigned count = SPIN_THRESHOLD;

        do {
            if (ACCESS_ONCE(lock->tickets.head) == inc.tail) goto out;
            
            cpu_relax();
        } while (--count);
        
        __ticket_lock_spinning(lock, inc.tail);
    }
    
out:	barrier();
}

// аппаратная блокировка (пытаться)
static __always_inline int arch_try_spin_lock(arch_spinlock_t *lock)
{
    arch_spinlock_t old, n;

    old.tickets = ACCESS_ONCE(lock->tickets);
    
    if (old.tickets.head != (old.tickets.tail & ~TICKET_SLOWPATH_FLAG)) return 0;

    n.head_tail = old.head_tail + (TICKET_LOCK_INC << TICKET_SHIFT);

    return cmpxchg_smp(&lock->head_tail, old.head_tail, n.head_tail) == old.head_tail;
}

static inline void __ticket_unlock_slowpath(arch_spinlock_t *lock, arch_spinlock_t old)
{
    arch_spinlock_t n;

    BUILD_BUG_ON(((__ticket_t)NR_CPUS) != NR_CPUS);

    // выполнить разблокировку до копирования
    old.tickets.head += TICKET_LOCK_INC;
    // снять флаг SLOWPATH
    n.head_tail = old.head_tail & ~(TICKET_SLOWPATH_FLAG << TICKET_SHIFT);

    // если блокировка не утверждена, очистить флаг
    if (n.tickets.head != n.tickets.tail || cmpxchg_smp(&lock->head_tail, old.head_tail, n.head_tail) != old.head_tail)
    {
        __ticket_unlock_kick(lock, old.tickets.head);
    }
}

// аппаратная разблокировка
static __always_inline void arch_spin_unlock(arch_spinlock_t *lock)
{
    __add(&lock->tickets.head, TICKET_LOCK_INC, UNLOCK_LOCK_PREFIX);
}

// проверка на блокировку
static inline int arch_spin_is_locked(arch_spinlock_t *lock)
{
    struct __raw_tickets tmp = ACCESS_ONCE(lock->tickets);

    return tmp.tail != tmp.head;
}

// проверка на оспаривание
#define arch_spin_is_contended  arch_spin_is_contended

static inline int arch_spin_is_contended(arch_spinlock_t *lock)
{
    struct __raw_tickets tmp = ACCESS_ONCE(lock->tickets);

    return (__ticket_t)(tmp.tail - tmp.head) > TICKET_LOCK_INC;
}

// аппаратная блокировка с регистром флагов
static __always_inline void arch_spin_lock_flags(arch_spinlock_t *lock, unsigned long flags)
{
    arch_spin_lock(lock);
}

// ждать аппаратной разблокировки
static inline void arch_spin_unlock_wait(arch_spinlock_t *lock)
{
    while (arch_spin_is_locked(lock)) cpu_relax();
}

/*
 * Чтение и запись спин-блокировок, что позволяет нескольким читателям, но только один писатель.
 */
// проверка на блокировки (чтение)
static inline int arch_read_can_lock(arch_rwlock_t *lock)
{
    return lock->lock > 0;
}

// проверка на блокировки (запись)
static inline int arch_write_can_lock(arch_rwlock_t *lock)
{
    return lock->write == WRITE_LOCK_CMP;
}

// блокировка на чтение
#define arch_read_lock_flags(lock, flags) arch_read_lock(lock)

static inline void arch_read_lock(arch_rwlock_t *rw)
{
    asm volatile(LOCK_PREFIX READ_LOCK_SIZE(dec) " (%0)\n\t"
                 "jns 1f\n"
                 "call __read_lock_failed\n\t"
                 "1:\n" : : LOCK_PTR_REG (rw) : "memory");
}

// блокировка на запись
#define arch_write_lock_flags(lock, flags) arch_write_lock(lock)

static inline void arch_write_lock(arch_rwlock_t *rw)
{
    asm volatile(LOCK_PREFIX WRITE_LOCK_SUB(%1) "(%0)\n\t"
                 "jz 1f\n"
                 "call __write_lock_failed\n\t"
                 "1:\n" : : LOCK_PTR_REG (&rw->write), "i" (RW_LOCK_BIAS) : "memory");
}

// попытка блокировки на чтение
static inline int arch_read_trylock(arch_rwlock_t *lock)
{
    READ_LOCK_ATOMIC(t) *count = (READ_LOCK_ATOMIC(t) *)lock;

    if (READ_LOCK_ATOMIC(dec_return)(count) >= 0) return 1;
    
    READ_LOCK_ATOMIC(inc)(count);
    return 0;
}

// попытка блокировки на запись
static inline int arch_write_trylock(arch_rwlock_t *lock)
{
    atomic_t *count = (atomic_t *)&lock->write;

    if (atomic_sub_and_test(WRITE_LOCK_CMP, count)) return 1;
    
    atomic_add(WRITE_LOCK_CMP, count);
    return 0;
}

// разблокировать чтение
static inline void arch_read_unlock(arch_rwlock_t *rw)
{
    asm volatile(LOCK_PREFIX READ_LOCK_SIZE(inc) " %0" : "+m" (rw->lock) : : "memory");
}

// разблокировать запись
static inline void arch_write_unlock(arch_rwlock_t *rw)
{
    asm volatile(LOCK_PREFIX WRITE_LOCK_ADD(%1) "%0" : "+m" (rw->write) : "i" (RW_LOCK_BIAS) : "memory");
}

#undef READ_LOCK_SIZE
#undef READ_LOCK_ATOMIC
#undef WRITE_LOCK_ADD
#undef WRITE_LOCK_SUB
#undef WRITE_LOCK_CMP

#define arch_spin_relax(lock)   cpu_relax()
#define arch_read_relax(lock)	cpu_relax()
#define arch_write_relax(lock)	cpu_relax()

#endif /* ARCH_X86_SYNC_SPINLOCK_H */