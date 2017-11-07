// структура создания синхронизации
struct _kernel_args_sync_create {
    KARGSLOT(unsigned       type);
    KARGSLOT(sync_t         *sync);
    KARGSLOT(sync_attr_t    *attr);
} sync_create;

// структура удаления синхронизации
struct _kernel_args_sync_destroy {
    KARGSLOT(sync_t	*sync);
} sync_destroy;

// структура блокировки мьютекса
struct _kernel_args_sync_mutex_lock {
    KARGSLOT(sync_t	*sync);
} sync_mutex_lock;

// структура разблокировки мьютекса
struct _kernel_args_sync_mutex_unlock {
    KARGSLOT(sync_t	*sync);
} sync_mutex_unlock;

// структура оживления мьютекса
struct _kernel_args_sync_mutex_revive {
    KARGSLOT(sync_t	*sync);
} sync_mutex_revive;

// структура синхронизации данных
struct _kernel_args_sync_ctl {
    KARGSLOT(int    cmd);
    KARGSLOT(sync_t *sync);
    KARGSLOT(void   *data);
} sync_ctl;

// структура ожидания условной переменной
struct _kernel_args_sync_condvar_wait {
    KARGSLOT(sync_t     *sync);
    KARGSLOT(sync_t	*mutex);
} sync_condvar_wait;

// структура сигнал условной переменной
struct _kernel_args_sync_condvar_signal {
    KARGSLOT(sync_t	*sync);
    KARGSLOT(int32_t    all);
} sync_condvar_signal;

// структура ожидания семафора
struct _kernel_args_sync_sem_wait {
    KARGSLOT(sync_t	*sync);
    KARGSLOT(int32_t    try);
} sync_sem_wait;

// структура размещение семафора
struct _kernel_args_sync_sem_post {
    KARGSLOT(sync_t	*sync);
} sync_sem_post;