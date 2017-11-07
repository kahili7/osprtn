struct _connect_entry {
    CONNECT                 *next;
    uint16_t                scoid;
    int16_t                 infoscoid;
    uint8_t                 type;
    uint8_t                 zero;
    uint16_t                flags;		// COF_*
    PROCESS                 *process;
    CHANNEL                 *channel;
    uint32_t                links;
    
    union {
        struct {
            uint32_t        nd;
            pid_t           pid;
            uint32_t        chid;
            uint32_t        seq;
            CONNECT         *cop;
            CONNECT         *next;
        } lcl;
        
        struct {
            CREDENTIAL      *cred;
            uint32_t        nd;
            pid_t           pid;
            pid_t           sid;
            uint32_t        flags;	// _NTO_CI_*
            uint32_t        coid;
        } net;
    } un;
    
    THREAD                  *restart; /* restart pointer, used by async messaging */
    struct _asyncmsg_connection_descriptor *cd; /* for async messaging */
    uint32_t         sendq_size;
};