// структура о получении параметров планировщика
struct _kernel_args_sched_get {
    KARGSLOT(pid_t              pid);
    KARGSLOT(int32_t            tid);
    KARGSLOT(struct sched_param *param);
} sched_get;

// структура об установке параметров планировщика
struct _kernel_args_sched_set {
    KARGSLOT(pid_t		pid);
    KARGSLOT(int32_t		tid);
    KARGSLOT(int32_t		policy);
    KARGSLOT(struct sched_param *param);
} sched_set;

// структура с информацией планировщика
struct _kernel_args_sched_info {
    KARGSLOT(pid_t		pid);
    KARGSLOT(int		policy);
    KARGSLOT(struct _sched_info *info);
} sched_info;

// структура планировщика с данными
struct _kernel_args_sched_ctl {
    KARGSLOT(int32_t    cmd);
    KARGSLOT(void	*data);
    KARGSLOT(size_t	length);
} sched_ctl;