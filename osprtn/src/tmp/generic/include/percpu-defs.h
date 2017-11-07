#ifndef GENERIC_PERCPU_DEFS_H
#define GENERIC_PERCPU_DEFS_H
// проверка указателя ptr
// + 0 - преобразовать указатель на массив в указатель на один элемент
#define __verify_percpu_ptr(ptr)\
        do {\
            const void __percpu *__vpp_verify = (typeof(ptr))NULL;\
            (void)__vpp_verify;\
        } while (0)

#ifdef CONFIG_SMP
    #ifndef __per_cpu_offset
    extern unsigned long __per_cpu_offset[NR_CPUS];

    #define per_cpu_offset(x)   (__per_cpu_offset[x])
    #endif

    #ifndef SHIFT_PERCPU_PTR
    #define SHIFT_PERCPU_PTR(__p, __offset)	({				\
            __verify_percpu_ptr((__p));					\
            RELOC_HIDE((typeof(*(__p)) __kernel __force *)(__p), (__offset)); \
    })
    #endif

    #define per_cpu(var, cpu)   (*SHIFT_PERCPU_PTR(&(var), per_cpu_offset(cpu)))   
    #define per_cpu_ptr(ptr, cpu) ({  __verify_percpu_ptr(ptr); SHIFT_PERCPU_PTR((ptr), per_cpu_offset((cpu))); })
#else
    #define VERIFY_PERCPU_PTR(__p)\
            ({\
                __verify_percpu_ptr((__p));\
                (typeof(*(__p)) __kernel __force *)(__p);\
            })

    #define per_cpu(var, cpu)       (*per_cpu_ptr(&(var), cpu))

    #define __get_cpu_var(var)      (*VERIFY_PERCPU_PTR(&(var)))

    #define per_cpu_ptr(ptr, cpu)   ({ (void)(cpu); VERIFY_PERCPU_PTR(ptr); })
    #define this_cpu_ptr(ptr)       per_cpu_ptr(ptr, 0)
    #define __this_cpu_ptr(ptr)     this_cpu_ptr(ptr)    
#endif

#ifndef PER_CPU_BASE_SECTION
    #ifdef CONFIG_SMP
    #define PER_CPU_BASE_SECTION    ".data..percpu"
    #else
    #define PER_CPU_BASE_SECTION    ".data"
    #endif
#endif

#ifdef CONFIG_SMP
    #ifdef MODULE
    #define PER_CPU_SHARED_ALIGNED_SECTION  ""
    #define PER_CPU_ALIGNED_SECTION         ""
    #else
    #define PER_CPU_SHARED_ALIGNED_SECTION  "..shared_aligned"
    #define PER_CPU_ALIGNED_SECTION         "..shared_aligned"
    #endif
    
    #define PER_CPU_FIRST_SECTION           "..first"
#else
    #define PER_CPU_SHARED_ALIGNED_SECTION  ""
    #define PER_CPU_ALIGNED_SECTION         "..shared_aligned"
    #define PER_CPU_FIRST_SECTION           ""
#endif
    
#ifndef PER_CPU_ATTRIBUTES
#define PER_CPU_ATTRIBUTES
#endif

#ifndef PER_CPU_DEF_ATTRIBUTES
#define PER_CPU_DEF_ATTRIBUTES
#endif

#define __PCPU_ATTRS(sec)   __percpu __attribute__((section(PER_CPU_BASE_SECTION sec))) PER_CPU_ATTRIBUTES

// отключение секции discard
#define __PCPU_DUMMY_ATTRS  __attribute__((section(".discard"), unused))

// объявление / определение перенных
#define DECLARE_PER_CPU_SECTION(type, name, sec)    extern __PCPU_ATTRS(sec) __typeof__(type) name
#define DEFINE_PER_CPU_SECTION(type, name, sec)     __PCPU_ATTRS(sec) PER_CPU_DEF_ATTRIBUTES __typeof__(type) name

// объявление / определение перенных на текущем процессоре
#define DECLARE_PER_CPU(type, name) DECLARE_PER_CPU_SECTION(type, name, "")
#define DEFINE_PER_CPU(type, name)  DEFINE_PER_CPU_SECTION(type, name, "")
    
// объявление / определение перенных выровненных в области shared
#define DECLARE_PER_CPU_SHARED_ALIGNED(type, name)\
        DECLARE_PER_CPU_SECTION(type, name, PER_CPU_SHARED_ALIGNED_SECTION) ____cacheline_aligned_in_smp

#define DEFINE_PER_CPU_SHARED_ALIGNED(type, name)\
        DEFINE_PER_CPU_SECTION(type, name, PER_CPU_SHARED_ALIGNED_SECTION) ____cacheline_aligned_in_smp
    
// объявление / определение для каждого процессора переменные, которые должны быть выровнены на начало страницы.    
#define DECLARE_PER_CPU_PAGE_ALIGNED(type, name) DECLARE_PER_CPU_SECTION(type, name, "..page_aligned") __aligned(PAGE_SIZE)
#define DEFINE_PER_CPU_PAGE_ALIGNED(type, name) DEFINE_PER_CPU_SECTION(type, name, "..page_aligned") __aligned(PAGE_SIZE)
    
    
#endif /* GENERIC_PERCPU_DEFS_H */