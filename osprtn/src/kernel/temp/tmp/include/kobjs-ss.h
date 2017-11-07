// структура пополнения информации о планировании
struct _ss_replenish {
    struct _ss_replenish    *next;      //след. элемент
    THREAD                  *thp;	//поток для пополнения
    uint64_t                amount;	//сумма пополнения (nsec)
    uint64_t                repl_time;	//когда для пополнения этого элемента (nsec)			
};

// структура с информацией о планировании
struct _ss_schedinfo {
    uint8_t                 low_priority;       // нижний приоритет
    uint8_t                 org_priority;	//0 if not dropped, pre-drop priority otherwise
    uint16_t                reserved;
    uint16_t                max_repl;		//максимальный номер пополнения
    uint16_t                repl_count;		//количество пополнений в исполнении
    uint64_t                repl_period;	//период пополнения (nsec)
    uint64_t                init_budget;	//первоначальный бюджет на поток (nsec)
    uint64_t                curr_budget;	//текущий бюджет на поток (nsec)
    uint64_t                activation_time;	//когда этот поток был "активирован"
    uint64_t                consumed;		//количество потребляемой на этот пробег
    struct _ss_replenish    replenishment;		
};