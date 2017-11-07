#ifndef ARCH_X86_PAGE_32_H
#define ARCH_X86_PAGE_32_H

#ifndef __ASSEMBLY__
#define __phys_addr_nodebug(x)	((x) - PAGE_OFFSET)

#define __phys_addr(x)		__phys_addr_nodebug(x)
#define __phys_addr_symbol(x)	__phys_addr(x)
#define __phys_reloc_hide(x)	RELOC_HIDE((x), 0)
#endif

#endif /* ARCH_X86_PAGE_32_H */