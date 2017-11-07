#ifndef LIB_TYPES_H
#define LIB_TYPES_H

// беззнаковые
typedef unsigned int __attribute__((__mode__(__DI__)))  u64_t;
typedef unsigned int                                    u32_t;
typedef unsigned short                                  u16_t;
typedef unsigned char                                   u8_t;
typedef u32_t                                           uintptr_t;

// знаковые
typedef signed int __attribute__((__mode__(__DI__)))    s64_t;
typedef signed int                                      s32_t;
typedef signed short                                    s16_t;
typedef signed char                                     s8_t;
typedef s32_t                                           iintptr_t;

// беззнаковое машинное слово
typedef u32_t                                           word_t;

#if defined(__i386)
    #define MAX_INTN    ((INTN)0x7FFFFFFF)
    #define MAX_UINTN   ((UINTN)0xFFFFFFFF)
#elif defined (__amd64)
    #define MAX_INTN    ((INTN)0x7FFFFFFFFFFFFFFF)
    #define MAX_UINTN   ((UINTN)0xFFFFFFFFFFFFFFFF)
#else
    //#error No known architecture was defined.
#endif

//определение типов
//
typedef unsigned char       BYTE, *PBYTE;
typedef unsigned short      WORD, *PWORD;
typedef unsigned int        DWORD, *PDWORD;

typedef char                CHAR, *PCHAR;
typedef signed char         SCHAR, *PSCHAR;
typedef unsigned char       UCHAR, *PUCHAR;
typedef const unsigned char CUCHAR, *PCUCHAR;

typedef short               SHORT, *PSHORT;
typedef unsigned short      USHORT, *PUSHORT;

typedef int                 INT, *PINT;
typedef unsigned int        UINT, *PUINT;

typedef int                 LONG, *PLONG;
typedef unsigned int        ULONG, *PULONG;
typedef long long           LONGLONG, *PLONGLONG;
typedef unsigned long long  ULONGLONG, *PULONGLONG;

#if __SIZEOF_LONG__ != __SIZEOF_POINTER__
    #error INTN and UINTN definitions are wrong.
#endif

typedef long                INTN, *PINTN;
typedef unsigned long       UINTN, *PUINTN;

typedef unsigned long long  P_ADDR, *PP_ADDR;

typedef void                *PVOID;
typedef const void          *PCVOID;
typedef char                *PSTR;
typedef const char          *PCSTR;

typedef enum _BOOL { FALSE = 0, TRUE = 1 } BOOL, *PBOOL;

typedef struct _LIST_ENTRY LIST_ENTRY, *PLIST_ENTRY;
struct _LIST_ENTRY {
    PLIST_ENTRY Next;
    PLIST_ENTRY Previous;
};

typedef struct _UUID {
    ULONG Data[4];
} UUID, *PUUID;

#if !defined(NULL)
    #define NULL ((PVOID)0)
#endif

// структура для синхронизации потоков
typedef struct _SYNC {
    volatile INT Count;
    volatile UINT Owner;
} SYNC, *PSYNC;

// атрибуты синхронизации
typedef struct _SYNC_ATTR {
    INT Protocol;
    INT Flags;
    INT PriorityCeiling;    // для увеличения приоритета
    INT ClockId;            // для условной переменной
} SYNC_ATTR, *PSYNC_ATTR;

typedef struct _ITIMER {
    ULONGLONG   NSecond;            // наносекунды
    ULONGLONG   Interval_NSecond;   // интервал в наносекундах
} ITIMER, *PITIMER;
#endif /* LIB_TYPES_H */