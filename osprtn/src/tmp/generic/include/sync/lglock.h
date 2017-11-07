#ifndef GENERIC_SYNC_LGLOCK_H
#define GENERIC_SYNC_LGLOCK_H

#include <sync/spinlock.h>
#include <percpu.h>

/*
 * эксклюзивный доступ к данным одного процессора к другому
 */
struct lglock {
    arch_spinlock_t __percpu *lock;
    
#ifdef CONFIG_DEBUG_LOCK_ALLOC
    struct lock_class_key lock_key;
    struct lockdep_map    lock_dep_map;
#endif
};

#define DEFINE_LGLOCK(name)\
	static DEFINE_PER_CPU(arch_spinlock_t, name ## _lock) = __ARCH_SPINLOCK_UNLOCKED;\
	struct lglock name = { .lock = &name ## _lock }

#define DEFINE_STATIC_LGLOCK(name)\
	static DEFINE_PER_CPU(arch_spinlock_t, name ## _lock) = __ARCH_SPINLOCK_UNLOCKED;					\
	static struct lglock name = { .lock = &name ## _lock }

//void lg_lock_init(struct lglock *lg, char *name);

void lg_local_lock(struct lglock *lg);
void lg_local_unlock(struct lglock *lg);
void lg_local_lock_cpu(struct lglock *lg, int cpu);
void lg_local_unlock_cpu(struct lglock *lg, int cpu);

void lg_global_lock(struct lglock *lg);
void lg_global_unlock(struct lglock *lg);
#endif /* GENERIC_SYNC_LGLOCK_H */