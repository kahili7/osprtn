#ifndef ARCH_X86_SYNC_MUTEX_H
#define ARCH_X86_SYNC_MUTEX_H

#ifdef CONFIG_X86_32
    #include _SOS_CPU_HDR_DIR_(sync/mutex-32.h)
#else
    #include _SOS_CPU_HDR_DIR_(sync/mutex-64.h)
#endif

#endif /* ARCH_X86_SYNC_MUTEX_H */