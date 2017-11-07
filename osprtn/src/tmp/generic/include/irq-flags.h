#ifndef GENERIC_IRQ_FLAGS_H
#define GENERIC_IRQ_FLAGS_H

#include <typecheck.h>
#include _SOS_CPU_HDR_DIR_(irq-flags.h)

// обертки для IRQ
#define raw_local_irq_disable()     arch_local_irq_disable()
#define raw_local_irq_enable()      arch_local_irq_enable()
#define raw_local_irq_save(flags)\
    do {\
        typecheck(unsigned long, flags);\
        flags = arch_local_irq_save();\
    } while (0)

#define raw_local_irq_restore_flags(flags)\
    do {\
        typecheck(unsigned long, flags);\
        arch_local_irq_restore_flags(flags);\
    } while (0)

#define raw_local_irq_save_flags(flags)\
    do {\
        typecheck(unsigned long, flags);\
        flags = arch_local_irq_save_flags();\
    } while (0)

#define raw_irqs_disabled_flags(flags)\
    ({\
        typecheck(unsigned long, flags);\
        arch_irqs_disabled_flags(flags);\
    })

#define raw_irqs_disabled()         (arch_irqs_disabled())
#define raw_safe_halt()             arch_local_safe_halt() 


#ifdef CONFIG_TRACE_IRQFLAGS_SUPPORT
#else
    #define local_irq_enable()              do { raw_local_irq_enable(); } while (0)
    #define local_irq_disable()             do { raw_local_irq_disable(); } while (0)
    #define local_irq_save(flags)           do { raw_local_irq_save(flags); } while (0)
    #define local_irq_restore_flags(flags)  do { raw_local_irq_restore_flags(flags); } while (0)
    #define local_irq_save_flags(flags)     do { raw_local_irq_save_flags(flags); } while (0)
    #define irqs_disabled()                 (raw_irqs_disabled())
    #define irqs_disabled_flags(flags)      (raw_irqs_disabled_flags(flags))
    #define safe_halt()                     do { raw_safe_halt(); } while (0)
#endif
#endif /* GENERIC_IRQ_FLAGS_H */