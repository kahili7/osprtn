#ifndef GENERIC_EXPORT_H
#define GENERIC_EXPORT_H

/*
 * экспорт из символа из ядра в модуль
 */

#define __VMLINUX_SYMBOL(x) x
#define __VMLINUX_SYMBOL_STR(x) #x

#define VMLINUX_SYMBOL(x) __VMLINUX_SYMBOL(x)
#define VMLINUX_SYMBOL_STR(x) __VMLINUX_SYMBOL_STR(x)

#ifndef __ASSEMBLY__
    struct kernel_symbol_struct
    {
        unsigned long value;
        const char *name;
    };
    
    #ifdef CONFIG_MODULES
        #ifndef __GENKSYMS__

            #define __CRC_SYMBOL(sym, sec)

            #define __EXPORT_SYMBOL(sym, sec)\
                extern typeof(sym) sym;\
                __CRC_SYMBOL(sym, sec)\
                static const char __kstrtab_##sym[] __attribute__((section("__ksymtab_strings"), aligned(1))) = VMLINUX_SYMBOL_STR(sym);\
                static const struct kernel_symbol_struct __ksymtab_##sym __used __attribute__((section("___ksymtab" sec "+" #sym), unused)) = { (unsigned long)&sym, __kstrtab_##sym }

            #define EXPORT_SYMBOL(sym)              __EXPORT_SYMBOL(sym, "")
            #define EXPORT_SYMBOL_GPL(sym)          __EXPORT_SYMBOL(sym, "_gpl")
            #define EXPORT_SYMBOL_GPL_FUTURE(sym)   __EXPORT_SYMBOL(sym, "_gpl_future")
        #endif
    #else
        #define EXPORT_SYMBOL(sym)
        #define EXPORT_SYMBOL_GPL(sym)
        #define EXPORT_SYMBOL_GPL_FUTURE(sym)
    #endif
#endif

#endif /* GENERIC_EXPORT_H */