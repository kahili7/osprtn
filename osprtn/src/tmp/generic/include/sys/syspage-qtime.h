#define QTIME_FLAG_TIMER_ON_CPU0	0x00000001
#define QTIME_FLAG_CHECK_STABLE		0x00000002

struct qtime_entry {
    _Uint64t                cycles_per_sec;	/* for ClockCycles */
    _Uint64t volatile       nsec_tod_adjust;    // при добавлении в нсек, данное поле дает число наносекунд с начала эпохи (1970)
    _Uint64t volatile       nsec;               // это 64-битовое поле, содержащее количество наносекунд, так как система была загружена
    unsigned long           nsec_inc;           // число наносекунд считаться прошедшее каждый раз, когда тактовый вход срабатывает прерывание
    unsigned long           boot_time;          /* UTC seconds when machine booted */

    struct _clockadjust     adjust;             // установить на ноль при запуске — содержит каких тока временная развертка регулировка параметров во время выполнения
    unsigned long           timer_rate;         // times 10^timer_scale
    long                    timer_scale;        
    unsigned long           timer_load;         // таймер микросхема делитель значение
    long                    intr;               // содержит вектор прерывания, что микросхема часов реального времени используется для прерывания процессора
    unsigned long           epoch;              // с 1970
    unsigned long           flags;              // флаги
    unsigned int            rr_interval_mul;    // 
    unsigned long           spare0;
    _Uint64t volatile       nsec_stable;
    unsigned long           spare[4];
};