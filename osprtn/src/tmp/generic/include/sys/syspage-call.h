struct debug_callout {
    _SPFPTR(void, display_char, (struct syspage_entry *, char));
    _SPFPTR(int, poll_key, (struct syspage_entry *));
    _SPFPTR(int, break_detect, (struct syspage_entry *));
    _SPFPTR(void, spare[1],);
};

typedef enum {
    DEBUG_WATCHDOG_STOP = 0,
    DEBUG_WATCHDOG_CONTINUE,
    DEBUG_WATCHDOG_FEED
} debug_watchdog_cmd;

struct callout_entry {
    _SPFPTR(void, reboot, (struct syspage_entry *, int));
    _SPFPTR(int, power, (struct syspage_entry *, unsigned, _Uint64t *));

    _SPFPTR(void, timer_load, (struct syspage_entry *, struct qtime_entry *));
    _SPFPTR(int, timer_reload, (struct syspage_entry *, struct qtime_entry *));
    _SPFPTR(unsigned, timer_value, (struct syspage_entry *, struct qtime_entry *));

    struct debug_callout debug[2];

    _SPFPTR(void, debug_watchdog, (struct syspage_entry *, debug_watchdog_cmd));
    _SPFPTR(void, spare[3],);
};

struct callin_entry {
    _SPFPTR(void, spare0,);
    _SPFPTR(int, interrupt_mask, (unsigned, int));
    _SPFPTR(int, interrupt_unmask, (unsigned, int));
    _SPFPTR(int, trace_event, (int *));
    _SPFPTR(void, spare[11],);
};
