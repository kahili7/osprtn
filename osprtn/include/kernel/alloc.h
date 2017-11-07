#ifndef KERNEL_ALLOC_H
#define KERNEL_ALLOC_H

#include "kernel/external.h"

#define PTRADD(ptr, inc)    ((PVOID)((PCHAR)(ptr) + (inc)))         // разименовываем указатель прибавляем значение и конвертируем в общий указатель
#define PTRDIFF(ptr0, ptr1) (((USHORT)(ptr0)) - ((USHORT)(ptr1)))
#define ALIGN(x)            ((USHORT)(x)) + ()

struct _FREE_ENTRY {
    struct _FREE_ENTRY  *Next;
    USHORT              Size;
} FREE_ENTRY, *PFREE_ENTRY;

// чтобы уменьшить задержки в ядре
PFREE_ENTRY     Kernel_Free_List;   // свобобный список для ядра
PFREE_ENTRY     Kernel_Crit_List;   // критический список для ядра
PFREE_ENTRY     Proc_Free_List;     // свобобный список для процесса


#endif /* KERNEL_ALLOC_H */