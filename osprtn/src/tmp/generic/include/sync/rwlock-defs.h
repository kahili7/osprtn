#ifndef GENERIC_RWLOCK_DEFS_H
#define GENERIC_RWLOCK_DEFS_H
/*
 * описание типа блокировок чтение/запись
 */

typedef struct {
    arch_rwlock_t raw_lock;
} rwlock_t;

#define RW_DEP_MAP_INIT(lockname)
#define __RWLOCK_UNLOCKED(lockname) (rwlock_t)	{ .raw_lock = __ARCH_RW_LOCK_UNLOCKED, RW_DEP_MAP_INIT(lockname) }

// определение блокировки 
#define DEFINE_RWLOCK(x)    rwlock_t x = __RWLOCK_UNLOCKED(x)

#endif /* GENERIC_RWLOCK_DEFS_H */