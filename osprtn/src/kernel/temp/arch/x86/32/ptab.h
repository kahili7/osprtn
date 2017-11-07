#ifndef KERNEL_ARCH_X86_32_PTAB_H
#define KERNEL_ARCH_X86_32_PTAB_H

#include DIR_ARCH(x86.h)

extern int      pae_enabled;    // is PAE turn on
extern unsigned pd_bits;        // page directory bits
extern unsigned pxe_bits;       // page directory pointer bits

// size page table (directory)
// used for both PDE & PTE
typedef union x86_pxe {
    u32_t   pxe32;
    u64_t   pxe64;
} pxe_t;

// PAE disabled
#define PXE1_BITS   2       // 2 bits of addr for each tbl entry
#define PD1_BITS    22      // 22 bits in page directory

#define PG1_REMAP       1023
#define PG1_PDIRADDR    (PG1_REMAP << PD1_BITS | PG1_REMAP << 12)   // Pointer to start of page directory 0xFFC00000 | 0x003FF000 = 0xFFFFF000
#define PG1_PTEADDR 	(PG1_REMAP << PD1_BITS)                     // Pointer to first page table 0xFFC

#define V1TOPDIRP(v)    ((u32_t *)(PG1_PDIRADDR | (((u32_t)(v)) >> 20 & ~3)))        // Pointer to page directory entry 0xFFFFF000 | 0xFFFC = 0xFFFFFFFC
#define V1TOPTEP(v)     ((u32_t *)(PG1_PTEADDR  | (((u32_t)(v)) >> 10 & ~3)))        // Pointer to page table entry
#define V1TOPTP(v)      ((u32_t *)(PG1_PTEADDR  | (((u32_t)(v)) >> 10 & 0x3FF000)))  // Pointer to start of page table

// PAE enabled
#define PXE2_BITS		 3				// 3 bits of addr for each tbl entry
#define PD2_BITS		21				// 21 bits in page directory

#define PG2_PDIRADDR    0xffffc000  // Pointer to start of page directory
#define PG2_PTEADDR     0xff800000  // Pointer to first page table

#define V2TOPDIRP(v)    ((u64_t *)(PG2_PDIRADDR | (((u32_t)(v)) >> 18 & ~7)))       // Pointer to page directory entry
#define V2TOPTEP(v)     ((u64_t *)(PG2_PTEADDR  | (((u32_t)(v)) >> 9 & ~7)))        // Pointer to page table entry
#define V2TOPTP(v)      ((u64_t *)(PG2_PTEADDR  | (((u32_t)(v)) >> 9 & 0x7FF000)))  // Pointer to start of page table

// macros common PAE
#define PXE_ADD(p, o)    ((pxe_t *)((word_t)(p) + (o)))
#define	PXE_GET(p)	(pae_enabled ? (p)->pxe64 : (p)->pxe32)
#define PXE_SET(p, v)	(pae_enabled ? ((p)->pxe64 = (v)) : ((p)->pxe32 = (v)))

#define GENERIC_VTOPDIRP(r, v)   PXE_ADD(r, ((v) >> pd_bits) << pxe_bits)
#define VTOPDIRP(v)             (pae_enabled ? (pxe_t *)V2TOPDIRP(v) : (pxe_t *)V1TOPDIRP(v))
#define VTOPTEP(v)		(pae_enabled ? (pxe_t *)V2TOPTEP(v)  : (pxe_t *)V1TOPTEP(v))
#define VTOPTP(v)		(pae_enabled ? (pxe_t *)V2TOPTP(v)   : (pxe_t *)V1TOPTP(v))

// начало адресного пространства ядра
#define KERNEL_SYSADDR_BASE     0xc0000000u
#define KERNEL_MAP_BASE         KERNEL_SYSADDR_BASE
#define KERNEL_MAP_SIZE         0x10000000U
#define KERNEL_L2MAP_BASE	(KERNEL_MAP_BASE + KERNEL_MAP_SIZE)     // temp mappings to zero new L2 pagetables 
#define PROCMEM_BASE            (KERNEL_L2MAP_BASE + (4 * 1024 * 1024)) // normal kernel mapping


// user address space
#define CPU_SYSTEM_PADDR_START	0
#define CPU_SYSTEM_PADDR_END	((256 * 1024 * 1024) - 1)

// virtual address regions for user programs
#define USER_VADDR_START	0x00000000u
#define USER_VADDR_END          0xbfffffffu
#define USER_SO_VADDR_START 	0xb8200000u
#define USER_SHMEM_VADDR_START	0x40100000u // shared objects

#define HW_PGSHIFTS         { 12, 22, 32 }
#define HW_VALID_PGSIZES    ((1 << 12) | (1 << 22))

#define X86_PGSIZES         {  size_4k = 0, size_4m = 1, size_4g = 2, size_sync = size_4m, size_superpage = size_4m, size_max = size_4m }

typedef enum x86_pagesize {
    size_4k = 0,
    size_4m = 1
} x86_pagesize_e;

