#ifndef KERNEL_MEMMGR_PALLOC_H
#define KERNEL_MEMMGR_PALLOC_H

struct syspage_entry;

// ограничитель аллокатора
struct palloc_restrict {
    struct palloc_restrict  *next;
    //int (*checker)(struct syspage_entry *, u64_t *, u64_t *, size_t, size_t); 
    word_t                  start;
    word_t                  end;
};

// двухсвязный список для свободных блоков 
struct palloc_free_link {
    struct palloc_quantum   *next;
    struct palloc_quantum   *prev;
};

// односвязный список для использованных блоков 
struct palloc_inuse_link {
    struct palloc_quantum   *next;
    u32_t                   qpos;
};

// структура выделения памяти 
struct palloc_quantum {
    union {
        struct palloc_inuse_link    inuse;
        struct palloc_free_link     free;
    } u;
    
    s32_t   run;	// run size if > 0, run backup if < 0, search if 0
    u16_t   blk;	// if == PAQ_BLK_FAKE, fake entry (see below)
    u16_t   flags;
};

// структура фейковой памяти 
struct palloc_quantum_fake {
    struct palloc_quantum   q;
    word_t                  paddr;
};

#ifndef QUANTUM_BITS
    #define QUANTUM_BITS    12
#endif

#define QUANTUM_SIZE    (1 << QUANTUM_BITS)

// флаги структуры
#define PALLOCQ_FLAG_UNUSED         0x8000
#define PALLOCQ_FLAG_INITIALIZED    0x4000
#define PALLOCQ_FLAG_ZEROED         0x2000
#define PALLOCQ_FLAG_INUSE          0x1000

#define PALLOCQ_FLAG_HAS_INSTRS     0x0800
#define PALLOCQ_FLAG_HAS_SYNC       0x0400
#define PALLOCQ_FLAG_LOCKED         0x0200
#define PALLOCQ_FLAG_MODIFIED       0x0100

#define PALLOCQ_FLAG_INIT_REQUIRED  0x0080 // Only used with pa_quantum's.
#define PALLOCQ_FLAG_RDB            0x0080 // Only used with pa_quantum_fake's.
#define PALLOCQ_FLAG_SYSTEM         0x0040
#define PALLOCQ_FLAG_ACTIVE         0x0020
#define PALLOCQ_FLAG_UNMOVABLE      0x0010 // can't be moved by defragmentation algorithms

#define PALLOCQ_FLAG_COLOUR_MASK    0x000f  // 15 цветов
#define PALLOCQ_COLOUR_NONE         (~0 & PALLOCQ_FLAG_COLOUR_MASK)

#define PALLOCQ_BLK_FAKE            ((u16_t)~0)

#define PALLOCQ_GET_COLOUR(pq)      ((pq)->flags & PALLOCQ_FLAG_COLOUR_MASK)
#define PALLOCQ_SET_COLOUR(pq, c)   ((pq)->flags = (c) | ((pq)->flags & ~PALLOCQ_FLAG_COLOUR_MASK))

// количество очередей
#define PALLOC_FREE_QUEUES      8
#define PALLOC_DEFAULT_QUEUE    0

struct block_head {
    union {
        u32_t	paddr32;
        u64_t	paddr64;
        word_t  paddr;
    } start;
    
    union {
        u32_t	paddr32;
        u64_t	paddr64;
        word_t  paddr;
    } end;
    
    unsigned generation;
    unsigned num_to_clean;
    unsigned num_quanta;
    unsigned max_free_run;
    
    struct palloc_quantum       *quanta;
    struct palloc_free_link     free[PALLOC_FREE_QUEUES];
};
#endif /* KERNEL_MEMMGR_PALLOC_H */