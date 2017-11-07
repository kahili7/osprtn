#ifndef GENERIC_CONF_NAME_H
#define GENERIC_CONF_NAME_H

// символьные константы для sysconf
#if defined(CONFIG_POSIX1_199009)
    #define _SC_ARG_MAX			1           // параметр соответствующий ARG_MAX
    #define _SC_CHILD_MAX		2
    #define _SC_CLK_TCK			3
    #define _SC_NGROUPS_MAX		4
    #define _SC_OPEN_MAX		5
    #define _SC_JOB_CONTROL		6
    #define _SC_SAVED_IDS		7
    #define _SC_VERSION			8
    #define _SC_PASS_MAX		9
    #define _SC_LOGNAME_MAX		10
    #define _SC_PAGESIZE		11
    #define _SC_PAGE_SIZE		_SC_PAGESIZE
    #define _SC_XOPEN_VERSION           12
    #define _SC_STREAM_MAX		13
    #define _SC_TZNAME_MAX		14
#endif

#endif /* GENERIC_CONF_NAME_H */