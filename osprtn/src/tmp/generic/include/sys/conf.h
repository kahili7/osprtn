#ifndef GENERIC_SYS_CONF_H
#define GENERIC_SYS_CONF_H

// функции
#define _CONF_NOP		(0U << 16)	/* Do nothing entry */
#define _CONF_LINK		(1U << 16)	/* table continues here */
#define _CONF_CALL		(2U << 16)	/* See if function will match */
#define _CONF_VALUE		(3U << 16)	// соответствующее значение
#define _CONF_END		(4U << 16)	// конец списка
#define _CONF_CMD_MASK		(0xfU << 16)

#define _CONF_STR		(0x1U << 20)	// строка
#define _CONF_NUM		(0x2U << 20)	// число
#define _CONF_COND_MASK		(0xfU << 20)    // маска

// модификаторы значений
#define _CONF_NUM_MIN		(1U << 24)
#define _CONF_NUM_MAX		(2U << 24)
#define _CONF_NUM_ADD		(3U << 24)
#define _CONF_MOD_MASK		(0xfU << 24)

// флаги
#define _CONF_STICKY		(0x1U << 28)	/* Used by library to make conf outlive the process */
#define _CONF_INDIRECT		(0x2U << 28)	/* Indirect pointer */
#define _CONF_FCN		(0x4U << 28)	/* Call function */
#define _CONF_FLAGS_MASK	(0xfU << 28)


#define	_CONF_NAME_MASK         (0xffffU)   // короткая маска
#define _CONF_NAME_LONG         (0xffffU)   // длинное имя


extern long *_confstr_list;     // список конфигурационных строк 
extern long *_sysconf_list;     // список системной конфигурации

extern void _conf_destroy(long *__list);
extern int _conf_get(const long *__list, int __name, long *__value, char *__str);
extern int _conf_set(long **__list, int __cmd, int __name, long __value, const char *__str);
#endif /* GENERIC_SYS_CONF_H */