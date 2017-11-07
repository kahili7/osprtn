// структура присоединения прерывания 
struct _kernel_args_interrupt_attach {
    KARGSLOT(int32_t                intr);
    KARGSLOT(const struct sigevent  *(*handler)(void *area, int id));
    KARGSLOT(void                   *area);
    KARGSLOT(int32_t                areasize);
    KARGSLOT(int32_t                flags);
} interrupt_attach;

// структура отсоединения прерывания функцией
struct _kernel_args_interrupt_detach_func {
    KARGSLOT(int32_t                intr);
    KARGSLOT(const struct sigevent  *(*handler)(void *area, int id));
} interrupt_detach;

// структура отсоединения прерывания
struct _kernel_args_interrupt_detach {
    KARGSLOT(int32_t    id);
} interrupt_detach_id;

// структура ожидания прерывания
struct _kernel_args_interrupt_wait {
    KARGSLOT(int32_t    flags);
    KARGSLOT(uint64_t   *timeout);
} interrupt_wait;

// структура маскировочного прерывания
struct _kernel_args_interrupt_mask {
    KARGSLOT(int32_t    intr);
    KARGSLOT(int32_t    id);
} interrupt_mask;

// структура немаскировочного прерывания
struct _kernel_args_interrupt_unmask {
    KARGSLOT(int32_t    intr);
    KARGSLOT(int32_t    id);
} interrupt_unmask;