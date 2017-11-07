#ifndef KERNEL_ARCH_X86_32_TRAPGATE_H
#define KERNEL_ARCH_X86_32_TRAPGATE_H

typedef enum x86_reg {
    esreg =  1, dsreg =  2,	 Dreg  =  3, 	 Sreg  =  4,  
    Breg  =  5, breg  =  7,  	 dreg  =  8,	 creg  =  9, 
    areg  = 10, ereg  = 11,	 ipreg = 12, 	 csreg = 13, 
    freg  = 14, spreg = 15,	 ssreg = 16, 
} x86_reg_e;

const word_t num_regs = 17;

#if defined(CONFIG_DEBUG)
    const word_t num_dbgregs = 12;
#endif
    
typedef struct x86_exceptionregs {
    union
    {
	struct
	{    
	    u32_t reason;		/*  0 */
	    u32_t es;			/*  1 */
	    u32_t ds;			/*  2 */
	    u32_t edi;			/*  3 */
	    u32_t esi;			/*  4 */
	    u32_t ebp;			/*  5 */
	    u32_t __esp;		        
	    u32_t ebx;			/*  7 */
	    u32_t edx;			/*  8 */
	    u32_t ecx;			/*  9 */
	    u32_t eax;			/* 10 */
	    /* default trapgate frame */	
	    u32_t error;		/* 11 */
	    u32_t eip;			/* 12 */
	    u32_t cs;			/* 13 */
	    u32_t eflags;		/* 14 */
	    u32_t esp;			/* 15 */
	    u32_t ss;			/* 16 */
	};

	word_t regs[num_regs];
        
        #if defined(CONFIG_DEBUG)
            const word_t num_dbgregs = 12;
        #endif
    };
} x86_exceptionregs_t;


#endif /* KERNEL_ARCH_X86_32_TRAPGATE_H */