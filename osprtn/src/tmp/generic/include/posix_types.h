#ifndef GENERIC_POSIX_TYPES_H
#define GENERIC_POSIX_TYPES_H

// установка 2048 файловых дескрипторов
#undef FD_SETSIZE
#define FD_SETSIZE    2048

typedef struct {
    unsigned long fds_bits[FD_SETSIZE / (8 * sizeof(long))];
} __kernel_fd_set;

#ifndef __kernel_long_t
    typedef long            __kernel_long_t;
    typedef unsigned long   __kernel_ulong_t;
#endif

#ifndef __kernel_ino_t
    typedef __kernel_ulong_t  __kernel_ino_t;     // тип inode файла
#endif
  
#ifndef __kernel_mode_t
    typedef unsigned int    __kernel_mode_t;    // тип модификаторы файла
#endif

#ifndef __kernel_pid_t
    typedef int             __kernel_pid_t;     // тип pid процесса
#endif

#ifndef __kernel_ipc_pid_t
    typedef int             __kernel_ipc_pid_t; // тип ipc_pid процесса
#endif
    
#ifndef __kernel_uid_t
    typedef unsigned int    __kernel_uid_t;     // тип пользователя
    typedef unsigned int    __kernel_gid_t;     // тип группы
#endif

#ifndef __kernel_uid32_t
    typedef unsigned int    __kernel_uid32_t;   // тип пользователя 32 бит
    typedef unsigned int    __kernel_gid32_t;   // тип группы 32 бит
#endif

#ifndef __kernel_daddr_t
    typedef int             __kernel_daddr_t;   // тип используется для количество устройств
#endif

typedef __kernel_ulong_t    __kernel_off_t;     // тип смещения
typedef long long           __kernel_loff_t;    // тип смещение лимита
typedef __kernel_ulong_t    __kernel_time_t;    // тип времени
typedef __kernel_ulong_t    __kernel_clock_t;   // тип часов
typedef int                 __kernel_timer_t;   // тип таймера
typedef int                 __kernel_clockid_t; // тип id часов
typedef char*               __kernel_caddr_t;   // указатель на адрес
typedef unsigned short      __kernel_uid16_t;   // тип пользователя 16 бит
typedef unsigned short      __kernel_gid16_t;   // тип группы 16 бит

#ifndef __kernel_size_t
    #if BITS_PER_LONG != 64
    typedef unsigned int        __kernel_size_t;
    typedef int                 __kernel_ssize_t;
    typedef int                 __kernel_ptrdiff_t;
    #else
    typedef __kernel_ulong_t    __kernel_size_t;
    typedef __kernel_long_t	__kernel_ssize_t;
    typedef __kernel_long_t	__kernel_ptrdiff_t;
    #endif
#endif

#endif /* GENERIC_POSIX_TYPES_H */