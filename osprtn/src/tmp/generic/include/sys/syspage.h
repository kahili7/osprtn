#ifndef GENERIC_SYS_SYSPAGE_H
#define GENERIC_SYS_SYSPAGE_H

#include _SOS_CPU_HDR_DIR_(syspage.h)

#undef _SPPTR
#undef _SPFPTR

#define _SPPTR(_t)              _t *
#define _SPFPTR(_r, _n, _p)     _r (*_n) _p

// предопределение структур
struct _thread_local_storage;
struct _process_local_storage;
struct syspage_entry;

#include <sys/syspage-sprivate.h>
#include <sys/syspage-as.h>
#include <sys/syspage-mem.h>
#include <sys/syspage-hw.h>
#include <sys/syspage-cpu.h>
#include <sys/syspage-cache.h>
#include <sys/syspage-qtime.h>
#include <sys/syspage-call.h>

// глобальный указатель на системную страницу
extern struct syspage_entry *_syspage_ptr;

typedef struct {
    _Uint16t entry_off;     // смещение записи
    _Uint16t entry_size;    // размер записи
} syspage_entry_info;

struct syspage_entry {
    _Uint16t        size;           // размер syspage_entry
    _Uint16t        total_size;     // размер системной страницы с указанием ссылочной подструктуры; эффективный размер всей системы-страница базы данных
    _Uint16t        type;           // используется для указания семейств процессоров
    _Uint16t        num_cpu;        // количество CPU
    
    syspage_entry_info system_private;      // в system_private района содержит информацию о том, что операционная система должна знать, когда она загружается
    syspage_entry_info asinfo;              // в asinfo секция состоит из массива на следующую структуру. Каждая запись описывает атрибуты одного раздела адресного пространства на машину
    syspage_entry_info meminfo;             // информация о блоках памяти
    syspage_entry_info hwinfo;              // в hwinfo область содержится информация об аппаратной платформы    
    syspage_entry_info cpuinfo;             // в cpuinfo содержит информацию о каждой микросхемы процессора в системе
    syspage_entry_info cacheattr;           // в cacheattr области содержится информация о конфигурации на кристалле и внешней кэш системы
    syspage_entry_info qtime;               // в qtime области содержится информация о временной разверткой в системе, а также других связанных со временем информация
    syspage_entry_info callout;             // выноски-это область, где различные выноски не отпускают в
    syspage_entry_info callin;              // для внутреннего использования
    syspage_entry_info typed_strings;       // в typed_strings зона состоит из нескольких записей, каждая из которых является числом и строкой
    syspage_entry_info strings;             // пул нетипизированных строк
    syspage_entry_info intrinfo;            // в intrinfo зона будет использоваться для хранения информации о системе прерывания
    syspage_entry_info smp;                 // для SMP систем
    syspage_entry_info pminfo;              // В pminfo зона-это зона общения между энергосбережением и диспетчером автозагрузки/мощность выноски
    syspage_entry_info mdriver;
    
};


#endif /* GENERIC_SYS_SYSPAGE_H */