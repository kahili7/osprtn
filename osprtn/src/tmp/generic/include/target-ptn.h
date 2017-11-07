#ifndef GENERIC_TARGET_PTN_H
#define GENERIC_TARGET_PTN_H

#include <types.h>

// структуры синхронизации
#undef _SYNC_T
#define _SYNC_T struct _sync {\
            int         __count;\
            unsigned    __owner;\
        }

#undef _SYNC_ATTR_T
#define _SYNC_ATTR_T struct _sync_attr {\
            int     __protocol;\
            int     __flags;\
            int     __prioceiling;\
            int     __clockid;\
            int     __reserved;\
        }

// типы времени
/*
 * секунды
 * наносекунды
 */
#undef _TIMESPEC_DEF
#define _TIMESPEC_DEF(__name, __pref)\
        struct __name {\
            time_t  __pref##_sec;\
            long    __pref##_nsec;\
        }

// тип timespec
#undef	_TIMESPEC
#define _TIMESPEC  _TIMESPEC_DEF(timespec, tv)

// тип __timespec внутренний
#undef	_TIMESPEC_INTERNAL
#define	_TIMESPEC_INTERNAL _TIMESPEC_DEF(_timespec, __tv)

// параметры планировщика
#undef _SCHED_PARAM_DEF
#define _SCHED_PARAM_DEF(__name, __ts, __pref)\
	struct __name {\
            _Int32t __pref##_priority;\
            _Int32t __pref##_curpriority;\
            union {	\
                _Int32t __reserved[8];\
                struct {	\
                    _Int32t __ss_low_priority;\
                    _Int32t __ss_max_repl;\
                    struct __ts	__ss_repl_period;\
                    struct __ts	__ss_init_budget;\
                } __ss;\
            } __ss_un;\
	}

#define _sched_ss_low_priority     __ss_un.__ss.__ss_low_priority
#define _sched_ss_max_repl         __ss_un.__ss.__ss_max_repl
#define _sched_ss_repl_period      __ss_un.__ss.__ss_repl_period
#define _sched_ss_init_budget      __ss_un.__ss.__ss_init_budget

// тип параметров планировщика для внутреннего использования
#undef	_SCHED_PARAM_INTERNAL
#define	_SCHED_PARAM_INTERNAL	_SCHED_PARAM_DEF(_sched_param, __timespec, __sched)

// тип параметров планировщика
#undef	_SCHED_PARAM_T
#define	_SCHED_PARAM_T          _SCHED_PARAM_DEF(sched_param, timespec, sched)


// атрибуты потока
/*
 * флаги
 * размер стека
 * адрес стека
 * функция выхода
 * политики
 * размер щита
 * выделить объем памяти для потока MAP_LAZY стек
 */
#undef _PTHREAD_ATTR_T
#define _PTHREAD_ATTR_T struct _pthread_attr {\
            int                 __flags;\
            size_t              __stacksize;\
            void                *__stackaddr;\
            void                (*__exitfunc)(void *__status);\
            int                 __policy;\
            struct _sched_param __param;\
            size_t              __guardsize;\
            size_t              __prealloc;\
        }

// биты сигналов
#undef _SIGSET_T
#define _SIGSET_T struct {\
            long __bits[2];\
	}

// вектор IN/OUT
#undef _IOVEC_T
#define _IOVEC_T struct _iovec {\
            void    *iov_base;\
            size_t  iov_len;\
        }

#define _CLOCKADJUST {\
            unsigned long   tick_count;\
            long            tick_nsec_inc;\
	}
#endif /* GENERIC_TARGET_PTN_H */