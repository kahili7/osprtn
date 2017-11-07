#ifndef KERNEL_X86_H
#define KERNEL_X86_H
#include "kernel/x86_defs.h"

// структура таблицы дескриптора
typedef struct _DESCRIPTOR_ENTRY {
    USHORT  LimitLow;
    USHORT  BaseLow;
    UCHAR   BaseMiddle;
    UCHAR   Access;
    UCHAR   Granularity;
    UCHAR   BaseHigh;
} DESCRIPTOR_ENTRY, *PDESCRIPTOR_ENTRY; 

// структура шлюза ловушки
typedef struct _PROCESSOR_GATE {
    USHORT  LowOffset;
    USHORT  Selector;
    UCHAR   Count;
    UCHAR   Access;
    USHORT  HighOffset;
} PROCESSOR_GATE, *PPROCESSOR_GATE;

// структуры определяющая таблицу страниц или директорию
typedef union _PXE {
    ULONG      Pxe32;
    ULONGLONG  Pxe64;
} PXE, *PPXE;

// структуры определяющая сегмент состояния задачи
typedef struct _TSS {
    ULONG   BackLink;
    
    ULONG   Esp0;
    USHORT  Ss0;
    USHORT  Pad0;
    
    ULONG   Esp1;
    USHORT  Ss1;
    USHORT  Pad1;
    
    ULONG   Esp2;
    USHORT  Ss2;
    USHORT  Pad2;
    
    ULONG   Cr3;
    ULONG   Eip;
    ULONG   Eflags;
    ULONG   Eax;
    ULONG   Ecx;
    ULONG   Edx;
    ULONG   Ebx;
    PULONG  Esp;
    ULONG   Ebp;
    ULONG   Esi;
    ULONG   Edi;
    
    USHORT  Es;
    USHORT  Pad3;
    
    USHORT  Cs;
    USHORT  Pad4;
    
    USHORT  Ss;
    USHORT  Pad5;
    
    USHORT  Ds;
    USHORT  Pad6;
    
    USHORT  Fs;
    USHORT  Pad7;
    
    USHORT  Gs;
    USHORT  Pad8;
    
    USHORT  LdtSelector;
    USHORT  Pad9;
    
    USHORT  DebugTrap;
    USHORT  IoMapBase;
    ULONG   IoMapData[1];
} TSS, *PTSS;

// структуры определяющая расширенное состояние архитектуры.
struct _FPU_CONTEXT {
    USHORT Fcw;
    USHORT Fsw;
    USHORT Ftw;
    USHORT Fop;
    ULONG FpuIp;
    USHORT Cs;
    USHORT Reserved1;
    ULONG FpuDp;
    USHORT Ds;
    USHORT Reserved2;
    ULONG Mxcsr;
    ULONG MxcsrMask;
    UCHAR St0Mm0[16];
    UCHAR St1Mm1[16];
    UCHAR St2Mm2[16];
    UCHAR St3Mm3[16];
    UCHAR St4Mm4[16];
    UCHAR St5Mm5[16];
    UCHAR St6Mm6[16];
    UCHAR St7Mm7[16];
    UCHAR Xmm0[16];
    UCHAR Xmm1[16];
    UCHAR Xmm2[16];
    UCHAR Xmm3[16];
    UCHAR Xmm4[16];
    UCHAR Xmm5[16];
    UCHAR Xmm6[16];
    UCHAR Xmm7[16];
    UCHAR Xmm8[16];
    UCHAR Xmm9[16];
    UCHAR Xmm10[16];
    UCHAR Xmm11[16];
    UCHAR Xmm12[16];
    UCHAR Xmm13[16];
    UCHAR Xmm14[16];
    UCHAR Xmm15[16];
    UCHAR Padding[96];
};
#endif /* KERNEL_X86_H */