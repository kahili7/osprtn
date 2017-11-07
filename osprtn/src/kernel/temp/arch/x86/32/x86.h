#ifndef KERNEL_ARCH_X86_32_X86_H
#define KERNEL_ARCH_X86_32_X86_H

// MMU
#define X86_X32_PDIR_BITS	22                              // 22 bits address memory
#define X86_X32_PDIR_SIZE       (__UL(1) << X86_X32_PDIR_BITS)  // 1 PDE = size memory 4Mb
#define X86_X32_PDIR_MASK       (~(X86_X32_PDIR_SIZE - 1))
#define X86_X32_PDIR_IDX(x)	((x & X86_X32_PDIR_MASK) >> X86_X32_PDIR_BITS)

#define X86_X32_PTAB_BITS       12                              // 12 bits address memory
#define X86_X32_PTAB_SIZE       (__UL(1) << X86_X32_PTAB_BITS)  // count 1024 PTE  
#define X86_X32_PTAB_MASK       ((~(X86_X32_PTAB_SIZE - 1)) ^ (~(X86_X32_PTAB_SIZE - 1)))
#define X86_X32_PTAB_IDX(x)     ((x & X86_X32_PTAB_MASK) >> X86_X32_PTAB_BITS)

#define X86_X32_PTAB_FLAGS_MASK	(0x0007)

#define X86_SUPERPAGE_BITS	22
#define X86_SUPERPAGE_SIZE	(__UL(1) << X86_SUPERPAGE_BITS)
#define X86_SUPERPAGE_MASK	(~(X86_SUPERPAGE_SIZE - 1))
#define X86_SUPERPAGE_FLAGS_MASK (0x11ff)

#define X86_PAGE_FLAGS_MASK	 (0x01ff)
#endif /* KERNEL_ARCH_X86_32_X86_H */