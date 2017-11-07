struct _pulse_entry {
    PRIL_ENTRY_FIELDS	// priority is a signal number for TYPE_SIGNAL
    uint8_t     spare;
    int8_t      code;
    uint32_t    value;
    int32_t     id;		// scoid if TYPE_PULSE or src pid if TYPE_SIGNAL
    unsigned    count;
};