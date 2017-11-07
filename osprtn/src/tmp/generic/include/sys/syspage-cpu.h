enum {
    CPUPAGE_ADDR = -1,	/* R */
    CPUPAGE_TLS = 0,	/* R */
    CPUPAGE_PLS,	/* RW */
    CPUPAGE_SYSPAGE,	/* R */
    CPUPAGE_CPU,	/* R */
    CPUPAGE_STATE,	/* R */
    CPUPAGE_MAX
};

struct cpupage_entry {
    _SPPTR(struct _thread_local_storage)    tls;
    _SPPTR(struct _process_local_storage)   pls;
    _SPPTR(struct syspage_entry)            syspage;
    
    unsigned long                           cpu;        // тип CPU
    unsigned long                           state;      // состояние 
    union {
        struct {
            long dummy[8];
        } dummy;
    } un;
    unsigned long                           spare[8];
};