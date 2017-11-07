#ifndef KERNEL_BIND_X86_CONFIG_H
#define KERNEL_BIND_X86_CONFIG_H

#define DIR_BIND_ARCH(src)       <bind/__ARCH__/src>
#define DIR_BIND_CPU(src)        <bind/__ARCH__/__CPU__/src>

#include DIR_BIND_CPU(config.h)

#endif /* KERNEL_BIND_X86_CONFIG_H */