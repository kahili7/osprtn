#ifndef ARCH_X86_CURRENT_H
#define ARCH_X86_CURRENT_H

#include _SOS_CPU_HDR_DIR_(percpu.h)

/*
 * получить текущий задачу на процессоре
 */

#ifndef __ASSEMBLY__
    struct task_struct;

    DECLARE_PER_CPU(struct task_struct*, current_task);

    static __always_inline struct task_struct* get_current(void)
    {
        return this_cpu_read_stable(current_task);
    }

    #define current get_current()
#endif

#endif /* ARCH_X86_CURRENT_H */