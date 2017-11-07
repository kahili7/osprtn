#ifndef GENERIC_MSG_SYSMSG_H
#define GENERIC_MSG_SYSMSG_H

enum _sys_bases {
    _SYSMSG_BASE =	0x0000,
    _SYSMGR_BASE =	0x0000,
    _SYSMGR_MAX = 	0x000f,
    _PROCMGR_BASE = 	0x0010,
    _PROCMGR_MAX = 	0x003f,
    _MEMMGR_BASE =	0x0040,
    _MEMMGR_MAX =	0x006f,
    _PATHMGR_BASE =	0x0070,
    _PATHMGR_MAX = 	0x009f,
    _CPUMSG_BASE =	0x00a0,
    _CPUMSG_MAX =	0x00cf,
    _RSRCDBMGR_BASE =	0x00d0,
    _RSRCDBMGR_MAX =	0x00d3,
    _SYSMSG_MAX =	0x00FF
};

enum {
    _SYS_CONF = _SYSMGR_BASE,
    _SYS_CMD,
    _SYS_LOG,
    _SYS_VENDOR
};

enum {
    _SYS_SUB_GET,
    _SYS_SUB_SET
};

// команды
enum {
    _SYS_CMD_REBOOT,
    _SYS_CMD_CPUMODE
};

// сообщение типа sys_conf_t
struct _sys_conf {
    _Uint16t    type;
    _Uint16t	subtype;
    _Int32t	cmd;
    _Int32t	name;
    _Int32t	spare;
    _Int64t	value;
};

struct _sys_conf_reply {
    _Uint32t    zero[3];
    _Int32t	match;
    _Int64t	value;
};

typedef union {
    struct _sys_conf        i;
    struct _sys_conf_reply  o;
} sys_conf_t;

// сообщение типа sys_cmd_t
struct _sys_cmd {
    _Uint16t    type;
    _Uint16t    cmd;
    _Uint32t	mode;
};

typedef union {
    struct _sys_cmd i;
} sys_cmd_t;

// сообщение типа sys_log_t
struct _sys_log {
    _Uint16t    type;
    _Uint16t	reserved;
    _Int32t	nbytes;
    _Uint32t	zero[2];
};

typedef union {
    struct _sys_log i;
} sys_log_t;

// сообщение типа sys_vendor_t
struct _sys_vendor {
    _Uint16t    type;
    _Uint16t	vendor_id;
    _Uint32t	reserved;
};

typedef union {
    struct _sys_vendor  i;
} sys_vendor_t;
#endif /* GENERIC_MSG_SYSMSG_H */