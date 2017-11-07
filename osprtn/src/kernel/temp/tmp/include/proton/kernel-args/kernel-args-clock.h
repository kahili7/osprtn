struct _kernel_args_clock_time {
    KARGSLOT(clockid_t  id);
    KARGSLOT(uint64_t	*new);
    KARGSLOT(uint64_t	*old);
} clock_time;

struct _kernel_args_clock_adjust {
    KARGSLOT(clockid_t              id);
    KARGSLOT(struct _clockadjust    *new);
    KARGSLOT(struct _clockadjust    *old);
} clock_adjust;

struct _kernel_args_clock_period {
    KARGSLOT(clockid_t              id);
    KARGSLOT(struct _clockperiod    *new);
    KARGSLOT(struct _clockperiod    *old);
    KARGSLOT(int32_t                external);
} clock_period;

struct _kernel_args_clock_id {
    KARGSLOT(int32_t    pid);
    KARGSLOT(int32_t    tid);
} clock_id;