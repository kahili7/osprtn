#ifndef ARCH_X86_STRING_H
#define ARCH_X86_STRING_H

#ifndef CONFIG_X86_32
    #include _SOS_CPU_HDR_DIR_(string-32.h)
#else
    #include _SOS_CPU_HDR_DIR_(string-64.h)
#endif

#endif /* ARCH_X86_STRING_H */