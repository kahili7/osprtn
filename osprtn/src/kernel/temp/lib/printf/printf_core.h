#ifndef KERNEL_LIB_PRINTF_PRINTF_CORE_H
#define KERNEL_LIB_PRINTF_PRINTF_CORE_H

typedef struct printf_spec {
    // возвращает количество напечатанных символов или eof
    int (*str_write)(const char *, size_t, void *);

    // (расширенная) возвращает количество напечатанных символов или eof
    int (*wstr_write)(const wchar_t *, size_t, void *);

    // пользовательские данные
    void *data;
} printf_spec_t;

int printf_core(const char *fmt, printf_spec_t *ps, va_list ap);
#endif /* KERNEL_LIB_PRINTF_PRINTF_CORE_H */