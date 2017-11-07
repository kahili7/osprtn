#ifndef KERNEL_ARCH_X86_32_CPU_H
#define KERNEL_ARCH_X86_32_CPU_H

INLINE void x86_iret_self()
{
    __asm__ __volatile__("pushf	\n\t"
                         "push %[kcs]\n\t"
                         "pushl $1f\n\t"
                         "iret\n\t"
                         "1:\n\t" : /* No output */ : [kcs] "r" ((word_t) X86_KCS));
}

INLINE bool x86_x32_has_cpuid()
{
    /* Iff bit 21 in EFLAGS can be set the CPU supports the CPUID
     * instruction */
    word_t eflags;
    
    __asm__ (
        // Save EFLAGS to the stack
	"pushfl\n"
        // Set bit 21 in EFLAGS image on stack
	"orl %1, (%%esp)\n"
        // Restore EFLAGS from stack.
	"popfl\n"
        // If supported, this has set bit 21
        // Save EFLAGS on stack to see if bit 21 was set or not
	"pushfl\n"
        // Move EFLAGS image to register for inspection
	"pop %0\n" : "=a" (eflags) : "i" (X86_FLAGS_ID));
    
    return (eflags & X86_FLAGS_ID);
}

INLINE u32_t x86_x32_get_cpu_features()
{
    if (x86_x32_has_cpuid ())
    {
	u32_t features, dummy;
        
	x86_cpuid(1, &dummy, &dummy, &dummy, &features);
        
	return features;
    }
    else
    {
	/* If there is no CPUID instruction we just fabricate the
         * appropriate feature word.  Currently we only support
         * i486DX+ and therefore assume the FPU to be present */
	return X86_X32_FEAT_FPU;
    }
}
#endif /* KERNEL_ARCH_X86_32_CPU_H */