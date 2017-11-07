#ifndef ARCH_X86_PROCESSOR_H
#define ARCH_X86_PROCESSOR_H

#include _SOS_CPU_HDR_DIR_(processor-flags.h)
#include _SOS_CPU_HDR_DIR_(math-emu.h)
#include _SOS_CPU_HDR_DIR_(segment.h)
#include _SOS_CPU_HDR_DIR_(cpu-feature.h)
#include _SOS_CPU_HDR_DIR_(page.h)
#include _SOS_CPU_HDR_DIR_(msr.h)
#include _SOS_CPU_HDR_DIR_(desc-defs.h)

#include <cache.h>
#include <percpu.h>
#include <stddef.h>
#include <irq-flags.h>

// структура TSS зависищая от железа
#ifdef CONFIG_X86_32
struct x86_hardware_tss_struct {
	unsigned short  back_link, __blh;   // поле обратной связи - информация о предыдущей задачи
	// определяет стек - зависит от уровня привилегий
        unsigned long   sp0;
	unsigned short  ss0, __ss0h;
	unsigned long   sp1;
	unsigned short  ss1, __ss1h;
	unsigned long	sp2;
	unsigned short	ss2, __ss2h;
        
	unsigned long	__cr3;
	unsigned long	ip;
	unsigned long	flags;
        
	unsigned long	ax;
	unsigned long	cx;
	unsigned long	dx;
	unsigned long	bx;
	unsigned long	sp;
	unsigned long	bp;
	unsigned long	si;
	unsigned long	di;
	unsigned short	es, __esh;
	unsigned short	cs, __csh;
	unsigned short	ss, __ssh;
	unsigned short	ds, __dsh;
	unsigned short	fs, __fsh;
	unsigned short	gs, __gsh;
        
	unsigned short	ldt, __ldth;
	unsigned short	trace;
	unsigned short	io_bitmap_base;
}__attribute__((packed));
#else
struct x86_hardware_tss_struct {
    _Uint32t    reserved1;
    _Uint64t	sp0;
    _Uint64t	sp1;
    _Uint64t	sp2;
    _Uint64t	reserved2;
    _Uint64t	ist[7];
    _Uint32t	reserved3;
    _Uint32t	reserved4;
    _Uint16t	reserved5;
    _Uint16t	io_bitmap_base;
}__attribute__((packed)) ____cacheline_aligned;
#endif

// IO битовый массив
#define IO_BITMAP_BITS			65536
#define IO_BITMAP_BYTES			(IO_BITMAP_BITS / 8)
#define IO_BITMAP_LONGS			(IO_BITMAP_BYTES / sizeof(long))
#define IO_BITMAP_OFFSET		offsetof(struct tss_struct, io_bitmap)
#define INVALID_IO_BITMAP_OFFSET	0x8000

// структура TSS
struct tss_struct {
    struct x86_hardware_tss_struct  x86_tss;
    unsigned long                   io_bitmap[IO_BITMAP_LONGS + 1];
    unsigned long                   stack[64];
}____cacheline_aligned;

//DECLARE_PER_CPU_SHARED_ALIGNED(struct tss_struct, init_tss);

struct x86_cpuinfo_struct {
	_Uint8t			x86;		// кодовое имя
	_Uint8t			x86_vendor;	// производитель
	_Uint8t			x86_model;      // модель
	_Uint8t			x86_mask;
#ifdef CONFIG_X86_32
	char			wp_works_ok;	/* It doesn't on 386's */

	/* Problems on some 486Dx4's and old 386's: */
	char			hard_math;
	char			rfu;
	char			pad0;
#else
	/* Number of 4K pages in DTLB/ITLB combined(in pages): */
	int			x86_tlbsize;
#endif
	_Uint8t			x86_virt_bits;
	_Uint8t			x86_phys_bits;
	/* CPUID returned core id bits: */
	_Uint8t			x86_coreid_bits;
	/* Max extended CPUID function supported: */
	_Uint32t		extended_cpuid_level;
	int			cpuid_level;    // уровень максимальной поддержки CPUID; -1 - нет
	_Uint32t		x86_capability[NCAPINTS + NBUGINTS];
	char			x86_vendor_id[16];
	char			x86_model_id[64];
	/* in KB - valid for CPUS which support this call: */
	int			x86_cache_size;
	int			x86_cache_alignment;	/* In bytes */
	int			x86_power;
	unsigned long		loops_per_jiffy;
	_Uint16t		x86_max_cores;  //CPUID возвращает максимальное значение ядер
	_Uint16t		apicid;
	_Uint16t		initial_apicid;
	_Uint16t		x86_clflush_size;
	_Uint16t		booted_cores;   // количество ядер видных в OS
	_Uint16t		phys_proc_id;   // физический id процессора
	_Uint16t		cpu_core_id;    // id ядра
	/* Compute unit id */
	_Uint8t			compute_unit_id;
	/* Index into per_cpu list: */
	_Uint16t		cpu_index;
	_Uint32t		microcode;      // микрокод процессора
}__attribute__((__aligned__(SMP_CACHE_BYTES)));

