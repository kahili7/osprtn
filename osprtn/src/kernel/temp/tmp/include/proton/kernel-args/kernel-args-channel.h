// структура создание канала
struct _kernel_args_channel_create {
    KARGSLOT(int32_t    flags);
    KARGSLOT(mode_t     mode);
    KARGSLOT(size_t     bufsize);
    KARGSLOT(unsigned   maxbuf);
    KARGSLOT(struct sigevent    *event);
    KARGSLOT(struct _cred_info  *cred);
} channel_create;

// структура удаление канала
struct _kernel_args_channel_destroy {
    KARGSLOT(int32_t    chid);
} channel_destroy;