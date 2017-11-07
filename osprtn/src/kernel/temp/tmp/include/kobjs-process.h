// структура процесса
struct _process_entry {
    PROCESS                         *next;              // следующий процесс
    pid_t                           pid;                // номер процесса
    uint32_t                        flags;              // флаги процесса
    ADDRESS                         *memory;            // адрес памяти
    uintptr_t                       boundry_addr;
    VECTOR                          chancons;		// Channels and non-fd connect vector.
    VECTOR                          fdcons;		// Fd connection vector.
    DEBUG                           *debugger;          // отладчик
    
    struct _process_local_storage   *pls;       // локальное хранилище процесса
    
    volatile uint64_t       running_time;       // время запуска
    volatile uint64_t       system_time;        // системное время
	
};