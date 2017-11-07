#ifndef GENERIC_COMPILER_H
#define GENERIC_COMPILER_H

#ifdef __GNUC__
    #include _SOS_HDR_(compiler-gcc.h)
#endif

// проверка для переменных в своем адресном пространстве
#ifdef __CHECKER__
    #define __kernel    __attribute__((address_space(0)))
    #define __user      __attribute__((noderef, address_space(1)))
    #define __iomem     __attribute__((noderef, address_space(2)))
    #define __percpu    __attribute__((noderef, address_space(3)))

    #define __force     __attribute__((force))

    #define __acquire(x)    __context__(x, 1)
#else
    #define __kernel
    #define __user
    #define __iomem
    #define __percpu

    // проверка адреса пользователя
    #define __chk_user_ptr(x)   (void)0
    #define __chk_io_ptr(x)     (void)0

    #define __force

    #define __acquires(x)
    #define __releases(x)
    #define __acquire(x)        (void)0
    #define __release(x)        (void)0

    #define __cond_lock(x, c)    (c)
#endif

// функцию с данным атрибутом нельзя будет трассировать
#define notrace __attribute__((no_instrument_function))

// указатель ptr + смещение 
#ifndef RELOC_HIDE
    #define RELOC_HIDE(ptr, off) ({ unsigned long __ptr;\
        __ptr = (unsigned long) (ptr);\
       (typeof(ptr)) (__ptr + (off)); })
#endif

// определение выравнивания
#define __aligned(x)        __attribute__((aligned(x)))

// отмена любых ограничений для встраиваемой функции
#define __always_inline     inline __attribute__((always_inline))

// информация для предсказания ветвления
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

// барьер компилятора (соблюдение порядка выполнения операций для компилятора)
#ifndef barrier
    #define barrier()   asm volatile("": : :"memory")
#endif

#ifndef __used
    #define __used      __attribute__((__used__))
#endif 

#define __compiler_offsetof(a, b)    __builtin_offsetof(a, b)

#define ACCESS_ONCE(x)  (*(volatile typeof(x) *)&(x))
#endif /* GENERIC_COMPILER_H */