typedef struct x86_pgent {
    union {
	struct {
	    unsigned present		:1;
	    unsigned rw			:1;
	    unsigned privilege		:1;
	    unsigned write_through	:1;

	    unsigned cache_disabled	:1;
	    unsigned accessed		:1;
	    unsigned dirty		:1;
	    unsigned size		:1;

	    unsigned global		:1;
	    unsigned cpulocal		:1;
	    unsigned avail		:2;

	    unsigned base		:20;
	} pg;

	struct {
	    unsigned present		:1;
	    unsigned rw			:1;
	    unsigned privilege		:1;
	    unsigned write_through	:1;

	    unsigned cache_disabled	:1;
	    unsigned accessed		:1;
	    unsigned dirty		:1;
	    unsigned size		:1;

	    unsigned global		:1;
	    unsigned cpulocal		:1;
	    unsigned avail		:2;

	    unsigned pat		:1;
	    unsigned reserved		:9;
	    unsigned base		:10;
	} pg4m;

	u32_t raw;
    };
} x86_pgent_t;

int x86_pgent_is_valid(x86_pgent_t *p) 
{
    return p->pg.present == 1;
}

int x86_pgent_is_writable(x86_pgent_t *p) 
{
    return p->pg.rw == 1;
}

int x86_pgent_is_executable(x86_pgent_t *p) 
{
    return (p->pg.present == 1);
}

int x86_pgent_is_accessed(x86_pgent_t *p) 
{
    return (p->pg.accessed == 1);
}

int x86_pgent_is_dirty(x86_pgent_t *p) 
{
    return (p->pg.dirty == 1);
}

int x86_pgent_is_superpage(x86_pgent_t *p) 
{
    return (p->pg.size == 1);
}

int x86_pgent_is_kernel(x86_pgent_t *p) 
{
    return (p->pg.privilege == 0);
}

int x86_pgent_is_write_through(x86_pgent_t *p) 
{
    return (p->pg.write_through == 1);
}

int x86_pgent_is_cache_disabled(x86_pgent_t *p) 
{
    return (p->pg.cache_disabled == 1);
}

int x86_pgent_is_pat(x86_pgent_t *p, enum x86_pagesize_e size) 
{
    #if defined(CONFIG_X86_PAT)
	return (size == size_4k ? p->pg.size : p->pg4m.pat); 
    #else
        return 0;
    #endif
}

int x86_pgent_is_global(x86_pgent_t *p) 
{
    return (p->pg.global == 1);
}

int x86_pgent_is_cpulocal(x86_pgent_t *p) 
{
    return (p->pg.cpulocal == 1);
}

addr_t x86_pgent_get_address(x86_pgent_t *p, x86_pagesize_e size)
{
    return (addr_t) (p->raw & (size == size_4k ? X86_PAGE_MASK : X86_SUPERPAGE_MASK));
}

x86_pgent_t* x86_pgent_get_ptab(x86_pgent_t *p)
{
    return (x86_pgent_t* )(p->raw & X86_PAGE_MASK);
}

u32_t x86_pgent_get_raw(x86_pgent_t *p)
{
    return p->raw;
}

void x86_pgent_clear(x86_pgent_t *p)
{
    p->raw = 0;
}

void x86_pgent_set_entry(x86_pgent_t *p, addr_t addr, x86_pagesize_e size, u32_t attrib)
{ 
    if (size == size_4k)
        p->raw = ((u32_t)(addr) & X86_PAGE_MASK) | (attrib & X86_PAGE_FLAGS_MASK);
    else
        p->raw = ((u32_t)(addr) & X86_SUPERPAGE_MASK) | X86_PAGE_SUPER | (attrib & X86_SUPERPAGE_FLAGS_MASK);
}

void x86_pgent_set_ptab_entry(x86_pgent_t *p, addr_t addr, u32_t attrib)
{
    p->raw = ((u32_t)(addr) & X86_PAGE_MASK) | X86_PAGE_VALID | (attrib & X86_X32_PTAB_FLAGS_MASK);
}

void x86_pgent_set_cacheability(x86_pgent_t *p, int cacheable, x86_pagesize_e size)
{
    p->pg.cache_disabled = !cacheable;
    #if defined(CONFIG_X86_PAT)
        if (size == size_4k) 
            p->pg.size = 0;
        else
            p->pg4m.pat = 0;
    #endif
}

void x86_pgent_set_pat(x86_pgent_t *p, word_t pat, x86_pagesize_e size)
{
    p->pg.write_through  = (pat & 1) ? 1 : 0;
    p->pg.cache_disabled = (pat & 2) ? 1 : 0;
    #if defined(CONFIG_X86_PAT)
        if (size == size_4k)
            p->pg.size  = (pat & 4) ? 1 : 0;
        else
            p->pg4m.pat = (pat & 4) ? 1 : 0;
    #endif
}

void x86_pgent_set_global(x86_pgent_t *p, int global)
{
    p->pg.global = global;
}


void x86_pgent_set_cpulocal(x86_pgent_t *p, int local)
{
    p->pg.cpulocal = local;
}

void x86_pgent_set_accessed(x86_pgent_t *p, int accessed)
{
    p->pg.accessed = accessed;
}

void x86_pgent_set_dirty(x86_pgent_t *p, int dirty)
{
    p->pg.dirty = dirty;
}
#endif /* KERNEL_ARCH_X86_32_PTAB_H */