#ifndef LIB_C_STDARG_H
#define LIB_C_STDARG_H

typedef	__builtin_va_list __va_list;

#define	__va_start(list, name)	__builtin_stdarg_start(list, name)
#define	__va_arg(list, type)	__builtin_va_arg(list, type)
#define	__va_end(list)		__builtin_va_end(list)
#define	__va_copy(to, from)	__builtin_va_copy(to, from)

typedef __va_list va_list;
#define	va_start(list, name)	__va_start(list, name)
#define	va_arg(list, type)	__va_arg(list, type)
#define	va_end(list)		__va_end(list)
#define	va_copy(to, from)	__va_copy(to, from)
#endif /* LIB_C_STDARG_H */