#ifndef KERNEL_OBJS_VECTOR_H
#define KERNEL_OBJS_VECTOR_H

typedef struct _VECTOR {
    USHORT  Count;
    USHORT  CountFree;
    PVOID   Free;
    PVOID   *Vector;
} VECTOR, *PVECTOR;

#define VECTOR_MAX          (0xFFFE)
#define VEC(v, i)           ((v)->Vector[i])
#define VECP(ptr, v, i)     (((USHORT)((ptr) = (v)->Vector[i]) & 3) ? NULL : (ptr))
#define VECP2(ptr, v, i)    (((USHORT)((ptr) = (v)->Vector[i]) & 1) ? NULL : VECAND((ptr), ~3))

#define VECAND(ptr, bits)   ((PVOID)((bits) & (USHORT)(ptr)))
#define VECOR(ptr, bits)    ((PVOID)((bits) | (USHORT)(ptr)))
#endif /* KERNEL_OBJS_VECTOR_H */