#define PRIL_ENTRY_FIELDS\
	union {\
            struct pril_entry   *pril;\
            THREAD              *thread;\
            PULSE               *pulse;\
            SYNCEVENT           *sev;\
	} next;\
	union {\
            struct pril_entry   *prio_tail;\
            struct pril_entry   **pril;	\
            THREAD              **thread;\
            PULSE               **pulse;\
            SYNCEVENT           **sev;\
	} prev;\
	uint8_t                 type;\
	uint8_t                 priority;

typedef struct _pril_entry {
    PRIL_ENTRY_FIELDS
} PRIL;

struct _pril_update {
    struct _pril_update *next;
    struct _pril_update *prev;
    PRIL                *pril;
};

typedef struct {
    PRIL    *data;
} PRIL_HEAD;