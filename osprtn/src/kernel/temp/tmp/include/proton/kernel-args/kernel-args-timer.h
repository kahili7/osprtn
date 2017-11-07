// структура создает таймер
struct _kernel_args_timer_create {
    KARGSLOT(clockid_t          id);
    KARGSLOT(struct sigevent    *event);
} timer_create;

// структура удаляет таймер
struct _kernel_args_timer_destroy {
    KARGSLOT(int32_t    id);
} timer_destroy;

// структура устанавливает время таймера
struct _kernel_args_timer_settime {
    KARGSLOT(timer_t            id);
    KARGSLOT(int32_t		flags);
    KARGSLOT(struct _itimer     *itime);
    KARGSLOT(struct _itimer	*oitime);
} timer_settime;

// структура информация о таймере
struct _kernel_args_timer_info {
    KARGSLOT(pid_t		pid);
    KARGSLOT(timer_t		id);
    KARGSLOT(int32_t		flags);
    KARGSLOT(struct _timer_info	*info);
} timer_info;

// структура таймера сигнализации
struct _kernel_args_timer_alarm {
    KARGSLOT(clockid_t      id);
    KARGSLOT(struct _itimer *itime);
    KARGSLOT(struct _itimer *otime);
} timer_alarm;

// структура таймера ожидания
struct _kernel_args_timer_timeout {
    KARGSLOT(clockid_t		id);
    KARGSLOT(uint32_t		timeout_flags);
    KARGSLOT(struct sigevent    *event);
    KARGSLOT(uint64_t		*ntime);
    KARGSLOT(uint64_t		*otime);
} timer_timeout;