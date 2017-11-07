#ifndef GENERIC_MSG_IOMSG_H
#define GENERIC_MSG_IOMSG_H

#include <platform.h>

enum _msg_bases {
    _IO_BASE = 0x100,
    _IO_MAX = 0x1FF
};

enum _io__Uint16types {
    _IO_CONNECT = _IO_BASE,
    _IO_READ,
    _IO_WRITE,
    _IO_RSVD_CLOSE_OCB,		/* Place holder in jump table */
    _IO_STAT,
    _IO_NOTIFY,
    _IO_DEVCTL,
    _IO_RSVD_UNBLOCK,		/* Place holder in jump table */
    _IO_PATHCONF,
    _IO_LSEEK,
    _IO_CHMOD,
    _IO_CHOWN,
    _IO_UTIME,
    _IO_OPENFD,
    _IO_FDINFO,
    _IO_LOCK,
    _IO_SPACE,
    _IO_SHUTDOWN,
    _IO_MMAP,
    _IO_MSG,
    _IO_RSVD,
    _IO_DUP,
    _IO_CLOSE,
    _IO_RSVD_LOCK_OCB,		/* Place holder in jump table */
    _IO_RSVD_UNLOCK_OCB,	/* Place holder in jump table */
    _IO_SYNC,
    _IO_POWER
};

enum _io_msg_xtypes {
    _IO_XTYPE_NONE,
    _IO_XTYPE_READCOND,
    _IO_XTYPE_MQUEUE,
    _IO_XTYPE_TCPIP,
    _IO_XTYPE_TCPIP_MSG,
    _IO_XTYPE_OFFSET,
    _IO_XTYPE_REGISTRY,
    _IO_XTYPE_MASK =		0x000000ff,
    _IO_XFLAG_DIR_EXTRA_HINT =	0x00000100,
    _IO_XFLAG_NONBLOCK =	0x00004000,
    _IO_XFLAG_BLOCK =		0x00008000
};

/* struct _io_connect subtype */
enum _io_connect_subtypes {
    _IO_CONNECT_COMBINE,		/* Combine with IO msg */
    _IO_CONNECT_COMBINE_CLOSE,	/* Combine with IO msg and always close */
    _IO_CONNECT_OPEN,
    _IO_CONNECT_UNLINK,
    _IO_CONNECT_RENAME,
    _IO_CONNECT_MKNOD,
    _IO_CONNECT_READLINK,
    _IO_CONNECT_LINK,
    _IO_CONNECT_RSVD_UNBLOCK,	/* Place holder in jump table */
    _IO_CONNECT_MOUNT
};

/* struct _io_connect extra_type */
enum _io_connect_extra_type {
    _IO_CONNECT_EXTRA_NONE,
    _IO_CONNECT_EXTRA_LINK,
    _IO_CONNECT_EXTRA_SYMLINK,
    _IO_CONNECT_EXTRA_MQUEUE,
    _IO_CONNECT_EXTRA_PHOTON,
    _IO_CONNECT_EXTRA_SOCKET,
    _IO_CONNECT_EXTRA_SEM,
    _IO_CONNECT_EXTRA_RESMGR_LINK,
    _IO_CONNECT_EXTRA_PROC_SYMLINK,
    _IO_CONNECT_EXTRA_RENAME,
    _IO_CONNECT_EXTRA_MOUNT,
    _IO_CONNECT_EXTRA_MOUNT_OCB,
    _IO_CONNECT_EXTRA_TYMEM
};

struct _xtype_readcond {
    _Int32t min;
    _Int32t time;
    _Int32t timeout;
};

struct _xtype_offset {
    off64_t offset;
};

/* struct _io_connect ioflag (non-masked values match O_? in fcntl.h) */
#define _IO_FLAG_RD					0x00000001  /* read permission */
#define _IO_FLAG_WR					0x00000002  /* write permission */
#define _IO_FLAG_MASK				0x00000003  /* permission mask */

/* struct _io_connect eflag */
#define _IO_CONNECT_EFLAG_DIR		0x01	/* Path referenced a directory    */
#define _IO_CONNECT_EFLAG_DOT		0x02	/* Last component was . or ..     */
#define _IO_CONNECT_EFLAG_DOTDOT	0x04	/* Last component was ..          */

/*
 * return status from connect (These are continuation cases that
 * always negative (RET_FLAG is set). To avoid conflicting io msgs
 * must never return a negative status
 */
