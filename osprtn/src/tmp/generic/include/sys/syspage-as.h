#define AS_NULL_OFF             ((_Uint16t)-1)

#define AS_ATTR_READABLE	0x0001
#define AS_ATTR_WRITABLE	0x0002
#define AS_ATTR_CACHABLE	0x0004
#define AS_ATTR_VISIBLE		0x0008
#define AS_ATTR_KIDS		0x0010
#define AS_ATTR_CONTINUED	0x0020

#define AS_PRIORITY_DEFAULT	100

struct asinfo_entry {
    _Uint64t    start;      // дает первый физический адрес из диапазона, описанного
    _Uint64t    end;        // дает последний физический адрес из диапазона, описанного. Обратите внимание, что это является фактической последнего байта, а не один за конец
    _Uint16t    owner;      // смещение от начала секции давая хозяину эта запись (ее "родителя" в дереве)
    _Uint16t    name;       // смещение от начала строки в разделе системы страница давая имя строки этой записи
    _Uint16t    attr;       // содержит несколько битов, влияющих на диапазон адресов
    _Uint16t    priority;   // показывает скорость памяти в диапазоне адресов
    int         (*alloc_checker)(struct syspage_entry *__sp, _Uint64t *__base, _Uint64t *__len, size_t __size, size_t __align);
    _Uint32t    spare;
};
