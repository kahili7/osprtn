#ifndef ARCH_X86_PAGE_DEFS_H
#define ARCH_X86_PAGE_DEFS_H

// определение размера страницы
#define PAGE_SHIFT  12
#define PAGE_SIZE   (1UL << PAGE_SHIFT)
#define PAGE_MASK   (~(PAGE_SIZE-1))

// смещение страницы
#define PAGE_OFFSET ((unsigned long)__PAGE_OFFSET)

#endif /* ARCH_X86_PAGE_DEFS_H */