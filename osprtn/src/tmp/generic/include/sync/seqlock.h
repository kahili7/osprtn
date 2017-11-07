#ifndef GENERIC_SYNC_SEQLOCK_H
#define GENERIC_SYNC_SEQLOCK_H

#include <sync/spinlock.h>
#include _SOS_CPU_HDR_DIR_(processor.h)

/*
 * последовательная блокировка
 * механизм чтения / запись совместно используемых данных
 */
typedef struct seqcount {
    unsigned sequence;
} seqcount_t;

#define SEQCNT_ZERO         { 0 }
#define __SEQCOUNT_INIT(x)  do { *(x) = (seqcount_t) SEQCNT_ZERO; } while (0)

// начало чтения счетчика блокировок - без барьера
static inline unsigned __read_seqcount_begin(const seqcount_t *s)
{
    unsigned ret;

repeat:
    ret = ACCESS_ONCE(s->sequence);

    if (unlikely(ret & 1))
    {
        cpu_relax();
        goto repeat;
    }

    return ret;
}

// начало чтения счетчика блокировок
static inline unsigned read_seqcount_begin(const seqcount_t *s)
{
    unsigned ret = __read_seqcount_begin(s);
    
    smp_rmb();
    return ret;
}

// чтение счетчика блокировок
static inline unsigned raw_read_seqcount(const seqcount_t *s)
{
    unsigned ret = ACCESS_ONCE(s->sequence);
    
    smp_rmb();
    return ret;
}

// начало чтение счетчика блокировок
static inline unsigned raw_seqcount_begin(const seqcount_t *s)
{
    unsigned ret = ACCESS_ONCE(s->sequence);
    
    smp_rmb();
    return ret & ~1;
}

// конец чтения счетчика блокировок - без барьера
static inline int __read_seqcount_retry(const seqcount_t *s, unsigned start)
{
    return unlikely(s->sequence != start);
}

// чтения счетчика блокировок
static inline int read_seqcount_retry(const seqcount_t *s, unsigned start)
{
    smp_rmb();
    return __read_seqcount_retry(s, start);
}

// начало записи счетчика блокировок
static inline void write_seqcount_begin(seqcount_t *s)
{
    s->sequence++;
    smp_wmb();
}

// конец записи счетчика блокировок
static inline void write_seqcount_end(seqcount_t *s)
{
    smp_wmb();
    s->sequence++;
}

static inline void write_seqcount_barrier(seqcount_t *s)
{
    smp_wmb();
    s->sequence += 2;
}

typedef struct {
    seqcount_t seqcount;
    spinlock_t lock;
} seqlock_t;

#define __SEQLOCK_UNLOCKED(lockname)\
	{\
            .seqcount = SEQCNT_ZERO,\
            .lock = __SPINLOCK_UNLOCKED(lockname)\
	}

#define __SEQLOCK_INIT(x)\
	do {\
            __SEQCOUNT_INIT(&(x)->seqcount);\
            __SPINLOCK_INIT(&(x)->lock);\
	} while (0)

#define DEFINE_SEQLOCK(x)   seqlock_t x = __SEQLOCK_UNLOCKED(x)

// начало и конец секции чтения  послед. блокировки 
static inline unsigned read_seqbegin(const seqlock_t *sl)
{
    return read_seqcount_begin(&sl->seqcount);
}

static inline unsigned read_seqretry(const seqlock_t *sl, unsigned start)
{
    return read_seqcount_retry(&sl->seqcount, start);
}

static inline void write_seqlock(seqlock_t *sl)
{
    spin_lock(&sl->lock);
    write_seqcount_begin(&sl->seqcount);
}

static inline void write_sequnlock(seqlock_t *sl)
{
    write_seqcount_end(&sl->seqcount);
    spin_unlock(&sl->lock);
}

// начало записи с сохранением предыдущего состояния
static inline unsigned long __write_seqlock_irqsave(seqlock_t *sl)
{
    unsigned long flags;

    spin_lock_irqsave(&sl->lock, flags);
    write_seqcount_begin(&sl->seqcount);
    return flags;
}

#define write_seqlock_irqsave(lock, flags)  do { flags = __write_seqlock_irqsave(lock); } while (0)

// конец записи с восстановлением предыдущего состояния
static inline void write_sequnlock_irqrestore(seqlock_t *sl, unsigned long flags)
{
    write_seqcount_end(&sl->seqcount);
    spin_unlock_irqrestore(&sl->lock, flags);
}

// исклюзивное чтение, но не обновляется блокировка - обычная блокировка
static inline void read_seqlock_excl(seqlock_t *sl)
{
    spin_lock(&sl->lock);
}

static inline void read_sequnlock_excl(seqlock_t *sl)
{
    spin_unlock(&sl->lock);
}

// послед. блокировка или обычная
static inline void read_seqbegin_or_lock(seqlock_t *lock, int *seq)
{
    if (!(*seq & 1)) *seq = read_seqbegin(lock);
    else read_seqlock_excl(lock);
}

static inline int need_seqretry(seqlock_t *lock, int seq)
{
    return !(seq & 1) && read_seqretry(lock, seq);
}

static inline void done_seqretry(seqlock_t *lock, int seq)
{
    if (seq & 1) read_sequnlock_excl(lock);
}

// исклюзивное чтение c маскированием прерываний, но не обновляется блокировка - обычная блокировка
static inline void read_seqlock_excl_irq(seqlock_t *sl)
{
    spin_lock_irq(&sl->lock);
}

static inline void read_sequnlock_excl_irq(seqlock_t *sl)
{
    spin_unlock_irq(&sl->lock);
}

// исклюзивное чтение c маскированием прерываний и сохранением / восстановлением состояния, но не обновляется блокировка - обычная блокировка
static inline unsigned long __read_seqlock_excl_irqsave(seqlock_t *sl)
{
    unsigned long flags;

    spin_lock_irqsave(&sl->lock, flags);
    return flags;
}

#define read_seqlock_excl_irqsave(lock, flags)  do { flags = __read_seqlock_excl_irqsave(lock); } while (0)

static inline void read_sequnlock_excl_irqrestore(seqlock_t *sl, unsigned long flags)
{
    spin_unlock_irqrestore(&sl->lock, flags);
}

// послед. блокировка или исклюзивное чтение c маскированием прерываний и сохранением состояния, но не обновляется блокировка - обычная блокировка
static inline unsigned long read_seqbegin_or_lock_irqsave(seqlock_t *lock, int *seq)
{
    unsigned long flags = 0;
    
    if (!(*seq & 1)) *seq = read_seqbegin(lock);
    else read_seqlock_excl_irqsave(lock, flags);
    
    return flags;
}

// исклюзивное чтение c маскированием прерываний и восстановлением состояния, но не обновляется блокировка - обычная блокировка
static inline void done_seqretry_irqrestore(seqlock_t *lock, int seq, unsigned long flags)
{
    if (seq & 1) read_sequnlock_excl_irqrestore(lock, flags);
}
#endif /* GENERIC_SYNC_SEQLOCK_H */