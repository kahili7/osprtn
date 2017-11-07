#ifndef KERNEL_ARCH_X86_X86_H
#define KERNEL_ARCH_X86_X86_H

#include DIR_CPU(x86.h)

// определение размера страницы
#define X86_PAGE_SHIFT  12
#define X86_PAGE_SIZE   (__UL(1) << X86_PAGE_SHIFT)
#define X86_PAGE_MASK   (~(X86_PAGE_SIZE-1))

#define X86_PAGE_VALID		(1<<0)
#define X86_PAGE_WRITABLE	(1<<1)
#define X86_PAGE_USER		(1<<2)
#define X86_PAGE_KERNEL		(0<<2)
#define X86_PAGE_WRITE_THROUGH	(1<<3)
#define X86_PAGE_CACHE_DISABLE	(1<<4)
#define X86_PAGE_ACCESSED	(1<<5)
#define X86_PAGE_DIRTY		(1<<6)
#define X86_PAGE_PAT		(1<<7)
#define X86_PAGE_SUPER		(1<<7)
#define X86_PAGE_GLOBAL		(1<<8)

// таблица аттрибутов страницы
#define X86_SUPERPAGE_PAT  	(1<<12)

/* pagefault */
#define X86_PFAULT_RW	(1 << 1)	// бит чтения/записи
#define X86_PFAULT_US	(1 << 2)	// бит уровня привилегий
#define X86_PFAULT_ID	(1 << 4)	// бит запрещения кэширования

// EFLAGS биты
#define X86_EFLAGS_CF       (__UL(1) <<  0)       /* флаг переноса */
#define X86_EFLAGS_PF       (__UL(1) <<  2)       /* флаг четности */
#define X86_EFLAGS_AF       (__UL(1) <<  4)       /* вспомогательный флаг переноса */
#define X86_EFLAGS_ZF       (__UL(1) <<  6)       /* флаг нуля */
#define X86_EFLAGS_SF       (__UL(1) <<  7)       /* флаг знака */
#define X86_EFLAGS_TF       (__UL(1) <<  8)       /* флаг трассировки */
#define X86_EFLAGS_IF       (__UL(1) <<  9)       /* флаг разрешение прерывания */
#define X86_EFLAGS_DF       (__UL(1) << 10)       /* флаг направления */
#define X86_EFLAGS_OF       (__UL(1) << 11)       /* флаг переполнения */
#define X86_EFLAGS_NT       (__UL(1) << 14)       /* флаг вложенности задач */
#define X86_EFLAGS_RF       (__UL(1) << 16)       /* флаг возобновления */
#define X86_EFLAGS_VM       (__UL(1) << 17)       /* режим виртуального процессора 8086 */
#define X86_EFLAGS_AC       (__UL(1) << 18)       /* проверка выравнивания */
#define X86_EFLAGS_VIF      (__UL(1) << 19)       /* виртуальный флаг разрешения прерывания */
#define X86_EFLAGS_VIP      (__UL(1) << 20)       /* ожидающее виртуальное прерывание */
#define X86_EFLAGS_ID       (__UL(1) << 21)       /* проверка на доступность инструкции CPUID */
#define X86_EFLAGS_IOPL(x)  ((x & 3) << 12)       /* уровень приоритета ввода-вывода */

// контрольные биты регистров(CR0, CR3, CR4)
#define X86_CR0_PE 	(__UL(1) <<  0)   /* вкл. защищенный режим */
#define X86_CR0_MP 	(__UL(1) <<  1)   /* монитор сопроцессора */
#define X86_CR0_EM 	(__UL(1) <<  2)   /* выключить fpu */
#define X86_CR0_TS 	(__UL(1) <<  3)   /* переключение задачи*/
#define X86_CR0_ET 	(__UL(1) <<  4)   /* тип расширения (всегда 1) */
#define X86_CR0_NE 	(__UL(1) <<  5)   /* цифровой режим отчетов об ошибках */
#define X86_CR0_WP 	(__UL(1) << 16)   /* страницы защищенные от записи из режима супервизора */
#define X86_CR0_AM	(__UL(1) << 3)	  /* маска для выравнивания */
#define X86_CR0_NW 	(__UL(1) << 29)   /* нет сквозной записи */
#define X86_CR0_CD 	(__UL(1) << 30)   /* кэш отключен */
#define X86_CR0_PG 	(__UL(1) << 31)   /* вкл. страничной адресации */

#define X86_CR3_PCD    	(__UL(1) <<  3)   /* страница-уровня кэш отключить */
#define X86_CR3_PWT    	(__UL(1) <<  4)   /* уровне страницы пишет прозрачно */

#define X86_CR4_VME    	(__UL(1) <<  0)   /* virtual 8086 mode extension  */
#define X86_CR4_PVI    	(__UL(1) <<  1)   /* расширение виртуального режима 8086 */
#define X86_CR4_TSD    	(__UL(1) <<  2)   /* штамп времени отключения */
#define X86_CR4_DE     	(__UL(1) <<  3)   /* расширения отладки */
#define X86_CR4_PSE    	(__UL(1) <<  4)   /* расширение размера страницы (4MB) */
#define X86_CR4_PAE    	(__UL(1) <<  5)   /* расширения физических адресов */
#define X86_CR4_MCE    	(__UL(1) <<  6)   /* проверяем расширения машина */
#define X86_CR4_PGE    	(__UL(1) <<  7)   /* включение глобального страниц */
#define X86_CR4_PCE    	(__UL(1) <<  8)   /* разрешить пользователю использовать rdpmc */
#define X86_CR4_OSFXSR 	(__UL(1) <<  9)   /* вкл. fxsave/fxrstor + sse  */
#define X86_CR4_OSXMMEXCPT (__UL(1) << 10) /* поддержка unmsk. SIMD exc. */
#define X86_CR4_VMXE   	(__UL(1) << 13)	  /* расширение vmx */



#endif /* KERNEL_ARCH_X86_X86_H */