#ifndef GENERIC_FCNTL_H
#define GENERIC_FCNTL_H

#include <platform.h>

/*
 * управление файлами
 */

#define O_RDONLY    000000  // только чтение
#define O_WRONLY    000001  // только запись
#define O_RDWR      000002  // чтение-запись
#define O_ACCMODE   000003  // маска доступа

#define O_CREAT     000400  // создание файла при открытии


#define O_CLOEXEC   020000  // позволяет избежать дополнительной команды fcntl
#endif /* GENERIC_FCNTL_H */