#define X86_VENDOR_INTEL	0
#define X86_VENDOR_CYRIX	1
#define X86_VENDOR_AMD		2
#define X86_VENDOR_UMC		3
#define X86_VENDOR_CENTAUR	5
#define X86_VENDOR_TRANSMETA	7
#define X86_VENDOR_NSC		8
#define X86_VENDOR_NUM		9

#define X86_VENDOR_UNKNOWN	0xff

// возможности CPU 
extern struct x86_cpuinfo_struct boot_cpu_data;
extern struct x86_cpuinfo_struct new_cpu_data;

extern _Uint32t cpu_caps_cleared[NCAPINTS]; // не установленные флаги
extern _Uint32t cpu_caps_set[NCAPINTS];     // установленные флаги

// структура FSAVE
struct i387_fsave_struct {
    _Uint32t    cwd;	/* FPU Control Word		*/
    _Uint32t    swd;	/* FPU Status Word		*/
    _Uint32t    twd;	/* FPU Tag Word			*/
    _Uint32t    fip;	/* FPU IP Offset		*/
    _Uint32t    fcs;	/* FPU IP Selector		*/
    _Uint32t    foo;	/* FPU Operand Pointer Offset	*/
    _Uint32t    fos;	/* FPU Operand Pointer Selector	*/

    /* 8*10 bytes for each FP-reg = 80 bytes:			*/
    _Uint32t    st_space[20];

    /* Software status information [not touched by FSAVE ]:		*/
    _Uint32t    status;
};

// структура FXSAVE
struct i387_fxsave_struct {
    _Uint16t    cwd; /* Control Word			*/
    _Uint16t	swd; /* Status Word			*/
    _Uint16t	twd; /* Tag Word			*/
    _Uint16t	fop; /* Last Instruction Opcode		*/
    union {
        struct {
            _Uint64t	rip; /* Instruction Pointer		*/
            _Uint64t	rdp; /* Data Pointer			*/
        };
        struct {
            _Uint32t	fip; /* FPU IP Offset			*/
            _Uint32t	fcs; /* FPU IP Selector			*/
            _Uint32t	foo; /* FPU Operand Offset		*/
            _Uint32t	fos; /* FPU Operand Selector		*/
        };
    };
    
    _Uint32t    mxcsr;		/* MXCSR Register State */
    _Uint32t    mxcsr_mask;	/* MXCSR Mask		*/
    /* 8*16 bytes for each FP-reg = 128 bytes:*/
    _Uint32t    st_space[32];
    /* 16*16 bytes for each XMM-reg = 256 bytes:*/
    _Uint32t    xmm_space[64];
    _Uint32t    padding[12];

    union {
        _Uint32t    padding1[12];
        _Uint32t    sw_reserved[12];
    };
}__attribute__((aligned(16)));

// программный сопроцессор
struct i387_soft_struct {
    _Uint32t    cwd;
    _Uint32t	swd;
    _Uint32t	twd;
    _Uint32t	fip;
    _Uint32t	fcs;
    _Uint32t	foo;
    _Uint32t	fos;
    /* 8*10 bytes for each FP-reg = 80 bytes: */
    _Uint32t	st_space[20];
    _Uint8t	ftop;
    _Uint8t	changed;
    _Uint8t	lookahead;
    _Uint8t	no_update;
    _Uint8t	rm;
    _Uint8t	alimit;
    struct math_emu_info_struct *info;
    _Uint32t	entry_eip;
};

// векторные регистры YMM - 16 X 128bit (старшая часть)
struct x86_ymmh_regs_struct {
    _Uint32t ymmh_space[64];
};

// регистры BND - 4 X 128bit (регистры состояния памяти)
struct x86_bnd_regs_struct {
    _Uint64t bndregs[8];
}__attribute__((packed)); 

// конфигурационный и статусный регистры BND
struct bndcsr_struct {
    _Uint64t config_reg;
    _Uint64t status_reg;
}__attribute__((packed));

struct xsave_hdr_struct {
    _Uint64t xstate_bv;
    _Uint64t reserved1[2];
    _Uint64t reserved2[5];
}__attribute__((packed));

