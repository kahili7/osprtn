#ifndef GENERIC_TYPECHECK_H
#define GENERIC_TYPECHECK_H

// проверка типа
#define typecheck(type, x)\
        ({	type __dummy;\
            typeof(x) __dummy2;\
            (void)(&__dummy == &__dummy2);\
            1;\
        })

// проверка типа указателя на функцию
#define typecheck_fn(type, function)\
        ({  typeof(type) __tmp = function;\
            (void)__tmp; \
        })
#endif /* GENERIC_TYPECHECK_H */