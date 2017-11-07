#ifndef GENERIC_TYPES_H
#define GENERIC_TYPES_H

#include <platform.h>
#include _SOS_CPU_HDR_DIR_(types.h)
#include _SOS_HDR_(posix_types.h)

#define DECLARE_BITMAP(name,bits)   unsigned long name[BITS_TO_LONGS(bits)]

typedef _Uint32t __kernel_dev_t;

typedef __kernel_fd_set     fd_set;     // тип файлового дескриптор
typedef __kernel_dev_t      dev_t;      // тип устройства

#ifndef _TIME_T
    #define _TIME_T __kernel_time_t
    typedef _TIME_T time_t; // тип времени
    #undef _TIME_T
#endif
    
#ifndef _MODE_T
    #define _MODE_T __kernel_mode_t
    typedef _MODE_T mode_t; // тип модификатора
    #undef _MODE_T
#endif
    
#ifndef _SIZE_T
    #define _SIZE_T __kernel_size_t
    typedef _SIZE_T size_t; // тип счетчик без знака
    #undef _SIZE_T
#endif

#ifndef _SSIZE_T
    #define _SSIZE_T __kernel_ssize_t
    typedef _SSIZE_T ssize_t; // тип счетчик со знаком
    #undef _SSIZE_T
#endif

#ifndef _PTRDIFF_T
    #define _PTRDIFF_T __kernel_ptrdiff_t
    typedef _PTRDIFF_T ptrdiff_t;
    #undef _PTRDIFF_T
#endif 

#ifndef _OFF_T
    #define _OFF_T __kernel_off_t
    typedef _OFF_T off_t;
    #undef _OFF_T
#endif 

#ifndef _OFF64_T
    #define _OFF64_T __kernel_loff_t
    typedef _OFF64_T off64_t;
    #undef _OFF64_T
#endif

#ifndef _PID_T
    #define _PID_T __kernel_pid_t
    typedef _PID_T pid_t;
    #undef _PID_T
#endif

#ifndef _UID_T
    #define _UID_T __kernel_uid_t
    typedef _UID_T uid_t;
    #undef _UID_T
#endif

#ifndef _GID_T
    #define _GID_T __kernel_gid_t
    typedef _GID_T gid_t;
    #undef _GID_T
#endif

#ifndef _CLOCKID_T
    #define _CLOCKID_T __kernel_clockid_t
    typedef _CLOCKID_T clockid_t;
    #undef _CLOCKID_T
#endif

#ifndef _SYNC_T
    typedef _SYNC_T sync_t;
    #undef _SYNC_T
#endif

#ifndef _SYNC_ATTR_T
    typedef _SYNC_ATTR_T sync_attr_t;
    #undef _SYNC_ATTR_T 
#endif

// тип для атомарной операции 32 | 64 бит
typedef struct {
    int counter;
} atomic_t;

#ifdef CONFIG_64BIT
    typedef struct {
        long counter;
    } atomic64_t;
#endif

#if defined(_IOVEC_T)
    typedef _IOVEC_T iov_t;
    #undef _IOVEC_T 
#endif

#if defined(_CLOCKADJUST)
    struct _clockadjust _CLOCKADJUST;
    #undef _CLOCKADJUST 
#endif

// структуры для списков
struct list_head {
    struct list_head *next, *prev;
};

struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};
#endif /* GENERIC_TYPES_H */