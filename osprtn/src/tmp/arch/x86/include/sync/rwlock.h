#ifndef ARCH_X86_RWLOCK_H
#define ARCH_X86_RWLOCK_H

/*
 * блокировка на чтение/запись 
 */

#if CONFIG_NR_CPUS <= 2048
    #ifndef __ASSEMBLY__
        typedef union {
            _Int32t lock;
            _Int32t write;
        } arch_rwlock_t;
    #endif

    #define RW_LOCK_BIAS            0x00100000
    #define READ_LOCK_SIZE(insn)    __ASM_FORM(insn##l)
    #define READ_LOCK_ATOMIC(n)     atomic_##n
    #define WRITE_LOCK_ADD(n)       __ASM_FORM_COMMA(addl n)
    #define WRITE_LOCK_SUB(n)       __ASM_FORM_COMMA(subl n)
    #define WRITE_LOCK_CMP          RW_LOCK_BIAS
#else
    #ifndef __ASSEMBLY__
        typedef union {
            _Int64t lock;
            struct {
                _Uint32t read;
                _Int32t write;
            };
        } arch_rwlock_t;
    #endif

    #define RW_LOCK_BIAS            (_AC(1,L) << 32)
    #define READ_LOCK_SIZE(insn)    __ASM_FORM(insn##q)
    #define READ_LOCK_ATOMIC(n)     atomic64_##n
    #define WRITE_LOCK_ADD(n)       __ASM_FORM(incl)
    #define WRITE_LOCK_SUB(n)       __ASM_FORM(decl)
    #define WRITE_LOCK_CMP		1
#endif

#endif /* ARCH_X86_RWLOCK_H */