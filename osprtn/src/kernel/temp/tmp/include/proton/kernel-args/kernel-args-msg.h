// структура для отправки сообщения
struct _kernel_args_msg_sendv {
    KARGSLOT(int32_t    coid);      //
    KARGSLOT(IOV        *smsg);
    KARGSLOT(int32_t    sparts);
    KARGSLOT(IOV        *rmsg);
    KARGSLOT(int32_t    rparts);
} msg_sendv;

// структура для получения сообщения
struct _kernel_args_msg_receivev {
    KARGSLOT(int32_t		chid);
    KARGSLOT(int32_t		coid);
    KARGSLOT(IOV		*rmsg);
    KARGSLOT(int32_t		rparts);
    KARGSLOT(struct _msg_info	*info);
} msg_receivev;

// структура сообщения содержащия ответ
struct _kernel_args_msg_replyv {
    KARGSLOT(int32_t	rcvid);
    KARGSLOT(int32_t	status);
    KARGSLOT(IOV	*smsg);
    KARGSLOT(int32_t	sparts);
} msg_replyv;

// структура для чтения сообщения
struct _kernel_args_msg_readv {
    KARGSLOT(int32_t	rcvid);
    KARGSLOT(IOV	*rmsg);
    KARGSLOT(int32_t	rparts);
    KARGSLOT(int32_t	offset);
} msg_readv;

// структура для записи сообщения
struct _kernel_args_msg_writev {
    KARGSLOT(int32_t	rcvid);
    KARGSLOT(IOV	*smsg);
    KARGSLOT(int32_t	sparts);
    KARGSLOT(int32_t	offset);
} msg_writev;

// структура для чтения/записи сообщения
struct _kernel_args_msg_readwritev {
    KARGSLOT(int32_t	src_rcvid);
    KARGSLOT(IOV	*src_msg);
    KARGSLOT(int32_t	src_parts);
    KARGSLOT(int32_t	src_offset);
    KARGSLOT(int32_t	dst_rcvid);
    KARGSLOT(IOV	*dst_msg);
    KARGSLOT(int32_t	dst_parts);
    KARGSLOT(int32_t	dst_offset);
} msg_readwritev;

// структура для чтения вектора in/out сообщения
struct _kernel_args_msg_readiov {
    KARGSLOT(int32_t	rcvid);
    KARGSLOT(IOV	*iov);
    KARGSLOT(int32_t	parts);
    KARGSLOT(int32_t	offset);
    KARGSLOT(int32_t	flags);
} msg_readiov;

// структура информация о сообщении
struct _kernel_args_msg_info {
    KARGSLOT(int32_t		rcvid);
    KARGSLOT(struct _msg_info   *info);
} msg_info;

// структура сообщения для отправки пульса
struct _kernel_args_msg_sendpulse {
    KARGSLOT(int32_t	coid);
    KARGSLOT(int32_t	priority);
    KARGSLOT(int32_t	code);
    KARGSLOT(int32_t	value);
} msg_sendpulse;

// структура сообщения для доставки события
struct _kernel_args_msg_deliver_event {
    KARGSLOT(int32_t            rcvid);
    KARGSLOT(struct sigevent    *event);
} msg_deliver_event;

// структура сообщения для проверки события
struct _kernel_args_msg_verify_event {
    KARGSLOT(int32_t		rcvid);
    KARGSLOT(struct sigevent	*event);
} msg_verify_event;

// структура сообщения для ключевых данных
struct _kernel_args_msg_keydata {
    KARGSLOT(int32_t	rcvid);
    KARGSLOT(int32_t	op);
    KARGSLOT(uint32_t	key);
    KARGSLOT(uint32_t	*newkey);
    KARGSLOT(IOV	*msg);
    KARGSLOT(int32_t    parts);
} msg_keydata;

// структура сообщения с ошибкой
struct _kernel_args_msg_error {
    KARGSLOT(int32_t    rcvid);
    KARGSLOT(int32_t	err);
} msg_error;

// структура текущее сообщение
struct _kernel_args_msg_current {
    KARGSLOT(int32_t	rcvid);
} msg_current;