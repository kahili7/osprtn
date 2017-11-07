// структура канала
struct _channel_entry {
    CHANNEL         *next;
    int32_t         chid;
    uint8_t         type;
    uint8_t         zero;
    uint16_t        flags;		// _NTO_CHF_*
    PROCESS         *process;
    PRIL_HEAD       send_queue;
    THREAD          *receive_queue;
    THREAD          *reply_queue;
    mode_t          mode; /* permissions */
};

struct _channel_async_entry {
    struct _channel_entry   ch;				/* basic channel_entry */
    struct _sigevent         event;			/* the event to be sent for notification */
    PROCESS                 *ev_prp;		/* the process who registers the event */
};

struct _gblmsg_entry {
    struct _gblmsg_entry    *next;
    unsigned                priority;
    size_t                  size;
};

struct _channel_gbl_entry {
    struct _channel_entry       ch;				/* basic channel_entry */
    struct _sigevent            event;			/* the event to be sent for notification */
    PROCESS                     *ev_prp;		/* the process who registers the event */
    int                         ev_coid;		/* handle to identify the owner of the event */
    size_t                      buffer_size;	/* size of kernel buffer */
    unsigned                    max_num_buffer;	/* maximum number of buffer allowed */
    unsigned                    num_curr_msg;	/* how many msgs in the channel send queue */ 
    struct _cred_info           cred;			/* credential */
    void                        *free;			/* free buffer list */
    struct _gblmsg_entry        *tail;			/* points to the tail of the queue */
    CONNECT                     *cons;			/* connection list for cleanup when channel is destroyed */
};