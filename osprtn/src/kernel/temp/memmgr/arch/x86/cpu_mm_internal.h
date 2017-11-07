#ifndef KERNEL_MEMMGR_ARCH_X86_CPU_MM_INTERNAL_H
#define KERNEL_MEMMGR_ARCH_X86_CPU_MM_INTERNAL_H

extern int          pae_enabled;    // is PAE turn on
extern unsigned     pd_bits;        // page directory bits
extern unsigned     pxe_bits;       // page directory pointer bits
extern uintptr_t    pde_map;        //

// size page table (directory)
// used for both PDE & PTE
typedef union x86_pxe {
    u32_t   pxe32;
    u64_t   pxe64;
} pxe_t;

// PAE disabled
#define PXE1_BITS       2       // 2 bits of addr for each tbl entry
#define PD1_BITS        22      // 22 bits in page directory

#define PG1_REMAP       1023
#define PG1_PDIRADDR    (PG1_REMAP << PD1_BITS | PG1_REMAP << 12)   // Pointer to start of page directory 0xFFC00000 | 0x003FF000 = 0xFFFFF000
#define PG1_PTEADDR 	(PG1_REMAP << PD1_BITS)                     // Pointer to first page table 0xFFC

#define V1TOPDIRP(v)    ((u32_t *)(PG1_PDIRADDR | (((u32_t)(v)) >> 20 & ~3)))        // Pointer to page directory entry 0xFFFFF000 | 0xFFFC = 0xFFFFFFFC
#define V1TOPTEP(v)     ((u32_t *)(PG1_PTEADDR  | (((u32_t)(v)) >> 10 & ~3)))        // Pointer to page table entry
#define V1TOPTP(v)      ((u32_t *)(PG1_PTEADDR  | (((u32_t)(v)) >> 10 & 0x3FF000)))  // Pointer to start of page table

// PAE enabled
#define PXE2_BITS       3				// 3 bits of addr for each tbl entry
#define PD2_BITS        21				// 21 bits in page directory

#define PG2_PDIRADDR    0xffffc000  // Pointer to start of page directory
#define PG2_PTEADDR     0xff800000  // Pointer to first page table

#define V2TOPDIRP(v)    ((u64_t *)(PG2_PDIRADDR | (((u32_t)(v)) >> 18 & ~7)))       // Pointer to page directory entry
#define V2TOPTEP(v)     ((u64_t *)(PG2_PTEADDR  | (((u32_t)(v)) >> 9 & ~7)))        // Pointer to page table entry
#define V2TOPTP(v)      ((u64_t *)(PG2_PTEADDR  | (((u32_t)(v)) >> 9 & 0x7FF000)))  // Pointer to start of page table

// macros common PAE
#define PXE_ADD(p, o)   ((pxe_t *)((uintptr_t)(p) + (o)))
#define	PXE_GET(p)	(pae_enabled ? (p)->pxe64 : (p)->pxe32)
#define PXE_SET(p, v)	(pae_enabled ? ((p)->pxe64 = (v)) : ((p)->pxe32 = (v)))
#define PXE_GET_FLAGS(p)        ((p)->pxe32)
#define PXE_SET_FLAGS(p, m, s)  ((p)->pxe32 = ((p)->pxe32 & (m)) | (s))

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

// user phys. address space
#define CPU_SYSTEM_PADDR_START	0
#define CPU_SYSTEM_PADDR_END	((256 * 1024 * 1024) - 1)

// virtual address regions for user programs
#define USER_VADDR_START	0x00000000u
#define USER_VADDR_END          0xbfffffffu
#define USER_SO_VADDR_START 	0xb8200000u
#define USER_SHMEM_VADDR_START	0x40100000u // shared objects

// структура организации менеджера памяти процессора
struct cpu_mm_area_space {
    struct cpu_mm_area_space    *next;
    struct cpu_mm_area_space    **prev;
    union x86_pxe               *pgdir;         // директория страниц
    struct palloc_quantum       *l2_list;
    paddr32_t                   *ptroot_paddr;  // физ. адрес начала таблицы страниц
};
#endif /* KERNEL_MEMMGR_ARCH_X86_CPU_MM_INTERNAL_H */