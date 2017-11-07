#ifndef KERNEL_KTYPES_H
#define KERNEL_KTYPES_H

typedef sigset_t                        SIGBITS;        // тип наборов сигналов
typedef struct _sighandler_entry	SIGHANDLER;
typedef struct _sigstack_entry		SIGSTACK;
typedef struct _sigtable_entry		SIGTABLE;

typedef struct _iovec                   IOV;

typedef struct _process_entry           PROCESS;
#endif /* KERNEL_KTYPES_H */