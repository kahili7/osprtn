#ifndef ARCH_X86_THREAD_STORAGE_H
#define ARCH_X86_THREAD_STORAGE_H

static __inline__ struct _thread_local_storage * __attribute__((__unused__,__const__)) current_tls(void)
{
    struct _thread_local_storage *__p;
    
    switch(sizeof(&__p))
    {
        case 4:
            asm volatile("movl %%fs:0,%0" : "=r" (__p) :);
            break;
            
        default:
            asm volatile("movq %%gs:0,%0" : "=r" (__p) :);
    }
        
    return __p;
}
#endif /* ARCH_X86_THREAD_STORAGE_H */