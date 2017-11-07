#ifndef KERNEL_GENERIC_KERNEL_MEMCLASS_H
#define KERNEL_GENERIC_KERNEL_MEMCLASS_H

#define ARRAY_EL(e)     [(e)] =
#define STRUCT_FLD(e)   .e =

// тип используется о размере всех сведений о размере memclass
#ifndef _MEMSIZE_T
    #define _MEMSIZE_T  u64_t
    typedef _MEMSIZE_T  memsize_t;
#endif

// идентификатор класса
typedef u32_t   memclass_id_t;
#define memclass_id_t_INVALID   ((memclass_id_t)0xFFFFFFFF)

// структура определяет специфические ограничения на memory class и доступно только для чтения 
typedef struct _memclass_limits
{
    struct {
        struct {
            _MEMSIZE_T  min;		// minimum size of an allocation unit
            _MEMSIZE_T  max;		// maximum size of an allocation unit
        } size;
    } alloc;
} memclass_limits_t;

// структура определяет атрибуты memory class
typedef struct _memclass_attr
{
    _MEMSIZE_T          size;       // объем доступной памяти
    memclass_limits_t	limits;     // ограничения
} memclass_attr_t;

#define MEMCLASS_DEFAULT_ATTR \
{ \
    STRUCT_FLD(size) 0, \
    STRUCT_FLD(limits) \
        {STRUCT_FLD(alloc) \
            {STRUCT_FLD(size) \
                {STRUCT_FLD(min) 0, STRUCT_FLD(max) 0}}}, \
}

// структура определяет область зарезер. и нерезер. памяти
typedef struct _memclass_sizeinfo
{
    struct {
        _MEMSIZE_T  free;
        _MEMSIZE_T  used;
    } reserved;
    
    struct {
        _MEMSIZE_T  free;
        _MEMSIZE_T  used;
    } unreserved;
} memclass_sizeinfo_t;

// структура определяет данные полученные от memory class
typedef struct _memclass_info
{
    memclass_id_t	id;
    u32_t		reserved;
    memclass_attr_t	attr;
    memclass_sizeinfo_t size;
} memclass_info_t;

#endif /* KERNEL_GENERIC_KERNEL_MEMCLASS_H */