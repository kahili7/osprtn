#ifndef KERNEL_GENERIC_DEBUG_H
#define KERNEL_GENERIC_DEBUG_H

#define SECTION_KDEBUG  ".kdebug"

// escape коды
#define TXT_CLRSCREEN		"\e[2J"
#define TXT_NORMAL		"\e[0m"
#define TXT_BRIGHT		"\e[1m"
#define TXT_REVERSED		"\e[7m"
#define TXT_FG_BLACK		"\e[30m"
#define TXT_FG_RED		"\e[31m"
#define TXT_FG_GREEN		"\e[32m"
#define TXT_FG_YELLOW		"\e[33m"
#define TXT_FG_BLUE		"\e[34m"
#define TXT_FG_MAGENTA		"\e[35m"
#define TXT_FG_CYAN		"\e[36m"
#define TXT_FG_WHITE		"\e[37m"
#define TXT_BG_BLACK		"\e[40m"
#define TXT_BG_RED		"\e[41m"
#define TXT_BG_GREEN		"\e[42m"
#define TXT_BG_YELLOW		"\e[43m"
#define TXT_BG_BLUE		"\e[44m"
#define TXT_BG_MAGENTA		"\e[45m"
#define TXT_BG_CYAN		"\e[46m"
#define TXT_BG_WHITE		"\e[47m"

#include DIR_BIND_ARCH(debug.h)

#if defined(CONFIG_DEBUG)
#else
    #define init_console(...)
    #define printf(fmt, args...)	do { } while (false)
    #define enter_kdebug(x)		do { } while (true)
    #define UNIMPLEMENTED()		do { } while (true)
    #define UNTESTED()		        do { } while (true)
    #define ASSERT(x)			do { } while (false)
    #define WARNING(fmt, args...)	do { } while (false)
    #define TRACE(x...)			do { } while (false)
    #define TRACEF(x...)		do { } while (false)
    #define spin_forever(x...)		do { } while (true)
    #define spin(x...)			do { } while (false)
#endif

#define panic(x...) do {\
            printf("PANIC in %s, %s, line %d:\n===> ", __PRETTY_FUNCTION__, __FILE__, __LINE__);\
            printf(x);\
            for (;;) enter_kdebug ("panic");\
        } while (false)

#endif /* KERNEL_GENERIC_DEBUG_H */