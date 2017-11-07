typedef uint8_t	int_fl_t; /* for typecasting in ker_message.c */

// структура потока
struct _thread_entry {		// Also used for vthread_entry
    PRIL_ENTRY_FIELDS
    uint8_t		real_priority;  // фактический приоритет потока без повышения
    uint8_t		policy;
    uint8_t		state;
    uint8_t		reserved_byte;
    uint8_t		runcpu;
    int_fl_t		internal_flags;
    uint64_t		timestamp_last_block; /* set to copy of snap_time() anytime this thread blocks. not valid if state is STATE_READY or STATE_RUNNING */ 
    PROCESS		*aspace_prp;
    volatile uint32_t   async_flags;
    DISPATCH		*dpp;
    uint32_t		timeout_flags;
    uint32_t		flags;
    uint32_t		sched_flags; /* for aps scheduling */
    int32_t		syscall;
    PROCESS		*process;
    int32_t		tid;
    DISPATCH		*orig_dpp;    /* after being a guest of another aps partition, it's returned here */
    union {
            struct _ss_schedinfo *ss_info;
            uint32_t rr_ticks;
    } schedinfo;
    union {
            struct {			// type = THREAD
                    struct _thread_local_storage *tls;
                    void			*stackaddr;
                    size_t			 stacksize;
            }				lcl;
            struct {			// type = VTHREAD
                    uint32_t		 srcnd;		// remote view of our node (Overlays thread_local_storage pointer)
                    void			*reserved;
                    int32_t			 vtid;		// virtual thread id (index in thread_vector)
            }				net;
    }				 un;
    THREAD			*client; /* the client that the server thread works on behalf */
    void			*blocked_on;
    THREAD			*restart;
    // The following is used to hold arguments when a thread blocks to make
    // them easy to access in another threads context. Only a very small
    // number of arguments need to be saved.
    union {
            struct {	// Used by send/read/write for general messages
                    IOV					*rmsg;		// Must be 1st arg
                    int32_t				 rparts;	// Must be 2nd arg
                    uint32_t			 coid;		// Must be 3rd arg
                    uint32_t			 msglen;	// Must be 4th arg
                    uint32_t			 dstmsglen;	// Must be 5th arg
                    THREAD				*server; /* the thread in server to serve this msg. Must be 6th arg */
                    uint32_t			 srcmsglen;
                    IOV					*smsg;
                    uint32_t			 sparts;
                    THREAD				*dthp;		// Dest thread for message restarts
                    IOV					 siov[_NUM_CACHED_SEND_IOV];
                    IOV					 riov[_NUM_CACHED_REPLY_IOV];
            } ms;

            struct {	// Used by send for short messages
                    IOV					*rmsg;		// Must be 1st arg
                    int32_t				 rparts;	// Must be 2nd arg
                    uint32_t			 coid;		// Must be 3rd arg
                    uint32_t			 msglen;	// Must be 4th arg
                    uint32_t			 dstmsglen;	// Must be 5th arg
                    THREAD				*server; /* the thread in server to serve this msg. Must be 6th arg */
                    void				*fill[4];
                    uint8_t				 buff[_SHORT_MSG_LEN];
                    IOV					 riov[_NUM_CACHED_REPLY_IOV];
            } msbuff;

            struct {	// Used by nano_specret for get rcvinfo && short messages
                    IOV					*rmsg;		// Must be 1st arg
                    int32_t				 rparts;	// Must be 2nd arg
                    struct _msg_info	*info;
                    THREAD				*thp;
                    CONNECT				*cop;
                    uint32_t			 value;
                    int32_t				 id;
                    int8_t				 code;
            } ri;

#define _NTO_NOIOV				1UL << (8*sizeof(uint32_t)-1)	// Must agree with sparts/rparts
#if 0
            struct {	// Used by net (must align with ms)
                    IOV					*rmsg;		// Must be 1st arg
                    int32_t				 rparts;	// Must be 2nd arg
                    uint32_t			 vtid;
                    uint32_t			 msglen;	// Must be 4th arg
                    uint32_t			 dstmsglen;	// Must be 5th arg
                    uint32_t			 srcmsglen;	// Must match ms
                    IOV					*smsg;
                    uint32_t			 sparts;
                    uint32_t			 offset;
            } netms;
#endif
            struct {	// Used by ker_signal_suspend.
                    sigset_t		 sig_blocked;
            } ss;
            struct {	// Used by ker_signal_wait.
                    sigset_t		 sig_wait;
                    siginfo_t		*sig_info;
                    int32_t			 value;
                    pid_t			 pid;
                    int8_t			 signo;
                    int8_t			 code;
            } sw;
            struct {	// Used by ker_timer_timeout (nanosleep only)
                    struct _itimer		 left;
                    uint64_t			*timeptr;
                    uint32_t			spare;
            } to;
            struct {	// Used by ker_thread_join
                    void			**statusptr;
                    void			*status;
            } jo;
            struct {	// Used by to aquire a mutex (*_condvar_wait, *_mutex_lock)
                    sync_t			*mutex;
                    uint32_t		saved_timeout_flags;
                    uint32_t		owner; /* owner of *mutex */ 
                    SYNC			*next; /* next mutex in the thread mutex hold list */
                    SYNC			**prev; /* owner, next and prev only meaningful when the thread is the first one in a mutex waiting list */
                    uint8_t			ceiling; /* for change of mutex prio ceiling */
                    unsigned		incr;    /* count increment */
            } mu;
            struct {	// Used by async_flags processing in an SMP machine
                    uint32_t			save_ip;
                    uint32_t			save_type;
                    uint32_t			code;
                    uint32_t			fault_type;
                    uint32_t			fault_addr;
            } async;
            struct {	// Used to hold stuff during thread creation
                    void				*arg;
                    const struct _thread_attr *attr;
                    void				(*exitfunc)(void *status);
                    const struct _thread_attr *real_attr;
                    int					not_sigev_thread;
            } wa;

    } args;
    sigset_t		 sig_blocked;
    PRIL_HEAD		 sig_pending;
    uint32_t		 runmask;
    uint32_t		 default_runmask;
    char			*name;
    int32_t			 key;
    int32_t			 last_chid;
    void			*status;
#define SIZEOF_VTHREAD		offsetof(struct thread_entry, timeout)
// Items below are not needed for type=VTHREAD
    TIMER			*timeout;
    THREAD			*join;
    SYNC			*mutex_holdlist; /* list of holding mutexes whose waiting queue is not empty */
    uint64_t		 start_time;
    FPU_REGISTERS	*fpudata;
    volatile unsigned	ticker_using;
    volatile uint64_t running_time;
    struct cpu_thread_entry	cpu; // Must be just before 'reg' field.
    CPU_REGISTERS	 reg;
};

