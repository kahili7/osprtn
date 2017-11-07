#ifndef KERNEL_MEMMGR_VMM_H
#define KERNEL_MEMMGR_VMM_H

// структур данных диспетчера виртуальной памяти

#include "mm_internal.h"

struct mm_map_head {
    struct mm_map       *head;
    struct mm_map       *rover;
    volatile unsigned   lock;
    u32_t               start;
    u32_t               end;
    volatile unsigned   walk_gen;
};

struct map_set {
    struct mm_map_head	*head;
    struct mm_map       *first;
    struct mm_map       *last;
    struct mm_map       *prev;
    int                 flags;
};

struct mm_object_ref {
    struct mm_object_ref    *next;
    struct mm_aspace        *adp;
    OBJECT                  *obp;
    struct mm_map           *first_ref;
    int                     fd;
};

struct mm_map {
    struct mm_map           *next;
    struct mm_object_ref    *obj_ref;
    u64_t                   offset;
    
    struct {
        struct mm_map   *next;
        struct mm_map   **owner;
    } ref;
    
    u32_t                   start;
    u32_t                   end;
    int                     reloc;
    unsigned                mmap_flags;
    unsigned                extra_flags;
    unsigned short          last_page_bss;
    u8_t                    spare;
    volatile u8_t           inuse;
};

#define EXTRA_FLAG_MADV_MASK        0x000f // bottom 4 bits are POSIX_MADV_*
#define EXTRA_FLAG_LOCK             0x0010
#define EXTRA_FLAG_RDONLY           0x0020
#define EXTRA_FLAG_LOADER           0x0040
#define EXTRA_FLAG_NOINHERIT        0x0080 // for minherit(), if we implement it
#define EXTRA_FLAG_SPECIAL          0x0100
#define EXTRA_FLAG_PRIMARY_STK      0x0200 // Can indicate with MAP_STACK & EXTRA_FLAG_LOADER if we need a bit
#define EXTRA_FLAG_CACHE_CLEANED    0x0400 // Only used with direct mappings
#define EXTRA_FLAG_GBL_VADDR        0x0800
#define EXTRA_FLAG_RLIMIT_DATA      0x1000 // include in rlimit accounting

struct mm_area_space {
    struct mm_map_head      map;
    
    struct  {
        u32_t   vmem;
        u32_t	data;
        u32_t	stack;
        u32_t	memlock;
        u32_t	rss;
    } rlimit;
    
    OBJECT                  *anon;
    struct memmgr_rwlock    rwlock;
    unsigned                fault_owner;
    unsigned                flags;
    u32_t                   tmap_base;
    size_t                  tmap_size;
    struct cpu_mm_area_space    cpu;
};

#define MM_ASFLAG_LOCKALL		0x00000001
#define MM_ASFLAG_ISR_LOCK		0x00000002
#define MM_ASFLAG_ISR_INPROGRESS	0x00000004
#define MM_ASFLAG_PRIVATIZING		0x00000008
#define MM_ASFLAG_PADDR64_SAFE		0x00000010

struct mm_pte_manipulate {
    paddr_t     paddr;
    ADDRESS	*adp;
    u32_t       start;
    u32_t	end;
    u32_t	split_end;
    u32_t	first;
    unsigned	prot;
    unsigned	op;
    unsigned	special;
    unsigned	shmem_flags;
};

#define PTE_OP_MAP		0x0001
#define PTE_OP_PROT		0x0002
#define PTE_OP_UNMAP		0x0004
#define PTE_OP_PREALLOC		0x0008
#define PTE_OP_BAD		0x0010
#define PTE_OP_PREEMPT		0x0080
#define PTE_OP_MERGESTARTED	0x0100
#define PTE_OP_TEMP		0x0200
#define PTE_OP_FORCEMERGE	0x0400

#endif /* KERNEL_MEMMGR_VMM_H */