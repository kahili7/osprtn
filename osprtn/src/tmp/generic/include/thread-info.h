#ifndef GENERIC_THREAD_INFO_H
#define GENERIC_THREAD_INFO_H

#include <types.h>

// структура перезагрузки блока
struct restart_block_struct {
    long (*fn)(struct restart_block_struct *);
};

#include <bit/bitops.h>
#include _SOS_CPU_HDR_DIR_(thread-info.h)

// установка флага
static inline void set_ti_thread_flag(struct thread_info_struct *ti, int flag)
{
    set_bit(flag, (unsigned long *)&ti->flags);
}

// очистка флага
static inline void clear_ti_thread_flag(struct thread_info_struct *ti, int flag)
{
    clear_bit(flag, (unsigned long *)&ti->flags);
}

static inline int test_and_set_ti_thread_flag(struct thread_info_struct *ti, int flag)
{
    return test_and_set_bit(flag, (unsigned long *)&ti->flags);
}

static inline int test_and_clear_ti_thread_flag(struct thread_info_struct *ti, int flag)
{
    return test_and_clear_bit(flag, (unsigned long *)&ti->flags);
}

static inline int test_ti_thread_flag(struct thread_info_struct *ti, int flag)
{
    return test_bit(flag, (unsigned long *)&ti->flags);
}
#endif /* GENERIC_THREAD_INFO_H */