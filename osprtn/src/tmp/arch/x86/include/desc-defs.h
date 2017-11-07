#ifndef ARCH_X86_DESC_DEFS_H
#define ARCH_X86_DESC_DEFS_H

// 8-байтный сегментный дескриптор
struct x86_desc_struct {
    union {
        struct {
            unsigned int a;
            unsigned int b;
        };
        
        struct {
            _Uint16t limit0;    // 0-15
            _Uint16t base0;     // 16-31
            unsigned base1:8, type:4, s:1, dpl:2, p:1;       // 32-47
            unsigned limit1:4, avl:1, l:1, d:1, g:1, base2:8;// 48-63
        };
    };
}__attribute__((packed));

#define GDT_ENTRY_INIT(flags, base, limit) { { { \
    .a = ((limit) & 0xffff) | (((base) & 0xffff) << 16), \
    .b = (((base) & 0xff0000) >> 16) | (((flags) & 0xf0ff) << 8) | ((limit) & 0xf0000) | ((base) & 0xff000000), \
} } }

// 16-байтный дескриптор шлюза
struct x86_gate_struct64 {
    _Uint16t offset_low;    // 0-15
    _Uint16t segment;       // 16-31
    unsigned ist:3, zero0:5, type:5, dpl:2, p:1;    //32-47
    _Uint16t offset_middle; // 48-63
    _Uint32t offset_high;
    _Uint32t zero1;
}__attribute__((packed));

// типы gate дескрипторов
enum {
    GATE_TASK = 0x5,
    GATE_CALL = 0xC,
    GATE_INTERRUPT = 0xE,
    GATE_TRAP = 0xF,	
};

// 16-байтный дескриптор LDT или задачи
struct x86_ldt_tss_struct64 {
    _Uint16t limit0;
    _Uint16t base0;
    unsigned base1:8, type:5, dpl:2, p:1;
    unsigned limit1:4, avl:1, zero0:2, g:1, base2:8;
    _Uint32t base3;
    _Uint32t zero1;
}__attribute__((packed));

// типы дескрипторов
enum {
    DESC_LDT = 0x2,
    DESC_TSS = 0x9,
    DESCTYPE_S = 0x10,	/* системный дескриптор */
};

#ifdef CONFIG_X86_64
    typedef struct x86_gate_struct64 gate_desc;
    typedef struct x86_ldt_tss_struct64 ldt_desc;
    typedef struct x86_ldt_tss_struct64 tss_desc;
    
    #define gate_offset(g)  ((g).offset_low | ((unsigned long)(g).offset_middle << 16) | ((unsigned long)(g).offset_high << 32))
    #define gate_segment(g) ((g).segment)
#else
    typedef struct x86_desc_struct gate_desc;
    typedef struct x86_desc_struct ldt_desc;
    typedef struct x86_desc_struct tss_desc;
    
    #define gate_offset(g)  (((g).b & 0xffff0000) | ((g).a & 0x0000ffff))
    #define gate_segment(g) ((g).a >> 16)
#endif

struct x86_desc_ptr_struct {
    unsigned short size;
    unsigned long address;
}__attribute__((packed));
#endif /* ARCH_X86_DESC_DEFS_H */