#include <platform.h>
#include <types.h>
#include <stdint.h>
#include <sys/thread-storage.h>
#
#ifndef CONFIG_X86_64
    #define current_sp() ({ unsigned sp; asm("movl %%esp, %0" : "=g" (sp) : ); sp; })
    #define current_bp() ({ unsigned long bp; asm("movl %%ebp, %0" : "=r" (bp) : ); bp; })
#endif

// смещение стек адреса
size_t __stackavail()
{
    return current_sp() - (uintptr_t)current_tls()->__stackaddr;
}