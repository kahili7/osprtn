#include MM_DIR(mm_internal.h)


#define TOP_VADDR   0xFF000000U     // 3GB

// найти системный виртуальный адрес
uintptr_t cpu_sysvaddr_find(uintptr_t start, unsigned size)
{
    unsigned    found_va;
    unsigned	found_va_size;
    int		is_free;    // страница свободна
    unsigned	flags;      // флаги дескриптора
    unsigned	pg_size;    // размер страницы
    
    found_va = VA_INVALID;
    found_va_size = 0;
    
    if((start == 0) || (start >= TOP_VADDR))
    {
        start = PROCMEM_BASE;
    }
    
    uintptr_t	rover;
    uintptr_t	next;
    pxe_t       *pde;
    
    rover = start;
    
    for(;;)
    {
        is_free = 1;
        pg_size = 1 << pd_bits; // большая страница или свободная
        pde = VTOPDIRP(rover);
        flags = PXE_GET_FLAGS(pde);
        
        next = (rover + pg_size) & ~(pg_size - 1);
    }
}