struct xsave_struct {
    struct i387_fxsave_struct i387;
    struct xsave_hdr_struct xsave_hdr;
    struct x86_ymmh_regs_struct ymmh;
	//RH_KABI_EXTEND(struct lwp_struct lwp)
	//RH_KABI_EXTEND(struct bndregs_struct bndregs)
	//RH_KABI_EXTEND(struct bndcsr_struct bndcsr)
	/* new processor state extensions will go here */
}__attribute__((packed, aligned(64)));

union thread_xstate_struct {
    struct i387_fsave_struct	fsave;
    struct i387_fxsave_struct	fxsave;
    struct i387_soft_struct     soft;
    struct xsave_struct		xsave;
};

struct fpu_struct {
    unsigned int last_cpu;
    unsigned int has_fpu;
    union thread_xstate_struct *state;
};

// структура нити
struct thread_struct {
    struct x86_desc_struct  tls_array[GDT_ENTRY_TLS_ENTRIES];   // кэширование локальной памяти потока
    unsigned long           sp0;
    unsigned long           sp;
#ifdef CONFIG_X86_32
    unsigned long           sysenter_cs;
#else
    unsigned long           usersp;	/* Copy from PDA */
    unsigned short          es;
    unsigned short          ds;
    unsigned short          fsindex;
    unsigned short          gsindex;
#endif  
};

// структура сегмента в памяти
typedef struct {
    unsigned long seg;
} mm_segment_t;

// установить IOPL бит в регистре флагов EFLAGS
#define set_iopl_mask   native_set_iopl_mask

static inline void native_set_iopl_mask(unsigned mask)
{
#ifdef CONFIG_X86_32
    unsigned int reg;

    asm volatile ("pushfl;"
                  "popl %0;"
                  "andl %1, %0;"
                  "orl %2, %0;"
                  "pushl %0;"
                  "popfl"
                  : "=&r" (reg) : "i" (~X86_EFLAGS_IOPL), "r" (mask));
#endif
}

// загрузка регистра SP на нулевом уровне из структуры нити в структуру TSS
static inline void native_load_sp0(struct tss_struct *tss, struct thread_struct *thread)
{
    tss->x86_tss.sp0 = thread->sp0;
        
    #ifdef CONFIG_X86_32
        if (unlikely(tss->x86_tss.ss1 != thread->sysenter_cs))
        {
            tss->x86_tss.ss1 = thread->sysenter_cs;
            wrmsr(MSR_IA32_SYSENTER_CS, thread->sysenter_cs, 0);    // запись в регистр MSR_IA32_SYSENTER_CS
        }
    #endif
}

static inline void load_sp0(struct tss_struct *tss, struct thread_struct *thread)
{
    native_load_sp0(tss, thread);
}

// определение для регистра CPUID
#define __cpuid native_cpuid

static inline void native_cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
{
    /* ecx is often an input as well as an output. */
    asm volatile("cpuid" : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx) 
                         : "0" (*eax), "2" (*ecx) : "memory");
}

static inline void cpuid(unsigned int op, unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
{
    *eax = op;
    *ecx = 0;
    __cpuid(eax, ebx, ecx, edx);
}

static inline void cpuid_count(unsigned int op, int count, unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
{
	*eax = op;
	*ecx = count;
	__cpuid(eax, ebx, ecx, edx);
}

static inline unsigned int cpuid_eax(unsigned int op)
{
    unsigned int eax, ebx, ecx, edx;

    cpuid(op, &eax, &ebx, &ecx, &edx);
    return eax;
}

static inline unsigned int cpuid_ebx(unsigned int op)
{
    unsigned int eax, ebx, ecx, edx;

    cpuid(op, &eax, &ebx, &ecx, &edx);
    return ebx;
}

static inline unsigned int cpuid_ecx(unsigned int op)
{
    unsigned int eax, ebx, ecx, edx;

    cpuid(op, &eax, &ebx, &ecx, &edx);
    return ecx;
}

static inline unsigned int cpuid_edx(unsigned int op)
{
    unsigned int eax, ebx, ecx, edx;

    cpuid(op, &eax, &ebx, &ecx, &edx);
    return edx;
}

static inline void rep_nop(void)
{
    asm volatile("rep; nop" ::: "memory");
}

static inline void cpu_relax(void)
{
    rep_nop();
}

#ifdef CONFIG_X86_32
    // размер задачи
    #define TASK_SIZE       PAGE_OFFSET
    #define TASK_SIZE_MAX   TASK_SIZE
#else
#endif

#endif /* ARCH_X86_PROCESSOR_H */