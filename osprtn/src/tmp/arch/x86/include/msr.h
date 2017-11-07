#ifndef ARCH_X86_MSR_H
#define ARCH_X86_MSR_H

#include _SOS_CPU_HDR_DIR_(asm.h)
#include _SOS_CPU_HDR_DIR_(errno.h)

// модели зависимые регистры msr
#define X86_MSR_EFER		0xc0000080 //регистр с расширенными свойствами
#define X86_MSR_STAR		0xc0000081 //устаревший режим SYSCALL целевой
#define X86_MSR_LSTAR		0xc0000082 //длинный режим SYSCALL целевой
#define X86_MSR_CSTAR		0xc0000083 //компактный режим SYSCALL целевой
#define X86_MSR_SYSCALL_MASK	0xc0000084 //RFLAGS маска для SYSCALL
#define X86_MSR_FS_BASE		0xc0000100 //64bit FS база
#define X86_MSR_GS_BASE		0xc0000101 //64bit GS база
#define X86_MSR_KERNEL_GS_BASE	0xc0000102 //SwapGS kernel GS база
#define X86_MSR_TSC_AUX		0xc0000103 //вспомогательный TSC

// биты EFER
#define _EFER_SCE		0  //SYSCALL/SYSRET
#define _EFER_LME		8  //длительный режим включить
#define _EFER_LMA		10 //длительный режим активный (только для чтения)
#define _EFER_NXE		11 //не выполнять включить
#define _EFER_SVME		12 //включить виртуализацию
#define _EFER_LMSLE		13 //длинный сегмент ограничить режим включить
#define _EFER_FFXSR		14 //включить быстрые FXSAVE/FXRSTOR

#define EFER_SCE		(1<<_EFER_SCE)
#define EFER_LME		(1<<_EFER_LME)
#define EFER_LMA		(1<<_EFER_LMA)
#define EFER_NXE		(1<<_EFER_NXE)
#define EFER_SVME		(1<<_EFER_SVME)
#define EFER_LMSLE		(1<<_EFER_LMSLE)
#define EFER_FFXSR		(1<<_EFER_FFXSR)

// фиксированный диапазон MTRRs
#define MSR_PLATFORM_INFO		0x000000ce
#define MSR_MTRRcap			0x000000fe
#define MSR_IA32_BBL_CR_CTL		0x00000119
#define MSR_IA32_BBL_CR_CTL3		0x0000011e

#define MSR_IA32_SYSENTER_CS		0x00000174
#define MSR_IA32_SYSENTER_ESP		0x00000175
#define MSR_IA32_SYSENTER_EIP		0x00000176 

#define X86_MSR_MTRRfix64K_00000	0x00000250
#define X86_MSR_MTRRfix16K_80000	0x00000258
#define X86_MSR_MTRRfix16K_A0000	0x00000259
#define X86_MSR_MTRRfix4K_C0000		0x00000268
#define X86_MSR_MTRRfix4K_C8000		0x00000269
#define X86_MSR_MTRRfix4K_D0000		0x0000026a
#define X86_MSR_MTRRfix4K_D8000		0x0000026b
#define X86_MSR_MTRRfix4K_E0000		0x0000026c
#define X86_MSR_MTRRfix4K_E8000		0x0000026d
#define X86_MSR_MTRRfix4K_F0000		0x0000026e
#define X86_MSR_MTRRfix4K_F8000		0x0000026f
#define X86_MSR_MTRRdefType		0x000002ff

// структура msr регистра
struct x86_msr_struct {
    union {
        struct {
            _Uint32t l;
            _Uint32t h;
        };
        
        _Uint64t q;
    };
};

struct x86_msr_info_struct {
    _Uint32t msr_no;
    struct x86_msr_struct reg;
    struct x86_msr_struct *msrs;
    int err;
};

struct x86_msr_regs_info_struct {
    _Uint32t *regs;
    int err;
};

// чтение счетчика времени
static inline unsigned long long native_read_tscp(unsigned int *aux)
{
	unsigned long low, high;
        
        // rtscp - для новые процессоров
	asm volatile(".byte 0x0f,0x01,0xf9" 
		     : "=a" (low), "=d" (high), "=c" (*aux));
	return low | ((_Uint64t)high << 32);
}

#ifdef CONFIG_X86_64
    #define DECLARE_ARGS(val, low, high)    unsigned low, high
    #define EAX_EDX_VAL(val, low, high)     ((low) | ((u64)(high) << 32))
    #define EAX_EDX_ARGS(val, low, high)    "a" (low), "d" (high)
    #define EAX_EDX_RET(val, low, high)     "=a" (low), "=d" (high)
    #define EDX_EAX_RET(val, high, low)     EAX_EDX_RET(val, low, high)
