#ifndef KERNEL_ARCH_X86_MMU_H
#define KERNEL_ARCH_X86_MMU_H

#include DIR_ARCH(cpu.h)

// очистка TLB
INLINE void x86_mmu_flush_tlb(bool global)
{
    word_t dummy1;
    
#if defined(CONFIG_X86_PGE)
    if (!global)
    {
        __asm__ __volatile__("mov %%cr3, %0\n\t"
                             "mov %0, %%cr3\n\t": "=r"(dummy1));
    }
    else
    {
        word_t dummy2;
        
        __asm__ __volatile__("mov %%cr4, %0\n"
                             "and %2, %0\n"
                             "mov %0, %%cr4\n"
                             "mov %%cr3, %1\n"
                             "mov %1, %%cr3\n"
                             "or  %3, %0\n"
                             "mov %0, %%cr4\n" : "=r"(dummy1), "=r"(dummy2) : "i" (~X86_CR4_PGE), "i" (X86_CR4_PGE));
    }
#else
    __asm__ __volatile__("mov %%cr3, %0\n\t"
                         "mov %0, %%cr3\n\t" : "=r"(dummy1));
#endif
}

// аннулировать элемент TLB
INLINE void x86_mmu_flush_tlbent(word_t addr)
{
    __asm__ __volatile__ ("invlpg (%0)\n" : :"r"(addr));
}

// вкл. страничного режима
INLINE void x86_mmu_enable_paging()
{
    x86_cr0_set(X86_CR0_PG | X86_CR0_WP | X86_CR0_PE);
    __asm__ __volatile__ ("jmp penabled; penabled:");
}

// выкл. страничного режима
INLINE void x86_mmu_disable_paging()
{
    x86_cr0_mask(X86_CR0_PG);
}

// возможность расширения физических адресов
// необходимое для длительного и режим совместимости
INLINE void x86_mmu_enable_pae_mode()
{
    x86_cr4_set(X86_CR4_PAE);
}

#if defined(CONFIG_IS_64BIT)
#endif /* defined(CONFIG_IS_64BIT) */

// включение глобального страниц
INLINE void x86_mmu_enable_global_pages()
{
      x86_cr4_set(X86_CR4_PGE);
}

// вкл. расширение размера страницы (4MB)
INLINE void x86_mmu_enable_super_pages(void)
{
    x86_cr4_set(X86_CR4_PSE);
}

// получить активную карту страницы
INLINE word_t x86_mmu_get_active_pagetable(void)
{
    word_t pgm;
    
    __asm__ __volatile__ ("mov %%cr3, %0\n" : "=a"(pgm));
    
    return pgm;
}

// установить активную карту страницы
INLINE void x86_mmu_set_active_pagetable(word_t root)
{
   __asm__ __volatile__ ("mov %0, %%cr3 n" : : "r"(root));
}

// получить адрес, вызвавшей страничное нарушение
INLINE word_t x86_mmu_get_pagefault_address(void)
{
    register word_t tmp;

    __asm__ ("mov %%cr2, %0\n" : "=r"(tmp));
    
    return tmp;
}
#endif /* KERNEL_ARCH_X86_MMU_H */