#ifndef ARCH_X86_PAGE_H
#define ARCH_X86_PAGE_H

#ifdef __KERNEL__
    #include _SOS_CPU_HDR_DIR_(page-defs.h)

    #ifdef CONFIG_X86_64
        #include <asm/page_64.h>
    #else
        #include _SOS_CPU_HDR_DIR_(page-32-defs.h)
        #include _SOS_CPU_HDR_DIR_(page-32.h)
    #endif
#endif

#endif /* ARCH_X86_PAGE_H */