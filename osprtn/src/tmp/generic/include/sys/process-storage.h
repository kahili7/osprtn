#ifndef GENERIC_SYS_PROCESS_STORAGE_H
#define GENERIC_SYS_PROCESS_STORAGE_H

/*
 * локальные данные процесса
 */
struct _process_local_storage {
    void *(*__getgot)(void *__pltaddr);
    void (*__mathemulator)(unsigned __sigcode, void **__pdata, void *__regs);
    void *__dll_list;
    void *__reserved[6];
    void (*__threadwatch)(int __tid);
};
#endif /* GENERIC_SYS_PROCESS_STORAGE_H */