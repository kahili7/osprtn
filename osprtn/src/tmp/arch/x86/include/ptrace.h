#ifndef ARCH_X86_PTRACE_H
#define ARCH_X86_PTRACE_H

#include _SOS_CPU_HDR_DIR_(segment.h)
/*
 * позволяет трассировать и отлаживать процесс
 */

#ifdef __i386__
    #define EBX 0
    #define ECX 1
    #define EDX 2
    #define ESI 3
    #define EDI 4
    #define EBP 5
    #define EAX 6
    #define DS 7
    #define ES 8
    #define FS 9
    #define GS 10
    #define ORIG_EAX 11
    #define EIP 12
    #define CS  13
    #define EFL 14
    #define UESP 15
    #define SS   16
    #define FRAME_SIZE 17
#else
    #define R15 0
    #define R14 8
    #define R13 16
    #define R12 24
    #define RBP 32
    #define RBX 40
    /* arguments: interrupts/non tracing syscalls only save up to here*/
    #define R11 48
    #define R10 56
    #define R9 64
    #define R8 72
    #define RAX 80
    #define RCX 88
    #define RDX 96
    #define RSI 104
    #define RDI 112
    #define ORIG_RAX 120       /* = ERROR */
    /* end of arguments */
    /* cpu exception frame or undefined in case of fast syscall. */
    #define RIP 128
    #define CS 136
    #define EFLAGS 144
    #define RSP 152
    #define SS 160
    #define ARGOFFSET R11
    #define FRAME_SIZE 168
#endif

#define PTRACE_GETREGS            12
#define PTRACE_SETREGS            13
#define PTRACE_GETFPREGS          14
#define PTRACE_SETFPREGS          15
#define PTRACE_GETFPXREGS         18
#define PTRACE_SETFPXREGS         19

#define PTRACE_OLDSETOPTIONS      21

/// для 32 битных программ
#define PTRACE_GET_THREAD_AREA    25
#define PTRACE_SET_THREAD_AREA    26

#ifdef __x86_64__
    #define PTRACE_ARCH_PRCTL	  30
#endif

#define PTRACE_SYSEMU		  31
#define PTRACE_SYSEMU_SINGLESTEP  32

#define PTRACE_SINGLEBLOCK	33

/*
#ifdef __i386__
    #ifndef __KERNEL__
    struct pt_regs_struct {
        long ebx;
        long ecx;
        long edx;
        long esi;
        long edi;
        long ebp;
        long eax;
        int  xds;
        int  xes;
        int  xfs;
        int  xgs;
        long orig_eax;
        long eip;
        int  xcs;
        long eflags;
        long esp;
        int  xss;
    };
    #endif
#else
    #ifndef __KERNEL__
    struct pt_regs_struct {
        unsigned long r15;
        unsigned long r14;
        unsigned long r13;
        unsigned long r12;
        unsigned long rbp;
        unsigned long rbx;

        unsigned long r11;
        unsigned long r10;
        unsigned long r9;
        unsigned long r8;
        unsigned long rax;
        unsigned long rcx;
        unsigned long rdx;
        unsigned long rsi;
        unsigned long rdi;
        unsigned long orig_rax;

        unsigned long rip;
        unsigned long cs;
        unsigned long eflags;
        unsigned long rsp;
        unsigned long ss;

    };
    #endif
#endif
*/
#ifdef __i386__
    struct pt_regs_struct {
        unsigned long bx;
        unsigned long cx;
        unsigned long dx;
        unsigned long si;
        unsigned long di;
        unsigned long bp;
        unsigned long ax;
        unsigned long ds;
        unsigned long es;
        unsigned long fs;
        unsigned long gs;
        unsigned long orig_ax;
        unsigned long ip;
        unsigned long cs;
        unsigned long flags;
        unsigned long sp;
        unsigned long ss;
    };
#else
    struct pt_regs_struct {
        unsigned long r15;
        unsigned long r14;
        unsigned long r13;
        unsigned long r12;
        unsigned long bp;
        unsigned long bx;
    /* arguments: non interrupts/non tracing syscalls only save up to here*/
        unsigned long r11;
        unsigned long r10;
        unsigned long r9;
        unsigned long r8;
        unsigned long ax;
        unsigned long cx;
        unsigned long dx;
        unsigned long si;
        unsigned long di;
        unsigned long orig_ax;
    /* end of arguments */
    /* cpu exception frame or undefined */
        unsigned long ip;
        unsigned long cs;
        unsigned long flags;
        unsigned long sp;
        unsigned long ss;
    /* top of stack page */
    };
#endif    

// возвращение значения в регистре AX    
static inline unsigned long regs_return_value(struct pt_regs_struct *regs)
{
	return regs->ax;
}

// проверяет из какого уровня набор регистров "пользовательский"
static inline int user_mode(struct pt_regs_struct *regs)
{
#ifdef CONFIG_X86_32
	return (regs->cs & SEGMENT_RPL_MASK) == USER_RPL;
#else
	return !!(regs->cs & 3);
#endif
}    

static inline int user_mode_vm(struct pt_regs_struct *regs)
{
#ifdef CONFIG_X86_32
	return ((regs->cs & SEGMENT_RPL_MASK) | (regs->flags & X86_VM_MASK)) >= USER_RPL;
#else
	return user_mode(regs);
#endif
}

static inline int v8086_mode(struct pt_regs_struct *regs)
{
#ifdef CONFIG_X86_32
	return (regs->flags & X86_VM_MASK);
#else
	return 0;   // VM86 не поддерживается
#endif
}

#ifdef CONFIG_X86_64
static inline bool user_64bit_mode(struct pt_regs_struct *regs)
{ 
    return regs->cs == __USER_CS; 
}
#endif

#endif /* ARCH_X86_PTRACE_H */