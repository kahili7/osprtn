#ifndef KERNEL_SYS_SYSPAGE_H
#define KERNEL_SYS_SYSPAGE_H

typedef struct _SYSPAGE_INFO {
    USHORT  Offset;
    USHORT  Size;
} SYSPAGE_INFO, *PSYSPAGE_INFO;

// структура содержащая информацию о временной разветки системы
typedef struct _TIMEBASE {
    ULONGLONG               CyclesPerSec;   // циклов в секунду
    ULONGLONG volatile      NSecond_TOD;    // наносекунд сначала 1970
    ULONGLONG volatile      NSecondStart;   // наносекунд с момента загрузки системы
    ULONG                   NSecondInc;     // количество секунд прошедших каждый раз, когда происходит прерывание
    ULONG                   BootTime;       // количество секунд прошедших с 1970, когда была загружена система
    ULONG                   TimerRate;      // норма времени
    ULONG                   TimerScale;     // масштаб времени
    ULONG                   TimerLoad;      // размер делителя таймера
    LONG                    Intr;           // содержит вектор прерывания, используемый чипом часов для прерывания процессора
    ULONG                   Flags;          // указывает, когда таймер относится к CPUO
    UINT                    RRIntervalMul;
} TIMEBASE, *PTIMEBASE;

// структура описывающая системную таблицу
typedef struct _SYSPAGE {
    USHORT          Size;       // размер _SYSPAGE
    USHORT          TotalSize;  // полный размер _SYSPAGE со всеми структурами
    USHORT          Type;       // тип архитектуры процессора
    USHORT          CountCpu;   // количество процессоров
    SYSPAGE_INFO    TIMEBASE;
} SYSPAGE, *PSYSPAGE;

#define _SYSPAGE_ENTRY_SIZE(base, field)    ((base)->field.Size)
#define SYSPAGE_ENTRY_SIZE(field)           _SYSPAGE_ENTRY_SIZE(SysPagePtr, field)

#define _SYSPAGE_ENTRY(base, field)   ((P##field)(PVOID)((PCHAR)(base) + (base)->field.Offset))
#define SYSPAGE_ENTRY(field)          _SYSPAGE_ENTRY(SysPagePtr, field)


#endif /* KERNEL_SYS_SYSPAGE_H */