#else
    #define DECLARE_ARGS(val, low, high)    unsigned long long val
    #define EAX_EDX_VAL(val, low, high)     (val)
    #define EAX_EDX_ARGS(val, low, high)    "A" (val)
    #define EAX_EDX_RET(val, low, high)     "=A" (val)
    #define EDX_EAX_RET(val, high, low)     EAX_EDX_RET(val, low, high)
#endif

// чтение из регистра MSR
static inline unsigned long long native_read_msr(unsigned int msr)
{
    DECLARE_ARGS(val, low, high);

    asm volatile("rdmsr" : EDX_EAX_RET(val, high, low) : "c" (msr));
    return EAX_EDX_VAL(val, low, high);
}

// запись в регистр MSR
static inline void native_write_msr(unsigned int msr, unsigned low, unsigned high)
{
    asm volatile("wrmsr" : : "c" (msr), "a"(low), "d" (high) : "memory");
}

// чтение регистра MSR и возврат ошибки в защищенном режиме
// заносим значение требуемого регистра MSR => ECX
// получаем из регистров EDX:EAX
static inline unsigned long long native_read_msr_safe(unsigned int msr, int *err)
{
    DECLARE_ARGS(val, low, high);

    asm volatile("2: rdmsr; xor %[err],%[err]\n"
                 "1:\n\t"
                 ".section .fixup,\"ax\"\n\t"
                 "3:  mov %[fault],%[err]; jmp 1b\n\t"
                 ".previous\n\t"
                 _ASM_EXTABLE(2b, 3b)
                 : [err] "=r" (*err), EDX_EAX_RET(val, high, low)
                 : "c" (msr), [fault] "i" (-EIO));
    return EAX_EDX_VAL(val, low, high);
}

// запись значения в требуемый регистр MSR
static inline int native_write_msr_safe(unsigned int msr, unsigned low, unsigned high)
{
    int err;
    
    asm volatile("2: wrmsr ; xor %[err],%[err]\n"
                 "1:\n\t"
                 ".section .fixup,\"ax\"\n\t"
                 "3:  mov %[fault],%[err] ; jmp 1b\n\t"
                 ".previous\n\t"
                 _ASM_EXTABLE(2b, 3b)
                 : [err] "=a" (err)
                 : "c" (msr), "0" (low), "d" (high), [fault] "i" (-EIO)
                 : "memory");
    return err;
}

// чтение счетчика TSC и значение возвращается в регистрах EDX:EAX 
static __always_inline unsigned long long __native_read_tsc(void)
{
    DECLARE_ARGS(val, low, high);

    asm volatile("rdtsc" : EDX_EAX_RET(val, high, low));
    return EAX_EDX_VAL(val, low, high);
}

// чтение счетчика мониторинга производительности
static inline unsigned long long native_read_pmc(int counter)
{
    DECLARE_ARGS(val, low, high);

    asm volatile("rdpmc" : EDX_EAX_RET(val, low, high) : "c" (counter));
    return EAX_EDX_VAL(val, low, high);       
}

// чтение из регистра спецификации модели MRS
#define rdmsr(msr, low, high)\
    do {\
        _Uint64t __val = native_read_msr((msr));\
        (void)((low) = (_Uint32t)__val);\
        (void)((high) = (_Uint32t)(__val >> 32));\
    } while (0)

// запись в регистр спецификации модели MSR
static inline void wrmsr(unsigned msr, unsigned low, unsigned high)
{
    native_write_msr(msr, low, high);
}

#define rdmsrl(msr, val)    ((val) = native_read_msr((msr)))
#define wrmsrl(msr, val)    native_write_msr((msr), (_Uint32t)((_Uint64t)(val)), (_Uint32t)((_Uint64t)(val) >> 32)) 

static inline int wrmsr_safe(unsigned msr, unsigned low, unsigned high)
{
    return native_write_msr_safe(msr, low, high);
}

#define rdmsr_safe(msr, low, high)\
    ({\
        int __err;\
        _Uint64t __val = native_read_msr_safe((msr), &__err);\
        (*low) = (_Uint32t)__val;\
        (*high) = (_Uint32t)(__val >> 32);\
        __err;\
    })

static inline int rdmsrl_safe(unsigned msr, unsigned long long *p)
{
    int err;

    *p = native_read_msr_safe(msr, &err);
    return err;
}

#define rdtscl(low)     ((low) = (_Uint32t)__native_read_tsc())
#define rdtscll(val)    ((val) = __native_read_tsc())

#endif /* ARCH_X86_MSR_H */