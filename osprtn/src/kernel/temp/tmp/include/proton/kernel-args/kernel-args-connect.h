// структура установки соединения
struct _kernel_args_connect_attach {
    KARGSLOT(uint32_t   nd);
    KARGSLOT(pid_t      pid);
    KARGSLOT(int32_t    chid);
    KARGSLOT(int32_t    index);
    KARGSLOT(int32_t    flags);
    KARGSLOT(void       *cd);
} connect_attach;

// структура закрытия соединения
struct _kernel_args_connect_detach {
    KARGSLOT(int32_t    coid);
} connect_detach;

// структура с инфо о клиенте
struct _kernel_args_connect_client_info {
    KARGSLOT(int32_t                scoid);
    KARGSLOT(struct _client_info    *info);
    KARGSLOT(int32_t                ngroups);
} connect_client_info;

// структура с инфо о сервере
struct _kernel_args_connect_server_info {
    KARGSLOT(pid_t                  pid);
    KARGSLOT(int32_t                coid);
    KARGSLOT(struct _server_info    *info);
} connect_server_info;

// структура флагов соединения
struct _kernel_args_connect_flags {
    KARGSLOT(int32_t    pid);
    KARGSLOT(int32_t    coid);
    KARGSLOT(int32_t    mask);
    KARGSLOT(int32_t    bits);
} connect_flags;