#ifndef ARCH_X86_IRQ_FLAGS_H
#define ARCH_X86_IRQ_FLAGS_H

#include _SOS_CPU_HDR_DIR_(processor-flags.h)

#ifndef __ASSEMBLY__
    // сохранение значения флагов в переменную
    static inline unsigned long native_save_flags(void)
    {
        unsigned long flags;

        asm volatile("# __raw_save_flags\n\t"
                     "pushf ; pop %0"
                     : "=rm" (flags)
                     :
                     : "memory");

        return flags;
    }

    // восстановление значения флагов из переменную
    static inline void native_restore_flags(unsigned long flags)
    {
        asm volatile("push %0 ; popf"
                     :
                     :"g" (flags)
                     :"memory", "cc");
    }

    // запретить прерывания
    static inline void native_irq_disable(void)
    {
        asm volatile("cli": : :"memory");
    }

    // разрешить прерывания
    static inline void native_irq_enable(void)
    {
            asm volatile("sti": : :"memory");
    }

    // разрешить прерывания и остановка процессора
    // процессор ждет аппаранные прерывания.
    static inline void native_safe_halt(void)
    {
        asm volatile("sti; hlt": : :"memory");
    }

    // остановка процессора
    static inline void native_halt(void)
    {
        asm volatile("hlt": : :"memory");
    }


    static inline notrace unsigned long arch_local_irq_save_flags(void)
    {
        return native_save_flags();
    }

    static inline notrace void arch_local_irq_restore_flags(unsigned long flags)
    {
        native_restore_flags(flags);
    }

    static inline notrace void arch_local_irq_disable(void)
    {
        native_irq_disable();
    }

    static inline notrace void arch_local_irq_enable(void)
    {
        native_irq_enable();
    }

    static inline void arch_local_safe_halt(void)
    {
        native_safe_halt();
    }

    static inline void arch_local_halt(void)
    {
        native_halt();
    }

    static inline notrace unsigned long arch_local_irq_save(void)
    {
        unsigned long flags = arch_local_irq_save_flags();

        arch_local_irq_disable();
        return flags;
    }

    // установка флага прерывания отключено
    static inline int arch_irqs_disabled_flags(unsigned long flags)
    {
        return !(flags & X86_EFLAGS_IF);
    }

    static inline int arch_irqs_disabled(void)
    {
        unsigned long flags = arch_local_irq_save_flags();

        return arch_irqs_disabled_flags(flags);
    }
#else
    #define ENABLE_INTERRUPTS(x)	sti
    #define DISABLE_INTERRUPTS(x)	cli


#endif
#endif /* ARCH_X86_IRQ_FLAGS_H */