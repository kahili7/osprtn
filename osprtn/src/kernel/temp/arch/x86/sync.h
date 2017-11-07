#ifndef KERNEL_ARCH_X86_SYNC_H
#define KERNEL_ARCH_X86_SYNC_H

typedef struct spinlock {
    volatile word_t _lock;
} spinlock_t;

void spinlock_init(spinlock_t *s, word_t val)
{
    s->_lock = val;
}

void spinlock_unlock(spinlock_t *s)
{
    s->_lock = 0;
}

int spinlock_is_locked(spinlock_t *s)
{
    return s->_lock;
}

#define DECLARE_SPINLOCK(name) extern spinlock_t *name;
#define DEFINE_SPINLOCK(name)   { spinlock_t *name;\
                                  spinlock_init(name, 0); }

INLINE void spinlock_lock(spinlock_t *s)
{
    word_t dummy;
    
    __asm__ __volatile__ ("1:\n\t"
                          "xchg %1, %2\n\t"
                          "test $0xff, %2\n\t"
                          "jnz 2f\n\t"
                          ".subsection 2\n\t"
                          "2:\n\t"
                          "rep; nop\n\t"
                          "testb $1, %1\n\t"
                          "jne 2b\n\t"
                          "jmp 1b\n\t"
                          ".previous\n\t" : "=D" (dummy) : "m" (s->_lock), "0" ((word_t) 1));
}
#endif /* KERNEL_ARCH_X86_SYNC_H */