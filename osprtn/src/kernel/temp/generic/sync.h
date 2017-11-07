#ifndef KERNEL_GENERIC_SYNC_H
#define KERNEL_GENERIC_SYNC_H

INLINE void memory_barrier()
{
    __asm__ __volatile__ ("" ::: "memory");
}

#ifndef CONFIG_SMP
    #define DEFINE_SPINLOCK(name) spinlock_t name
    #define DECLARE_SPINLOCK(name) extern spinlock_t name

    typedef struct spinlock {

    } spinlock_t;

    void spinlock_lock(spinlock_t *s) {}
    void spinlock_unlock(spinlock_t *s) {}
    void spinlock_init(spinlock_t *s) {}
    int spinlock_is_locked(spinlock_t *s) { return 0; }
#else
    #include DIR_ARCH(sync.h)

    typedef struct lockstate {
        union {
            word_t raw;
            
            struct {
                BITFIELD3(word_t,
                          enabled : 1,
                          promote : 1,
                          demote  : 1);
            } x;
        } flags;
        
        word_t rcu_epoch;
    } lockstate_t;
    
    void lockstate_init(lockstate_t *s, bool enabled) 
    {
        s->flags.raw = 0;
        s->flags.x.enabled = enabled;
    }

    bool lockstate_is_enabled(lockstate_t *s)
    {
	return s->flags.x.enabled;
    }

    bool lockstate_is_active(lockstate_t *s)
    {
	return s->flags.raw;
    }
#endif
#endif /* KERNEL_GENERIC_SYNC_H */