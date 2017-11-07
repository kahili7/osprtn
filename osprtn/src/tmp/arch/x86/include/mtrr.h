#ifndef ARCH_X86_MTRR_H
#define ARCH_X86_MTRR_H

/*
 * диапазонные регистры типа памяти
 * (политика кэширования памяти)
 */
#ifdef __i386__
#endif

// до 8 пар MSR, каждая из которых задает произвольный участок памяти 
struct x86_mtrr_variable_range {
    _Uint32t base_lo;
    _Uint32t base_hi;
    _Uint32t mask_lo;
    _Uint32t mask_hi;
};

#define MTRR_NUM_FIXED_RANGES 88
#define MTRR_MAX_VAR_RANGES 256

typedef _Uint8t mtrr_type;

// типы регистров mtrr
struct x86_mtrr_state_type {
    struct x86_mtrr_variable_range variable_ranges[MTRR_MAX_VAR_RANGES];
    mtrr_type fixed_ranges[MTRR_NUM_FIXED_RANGES];
    mtrr_type def_type;
    unsigned char enabled;
    unsigned char have_fixed;   
};

#define X86_MTRR_TYPE_UNCACHEABLE       0
#define X86_MTRR_TYPE_WRITECOMBINING    1
#define X86_MTRR_TYPE_WRITETHROUGH      4
#define X86_MTRR_TYPE_WRITEPROTECTED    5
#define X86_MTRR_TYPE_WRITEBACK         6
#define X86_MTRR_NUM_TYPE               7

#endif /* ARCH_X86_MTRR_H */