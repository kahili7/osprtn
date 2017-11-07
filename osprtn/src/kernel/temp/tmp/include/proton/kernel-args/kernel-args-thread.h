// структура создания потока 
struct _kernel_args_thread_create {
    KARGSLOT(pid_t                  pid);
    KARGSLOT(void                   (*func)(union sigval));
    KARGSLOT(void                   *arg);
    KARGSLOT(struct _thread_attr    *attr);
} thread_create;

// структура удаление потока
struct _kernel_args_thread_destroy {
    KARGSLOT(int32_t	tid);
    KARGSLOT(int32_t	priority);
    KARGSLOT(void	*status);
} thread_destroy;

// структура отсоединения потока
struct _kernel_args_thread_detach {
    KARGSLOT(int32_t	tid);
} thread_detach;

// структура отмены потока
struct kerargs_thread_cancel {
    KARGSLOT(int32_t	tid);
    KARGSLOT(void	(*canstub)());
} thread_cancel;

// структура присоединения потока
struct kerargs_thread_join {
    KARGSLOT(int32_t	tid);
    KARGSLOT(void	**status);
} thread_join;

// структура потока данных
struct kerargs_thread_ctl {
    KARGSLOT(int32_t    cmd);
    KARGSLOT(void	*data);
} thread_priv;