#define _IO_CONNECT_RET_UMASK		0x00020000	/* umask field in link reply is valid */
#define _IO_CONNECT_RET_NOCTTY		0x00040000	/* No controling terminal defined  */
#define _IO_CONNECT_RET_CHROOT		0x00080000	/* chroot_len field in link reply is valid */
#define _IO_CONNECT_RET_MSG			0x00100000	/* Connect to server and send new message */

#define _IO_CONNECT_RET_TYPE_MASK	0x0001e000	/* Mask for returned file type */
#define _IO_CONNECT_RET_FTYPE		0x00008000	/* File type was matched, _io_connect_ftype_reply expected */
#define _IO_CONNECT_RET_LINK		0x00010000  /* Not fully resolved, follow link */

#define _IO_CONNECT_RET_FLAG		0x80000000	/* Must be set to signify connect is returing */

#define _IO_SET_CONNECT_RET(_c, _s)	_RESMGR_STATUS(_c, _IO_CONNECT_RET_FLAG | (_s))		/* Sets the connect return code */

// структура ресурса менеджера соединить сообщения
struct _io_connect {
    _Uint16t    type;           // _IO_CONNECT
    _Uint16t    subtype;        /* _IO_CONNECT_? */
    _Uint32t    file_type;	/* _FTYPE_? in sys/ftype.h */
    _Uint16t	reply_max;      // максимальная длина ответного сообщения
    _Uint16t	entry_max;      // максимальное количество _io_connect_entry структур, что ресурс менеджер готов принять
    _Uint32t	key;            // резерв
    _Uint32t	handle;         // дескриптор, возвращаемый resmgr_attach()
    _Uint32t	ioflag;		/* O_? in fcntl.h & _IO_FLAG_? */
    _Uint32t	mode;		/* S_IF? in sys/stat.h */
    _Uint16t	sflag;		/* SH_? in share.h */
    _Uint16t	access;		/* S_I in sys/stat.h */
    _Uint16t	zero;
    _Uint16t	path_len;       // длина пути, по которому член
    _Uint8t	eflag;		/* _IO_CONNECT_EFLAG_? */
    _Uint8t	extra_type;	/* _IO_CONNECT_EXTRA_? */
    _Uint16t	extra_len;      // длина дополнительных данных, включенных в сообщение
    char	path[1];	// путь, что клиент пытается установить соединение, относительно ресурса менеджера монтирования
};

// cтруктура сообщения о подключении, который перенаправляет клиента на другой ресурс
struct _io_connect_link_reply {
    _Uint32t    reserved1;
    _Uint32t    file_type;      /*_FTYPE_? in sys/ftype.h */
    _Uint8t	eflag;          /* _IO_CONNECT_EFLAG_? */
    _Uint8t     reserved2[1];
    _Uint16t	chroot_len;	/* len of chroot in returned path*/
    _Uint32t	umask;		/* S_IF? in sys/stat.h */
    _Uint16t	nentries;	// если этот член равен нулю, этот путь является символической ссылкой
    _Uint16t	path_len;       /* len includs null, if zero, path is null terminated */
};

// структура сообщения о подключении дает статус и тип файла
struct _io_connect_ftype_reply {
    _Uint16t    status;         /* Typically an errno */
    _Uint16t    reserved;
    _Uint32t    file_type;      /* _FTYPE_? in sys/ftype.h */
};

// типы данных для операций
typedef union {
    struct _io_connect              connect;
    struct _io_connect_link_reply   link_reply;
    struct _io_connect_ftype_reply  ftype_reply;
} io_open_t;

typedef union {
    struct _io_connect              connect;
    struct _io_connect_link_reply   link_reply;
    struct _io_connect_ftype_reply  ftype_reply;
} io_unlink_t;


typedef union {
    struct _io_connect              connect;
    struct _io_connect_link_reply   link_reply;
    struct _io_connect_ftype_reply  ftype_reply;
} io_rename_t;

typedef union _io_rename_extra {
    char path[1];
} io_rename_extra_t;

typedef union {
    struct _io_connect              connect;
    struct _io_connect_link_reply   link_reply;
    struct _io_connect_ftype_reply  ftype_reply;
} io_mknod_t;

typedef union {
    struct _io_connect              connect;
    struct _io_connect_link_reply   link_reply;
    struct _io_connect_ftype_reply  ftype_reply;
} io_readlink_t;

typedef union {
    struct _io_connect              connect;
    struct _io_connect_link_reply   link_reply;
    struct _io_connect_ftype_reply  ftype_reply;
} io_link_t;



#endif /* GENERIC_MSG_IOMSG_H */