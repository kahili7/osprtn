#ifndef ARCH_X86_PERCPU_H
#define ARCH_X86_PERCPU_H

#ifdef CONFIG_X86_64
    #define __percpu_seg        gs
    #define __percpu_mov_op     movq
#else
    #define __percpu_seg        fs
    #define __percpu_mov_op     movl
#endif

#ifdef __ASSEMBLY__
#else
    #ifdef CONFIG_SMP
    #else
        #define __percpu_prefix ""
    #endif

    #define __percpu_arg(x) __percpu_prefix "%P" #x

    #define DECLARE_INIT_PER_CPU(var)   extern typeof(var) init_per_cpu_var(var)
    
    #ifdef CONFIG_X86_64_SMP
        #define init_per_cpu_var(var)  init_per_cpu__##var
    #else
        #define init_per_cpu_var(var)  var
    #endif

    extern void __bad_percpu_size(void);

    // макрос выполнение инструкции на процессоре в зависимости от размерам переменной
    // значение сохранить в переменной в памяти
    #define percpu_to_op(op, var, val)\
            do {\
                typedef typeof(var) pto_T__;\
                if (0) {\
                    pto_T__ pto_tmp__;\
                    pto_tmp__ = (val);\
                    (void)pto_tmp__;\
                }\
                switch (sizeof(var)) {\
                    case 1:\
                        asm(op "b %1,"__percpu_arg(0)\
                            : "+m" (var)\
                            : "qi" ((pto_T__)(val)));\
                        break;\
                    case 2:\
                        asm(op "w %1,"__percpu_arg(0)\
                            : "+m" (var)\
                            : "ri" ((pto_T__)(val)));\
                        break;\
                    case 4:\
                        asm(op "l %1,"__percpu_arg(0)\
                            : "+m" (var)\
                            : "ri" ((pto_T__)(val)));\
                        break;\
                    case 8:\
                        asm(op "q %1,"__percpu_arg(0)\
                            : "+m" (var)\
                            : "re" ((pto_T__)(val)));\
                        break;\
                    default: __bad_percpu_size();\
                }\
            } while (0)

    // значение сохранить в переменной в регистре
    #define percpu_from_op(op, var, constraint)\
            ({\
                typeof(var) pfo_ret__;\
                switch (sizeof(var)) {\
                    case 1:\
                        asm(op "b "__percpu_arg(1)",%0"\
                            : "=q" (pfo_ret__) : constraint);\
                        break;\
                    case 2:\
                        asm(op "w "__percpu_arg(1)",%0"\
                            : "=r" (pfo_ret__) : constraint);\
                        break;\
                    case 4:\
                        asm(op "l "__percpu_arg(1)",%0"\
                            : "=r" (pfo_ret__) : constraint);\
                        break;\
                    case 8:\
                        asm(op "q "__percpu_arg(1)",%0"\
                            : "=r" (pfo_ret__) : constraint);\
                        break;\
                    default: __bad_percpu_size();\
                }\
                pfo_ret__;\
            })

    // макрос выполнение унарной инструкции на процессоре в зависимости от размерам переменной
    // значение сохранить в переменной в памяти
    #define percpu_unary_op(op, var)\
            ({\
                switch (sizeof(var)) {\
                    case 1:\
                        asm(op "b "__percpu_arg(0) : "+m" (var));\
                        break;\
                    case 2:\
                        asm(op "w "__percpu_arg(0) : "+m" (var));\
                        break;\
                    case 4:\
                        asm(op "l "__percpu_arg(0) : "+m" (var));\
                        break;\
                    case 8:\
                        asm(op "q "__percpu_arg(0) : "+m" (var));\
                        break;\
                    default: __bad_percpu_size();\
                }\
            })

    // макрос выполнение инструкции ADD на процессоре
    #define percpu_add_op(var, val)\
            do {\
                typedef typeof(var) pao_T__;\
                const int pao_ID__ = (__builtin_constant_p(val) && ((val) == 1 || (val) == -1)) ? (val) : 0;\
                if (0) {\
                    pao_T__ pao_tmp__;\
                    pao_tmp__ = (val);\
                    (void)pao_tmp__;\
                }\
                switch (sizeof(var)) {\
                    case 1:\
                        if (pao_ID__ == 1)          asm("incb "__percpu_arg(0) : "+m" (var));\
                        else if (pao_ID__ == -1)    asm("decb "__percpu_arg(0) : "+m" (var));\
                        else                        asm("addb %1, "__percpu_arg(0) : "+m" (var) : "qi" ((pao_T__)(val)));\
                        break;\
                    case 2:\
                        if (pao_ID__ == 1)          asm("incw "__percpu_arg(0) : "+m" (var));\
                        else if (pao_ID__ == -1)    asm("decw "__percpu_arg(0) : "+m" (var));\
                        else                        asm("addw %1, "__percpu_arg(0) : "+m" (var) : "ri" ((pao_T__)(val)));\
                        break;							\
                    case 4:								\
                        if (pao_ID__ == 1)          asm("incl "__percpu_arg(0) : "+m" (var));\
                        else if (pao_ID__ == -1)    asm("decl "__percpu_arg(0) : "+m" (var));\
                        else                        asm("addl %1, "__percpu_arg(0) : "+m" (var) : "ri" ((pao_T__)(val)));\
                        break;\
                    case 8:\
                        if (pao_ID__ == 1)          asm("incq "__percpu_arg(0) : "+m" (var));\
                        else if (pao_ID__ == -1)    asm("decq "__percpu_arg(0) : "+m" (var));\
                        else                        asm("addq %1, "__percpu_arg(0) : "+m" (var) : "re" ((pao_T__)(val)));\
                        break;\
                    default: __bad_percpu_size();\
                }\
            } while (0)

    // макрос выполнение инструкции XADD на процессоре
    // обменять операнды и сложить
    #define percpu_add_return_op(var, val)\
            ({\
                typeof(var) paro_ret__ = val;\
                switch (sizeof(var)) {\
                    case 1:\
                        asm("xaddb %0, "__percpu_arg(1)\
                           : "+q" (paro_ret__), "+m" (var) : : "memory");\
                        break;\
                    case 2:	\
                        asm("xaddw %0, "__percpu_arg(1)\
                           : "+r" (paro_ret__), "+m" (var) : : "memory");\
                        break;\
                    case 4:\
                        asm("xaddl %0, "__percpu_arg(1)\
                           : "+r" (paro_ret__), "+m" (var) : : "memory");\
                        break;\
                    case 8:\
                        asm("xaddq %0, "__percpu_arg(1)\
                           : "+re" (paro_ret__), "+m" (var) : : "memory");\
                        break;\
                    default: __bad_percpu_size();\
                }\
                paro_ret__ += val;\
                paro_ret__;\
            })

    // макрос выполнение инструкции XCHG(заменяется cmpxchg) на процессоре
    #define percpu_xchg_op(var, nval)\
        ({\
            typeof(var) pxo_ret__;\
            typeof(var) pxo_new__ = (nval);\
            switch (sizeof(var)) {\
                case 1:\
                    asm("\n\tmov "__percpu_arg(1)",%%al"\
                        "\n1:\tcmpxchgb %2, "__percpu_arg(1)\
                        "\n\tjnz 1b" : "=&a" (pxo_ret__), "+m" (var) : "q" (pxo_new__) : "memory");\
                    break;\
                case 2:\
                    asm("\n\tmov "__percpu_arg(1)",%%ax"\
                        "\n1:\tcmpxchgw %2, "__percpu_arg(1)\
                        "\n\tjnz 1b" : "=&a" (pxo_ret__), "+m" (var) : "r" (pxo_new__) : "memory");\
                    break;\
                case 4:\
                    asm("\n\tmov "__percpu_arg(1)",%%eax"\
                        "\n1:\tcmpxchgl %2, "__percpu_arg(1)\
                        "\n\tjnz 1b" : "=&a" (pxo_ret__), "+m" (var) : "r" (pxo_new__) : "memory");\
                    break;\
                case 8:\
                    asm("\n\tmov "__percpu_arg(1)",%%rax"\
                        "\n1:\tcmpxchgq %2, "__percpu_arg(1)\
                        "\n\tjnz 1b" : "=&a" (pxo_ret__), "+m" (var) : "r" (pxo_new__) : "memory");\
                    break;\
                default: __bad_percpu_size();\
            }\
            pxo_ret__;\
        })

    // макрос выполнение инструкции CMPXCHG на процессоре
    #define percpu_cmpxchg_op(var, oval, nval)\
            ({\
                typeof(var) pco_ret__;\
                typeof(var) pco_old__ = (oval);\
                typeof(var) pco_new__ = (nval);\
                switch (sizeof(var)) {\
                    case 1:\
                        asm("cmpxchgb %2, "__percpu_arg(1)\ : "=a" (pco_ret__), "+m" (var)\
                           : "q" (pco_new__), "0" (pco_old__) : "memory");\
                        break;\
                    case 2:\
                        asm("cmpxchgw %2, "__percpu_arg(1) : "=a" (pco_ret__), "+m" (var)\
                           : "r" (pco_new__), "0" (pco_old__) : "memory");\
                        break;\
                    case 4:\
                        asm("cmpxchgl %2, "__percpu_arg(1) : "=a" (pco_ret__), "+m" (var)\
                           : "r" (pco_new__), "0" (pco_old__) : "memory");\
                        break;\
                    case 8:\
                        asm("cmpxchgq %2, "__percpu_arg(1) : "=a" (pco_ret__), "+m" (var)\
                           : "r" (pco_new__), "0" (pco_old__) : "memory");\
                        break;\
                    default: __bad_percpu_size();\
                }\
                pco_ret__;\
            })

    // для статически выделенных переменных без стека
    #define this_cpu_read_stable(var)   percpu_from_op("mov", var, "p" (&(var)))

    #define __this_cpu_read_1(pcp)      percpu_from_op("mov", (pcp), "m"(pcp))
    #define __this_cpu_read_2(pcp)      percpu_from_op("mov", (pcp), "m"(pcp))
    #define __this_cpu_read_4(pcp)      percpu_from_op("mov", (pcp), "m"(pcp))

    #define __this_cpu_write_1(pcp, val)	percpu_to_op("mov", (pcp), val)
    #define __this_cpu_write_2(pcp, val)	percpu_to_op("mov", (pcp), val)
    #define __this_cpu_write_4(pcp, val)	percpu_to_op("mov", (pcp), val)

    #define __this_cpu_add_1(pcp, val)	percpu_add_op((pcp), val)
    #define __this_cpu_add_2(pcp, val)	percpu_add_op((pcp), val)
    #define __this_cpu_add_4(pcp, val)	percpu_add_op((pcp), val)

    #define __this_cpu_and_1(pcp, val)	percpu_to_op("and", (pcp), val)
    #define __this_cpu_and_2(pcp, val)	percpu_to_op("and", (pcp), val)
    #define __this_cpu_and_4(pcp, val)	percpu_to_op("and", (pcp), val)

    #define __this_cpu_or_1(pcp, val)	percpu_to_op("or", (pcp), val)
    #define __this_cpu_or_2(pcp, val)	percpu_to_op("or", (pcp), val)
    #define __this_cpu_or_4(pcp, val)	percpu_to_op("or", (pcp), val)

    #define __this_cpu_xor_1(pcp, val)	percpu_to_op("xor", (pcp), val)
    #define __this_cpu_xor_2(pcp, val)	percpu_to_op("xor", (pcp), val)
    #define __this_cpu_xor_4(pcp, val)	percpu_to_op("xor", (pcp), val)

    #define __this_cpu_xchg_1(pcp, val)	percpu_xchg_op(pcp, val)
    #define __this_cpu_xchg_2(pcp, val)	percpu_xchg_op(pcp, val)
    #define __this_cpu_xchg_4(pcp, val)	percpu_xchg_op(pcp, val)

    #define this_cpu_read_1(pcp)		percpu_from_op("mov", (pcp), "m"(pcp))
    #define this_cpu_read_2(pcp)		percpu_from_op("mov", (pcp), "m"(pcp))
    #define this_cpu_read_4(pcp)		percpu_from_op("mov", (pcp), "m"(pcp))

    #define this_cpu_write_1(pcp, val)	percpu_to_op("mov", (pcp), val)
    #define this_cpu_write_2(pcp, val)	percpu_to_op("mov", (pcp), val)
    #define this_cpu_write_4(pcp, val)	percpu_to_op("mov", (pcp), val)

    #define this_cpu_add_1(pcp, val)	percpu_add_op((pcp), val)
    #define this_cpu_add_2(pcp, val)	percpu_add_op((pcp), val)
    #define this_cpu_add_4(pcp, val)	percpu_add_op((pcp), val)

    #define this_cpu_and_1(pcp, val)	percpu_to_op("and", (pcp), val)
    #define this_cpu_and_2(pcp, val)	percpu_to_op("and", (pcp), val)
    #define this_cpu_and_4(pcp, val)	percpu_to_op("and", (pcp), val)

    #define this_cpu_or_1(pcp, val)		percpu_to_op("or", (pcp), val)
    #define this_cpu_or_2(pcp, val)		percpu_to_op("or", (pcp), val)
    #define this_cpu_or_4(pcp, val)		percpu_to_op("or", (pcp), val)

    #define this_cpu_xor_1(pcp, val)	percpu_to_op("xor", (pcp), val)
    #define this_cpu_xor_2(pcp, val)	percpu_to_op("xor", (pcp), val)
    #define this_cpu_xor_4(pcp, val)	percpu_to_op("xor", (pcp), val)

    #define this_cpu_xchg_1(pcp, nval)	percpu_xchg_op(pcp, nval)
    #define this_cpu_xchg_2(pcp, nval)	percpu_xchg_op(pcp, nval)
    #define this_cpu_xchg_4(pcp, nval)	percpu_xchg_op(pcp, nval)

    #define __this_cpu_add_return_1(pcp, val)       percpu_add_return_op(pcp, val)
    #define __this_cpu_add_return_2(pcp, val)       percpu_add_return_op(pcp, val)
    #define __this_cpu_add_return_4(pcp, val)       percpu_add_return_op(pcp, val)

    #define __this_cpu_cmpxchg_1(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)
    #define __this_cpu_cmpxchg_2(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)
    #define __this_cpu_cmpxchg_4(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)

    #define this_cpu_add_return_1(pcp, val)         percpu_add_return_op(pcp, val)
    #define this_cpu_add_return_2(pcp, val) 	percpu_add_return_op(pcp, val)
    #define this_cpu_add_return_4(pcp, val)         percpu_add_return_op(pcp, val)

    #define this_cpu_cmpxchg_1(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)
    #define this_cpu_cmpxchg_2(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)
    #define this_cpu_cmpxchg_4(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)

    #ifdef CONFIG_X86_64
        #define __this_cpu_read_8(pcp)		percpu_from_op("mov", (pcp), "m"(pcp))
        #define __this_cpu_write_8(pcp, val)	percpu_to_op("mov", (pcp), val)
        #define __this_cpu_add_8(pcp, val)          percpu_add_op((pcp), val)
        #define __this_cpu_and_8(pcp, val)          percpu_to_op("and", (pcp), val)
        #define __this_cpu_or_8(pcp, val)           percpu_to_op("or", (pcp), val)
        #define __this_cpu_xor_8(pcp, val)          percpu_to_op("xor", (pcp), val)
        #define __this_cpu_add_return_8(pcp, val)   percpu_add_return_op(pcp, val)
        #define __this_cpu_xchg_8(pcp, nval)	percpu_xchg_op(pcp, nval)
        #define __this_cpu_cmpxchg_8(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)

        #define this_cpu_read_8(pcp)		percpu_from_op("mov", (pcp), "m"(pcp))
        #define this_cpu_write_8(pcp, val)          percpu_to_op("mov", (pcp), val)
        #define this_cpu_add_8(pcp, val)            percpu_add_op((pcp), val)
        #define this_cpu_and_8(pcp, val)            percpu_to_op("and", (pcp), val)
        #define this_cpu_or_8(pcp, val)		percpu_to_op("or", (pcp), val)
        #define this_cpu_xor_8(pcp, val)            percpu_to_op("xor", (pcp), val)
        #define this_cpu_add_return_8(pcp, val)	percpu_add_return_op(pcp, val)
        #define this_cpu_xchg_8(pcp, nval)          percpu_xchg_op(pcp, nval)
        #define this_cpu_cmpxchg_8(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)

        #define percpu_cmpxchg16b_double(pcp1, pcp2, o1, o2, n1, n2)\
                ({\
                    bool __ret;\
                    typeof(pcp1) __o1 = (o1), __n1 = (n1);\
                    typeof(pcp2) __o2 = (o2), __n2 = (n2);\
                    alternative_io("leaq %P1,%%rsi\n\tcall this_cpu_cmpxchg16b_emu\n\t",\
                                   "cmpxchg16b " __percpu_arg(1) "\n\tsetz %0\n\t", X86_FEATURE_CX16,\
                                   ASM_OUTPUT2("=a" (__ret), "+m" (pcp1), "+m" (pcp2), "+d" (__o2)),\
                                   "b" (__n1), "c" (__n2), "a" (__o1) : "rsi");\
                    __ret;\
                })

        #define __this_cpu_cmpxchg_double_8 percpu_cmpxchg16b_double
        #define this_cpu_cmpxchg_double_8   percpu_cmpxchg16b_double
    #endif

    #include <percpu-defs.h>

    DECLARE_PER_CPU(unsigned long, this_cpu_off);
#endif
#endif /* ARCH_X86_PERCPU_H */