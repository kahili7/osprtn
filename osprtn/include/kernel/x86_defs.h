#ifndef KERNEL_X86_DEFS_H
#define KERNEL_X86_DEFS_H

#define DIR_API(src)        <api/src>
#define DIR_ARCH(src)       <arch/__ARCH__/src>
#define DIR_CPU(src)        <arch/__ARCH__/__CPU__/src>
#define DIR_PLATFORM(src)   <platform/src>

#define SECTION(x)      __attribute__((section(x)))
#define UNIT(x)         __attribute__((section(".data." x)))

#define INLINE          extern inline

#if defined(ASSEMBLY)
    #define __UL(x)	x
#else
    #define __UL(x)     x##UL
#endif

#define CRASHCHECK(e) do{if(e) exit(-1);} while(0)

#if defined(CONFIG_BIGENDIAN)
	#define BITFIELD2(t,a,b)		t b; t a;
	#define BITFIELD3(t,a,b,c)		t c; t b; t a;
	#define BITFIELD4(t,a,b,c,d)		t d; t c; t b; t a;
	#define BITFIELD5(t,a,b,c,d,e)		t e; t d; t c; t b; t a;
	#define BITFIELD6(t,a,b,c,d,e,f)	t f; t e; t d; t c; t b; t a;
	#define BITFIELD7(t,a,b,c,d,e,f,g)	t g; t f; t e; t d; t c; t b; t a;
	#define BITFIELD8(t,a,b,c,d,e,f,g,h)	t h; t g; t f; t e; t d; t c; t b; t a;
	#define BITFIELD9(t,a,b,c,d,e,f,g,h,i)	t i; t h; t g; t f; t e; t d; t c; t b; t a;
	#define BITFIELD10(t,a,b,c,d,e,f,g,h,i,j) t j; t i; t h; t g; t f; t e; t d; t c; t b; t a;
	#define BITFIELD11(t,a,b,c,d,e,f,g,h,i,j,k) t k; t j; t i; t h; t g; t f; t e; t d; t c; t b; t a;
	#define BITFIELD12(t,a,b,c,d,e,f,g,h,i,j,k,l) t l; t k; t j; t i; t h; t g; t f; t e; t d; t c; t b; t a;
	#define BITFIELD13(t,a,b,c,d,e,f,g,h,i,j,k,l,m) t m; t l; t k; t j; t i; t h; t g; t f; t e; t d; t c; t b; t a;
	#define BITFIELD17(t,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q) t q; t p; t o; t n; t m; t l; t k; t j;t i; t h; t g; t f; t e; t d; t c; t b; t a;

	#define SHUFFLE2(a,b)			b,a
	#define SHUFFLE3(a,b,c)			c,b,a
	#define SHUFFLE4(a,b,c,d)		d,c,b,a
	#define SHUFFLE5(a,b,c,d,e)		e,d,c,b,a
	#define SHUFFLE6(a,b,c,d,e,f)		f,e,d,c,b,a
	#define SHUFFLE7(a,b,c,d,e,f,g)		g,f,e,d,c,b,a
#else
	#define BITFIELD2(t,a,b)		t a; t b;
	#define BITFIELD3(t,a,b,c)		t a; t b; t c;
	#define BITFIELD4(t,a,b,c,d)		t a; t b; t c; t d;
	#define BITFIELD5(t,a,b,c,d,e)		t a; t b; t c; t d; t e;
	#define BITFIELD6(t,a,b,c,d,e,f)	t a; t b; t c; t d; t e; t f;
	#define BITFIELD7(t,a,b,c,d,e,f,g)	t a; t b; t c; t d; t e; t f; t g;
	#define BITFIELD8(t,a,b,c,d,e,f,g,h)	t a; t b; t c; t d; t e; t f; t g; t h;
	#define BITFIELD9(t,a,b,c,d,e,f,g,h,i)	t a; t b; t c; t d; t e; t f; t g; t h; t i;
	#define BITFIELD10(t,a,b,c,d,e,f,g,h,i,j) t a; t b; t c; t d; t e; t f; t g; t h; t i; t j;
	#define BITFIELD11(t,a,b,c,d,e,f,g,h,i,j,k) t a; t b; t c; t d; t e; t f; t g; t h; t i; t j; t k;
	#define BITFIELD12(t,a,b,c,d,e,f,g,h,i,j,k,l) t a; t b; t c; t d; t e; t f; t g; t h; t i; t j; t k; t l;
	#define BITFIELD13(t,a,b,c,d,e,f,g,h,i,j,k,l,m) t a; t b; t c; t d; t e; t f; t g; t h; t i; t j; t k; t l; t m;
	#define BITFIELD17(t,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q) t a; t b; t c; t d; t e; t f; t g; t h; t i; t j; t k; t l; t m; t n; t o; t p; t q;
	
	#define SHUFFLE2(a,b)			a,b
	#define SHUFFLE3(a,b,c)			a,b,c
	#define SHUFFLE4(a,b,c,d)		a,b,c,d
	#define SHUFFLE5(a,b,c,d,e)		a,b,c,d,e
	#define SHUFFLE6(a,b,c,d,e,f)		a,b,c,d,e,f
	#define SHUFFLE7(a,b,c,d,e,f,g)		a,b,c,d,e,f,g
#endif


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

// определение размера страницы
#define X86_PAGE_SIZE       4096
#define X86_PAGE_MASK       0x00000FFF
#define X86_PAGE_SHIFT      12
#define X86_PAGE_DIR_SHIFT  22
#define X86_PDE_INDEX_MASK  0xFFC00000
#define X86_PTE_INDEX_MASK  0x003FF000

// определение PAGE биты
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

// определение PTE биты
#define X86_PTE_PRESENT         0x00000001
#define X86_PTE_WRITE           0x00000002
#define X86_PTE_USER_MODE       0x00000004
#define X86_PTE_WRITE_THROUCH   0x00000008
#define X86_PTE_CACHE_DISABLED	0x00000010
#define X86_PTE_ACCESSED	0x00000020
#define X86_PTE_DIRTY		0x00000040
#define X86_PTE_PAT		0x00000080
#define X86_PTE_GLOBAL		0x00000100
#define X86_PTE_USER1		0x00000200
#define X86_PTE_USER2		0x00000400
#define X86_PTE_USER3		0x00000800
#define X86_PTE_NX		0x8000000000000000

#endif /* KERNEL_X86_DEFS_H */