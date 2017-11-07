#ifndef GENERIC_SYS_THREAD_STORAGE_H
#define GENERIC_SYS_THREAD_STORAGE_H

#include <platform.h>
#include _SOS_CPU_HDR_DIR_(thread-storage.h)

/*
 * локальные данные потока
 * эти данные расположены вверху стека каждого потока
 */

struct _thread_local_storage {
    void        (*__exitfunc)(void *);  // поток возвращает функцию
    void        *__arg;                 // единственный аргумент переданный потоку
    int		*__errptr;              // указатель на поток уникальные для errno значение
                                        // для основного потока указывает на глобальную переменную errno
                                        // для остальных потоков указывает на член errval в этой структуре
    int		__errval;               // уникальное значение errno
    unsigned    __flags;                // флаги потока
    int		__pid;                  // идентификатор процесса, содержащего поток
    int		__tid;                  // идентификатор потока
    unsigned	__owner;                // владелец
    void        *__stackaddr;           // указатель на адрес стека
};

extern struct _thread_local_storage * __tls(void);
#endif /* GENERIC_SYS_THREAD_STORAGE_H */