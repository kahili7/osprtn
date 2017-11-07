#define SYSTEM_PRIVATE_FLAG_ABNORMAL_REBOOT	0x00000001
#define	SYSTEM_PRIVATE_FLAG_EALREADY_NEW	0x00000002

struct system_private_entry {
	_SPPTR(struct cpupage_entry)	user_cpupageptr;
	_SPPTR(struct syspage_entry)	user_syspageptr;
	_SPPTR(struct cpupage_entry)	kern_cpupageptr;
	_SPPTR(struct syspage_entry)	kern_syspageptr;
	_SPPTR(struct kdebug_info)	kdebug_info;	
	_SPPTR(struct kdebug_callback)	kdebug_call;
	
	struct {
		_Paddr32t						base;
		_Uint32t						entry;
	}								boot_pgm[4];
	unsigned long					boot_idx;
	unsigned long					cpupage_spacing;
	unsigned long					private_flags;
	_Uint32t						pagesize;
	
	_Uint32t						ramsize; 
	_SPPTR(struct tracebuf)			tracebuf;
	_Paddr32t						kdump_info;
	_Uint32t						spare[3];
	union kernel_entry {
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_X86)
            struct x86_kernel_entry x86;
#endif
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_PPC)
		struct ppc_kernel_entry			ppc;
#endif
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_MIPS)
		struct mips_kernel_entry		mips;
#endif
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_ARM)
		struct arm_kernel_entry			arm;
#endif
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_SH)
		struct sh_kernel_entry			sh;
#endif
	}								kercall;
};

