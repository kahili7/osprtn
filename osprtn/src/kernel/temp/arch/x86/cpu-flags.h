#ifndef KERNEL_ARCH_X86_CPU_FLAGS_H
#define KERNEL_ARCH_X86_CPU_FLAGS_H

// EFLAGS bits
#define X86_EFLAGS_CF_BIT       0 /* флаг переноса */
#define X86_EFLAGS_CF           _ONEBIT32(X86_EFLAGS_CF_BIT)
#define X86_EFLAGS_FIXED_BIT	1 /* зарезервировано */
#define X86_EFLAGS_FIXED        _ONEBIT32(X86_EFLAGS_FIXED_BIT)
#define X86_EFLAGS_PF_BIT	2 /* флаг четности */
#define X86_EFLAGS_PF		_ONEBIT32(X86_EFLAGS_PF_BIT)
#define X86_EFLAGS_AF_BIT	4 /* вспомогательный флаг переноса */
#define X86_EFLAGS_AF		_ONEBIT32(X86_EFLAGS_AF_BIT)
#define X86_EFLAGS_ZF_BIT	6 /* флаг нуля */
#define X86_EFLAGS_ZF		_ONEBIT32(X86_EFLAGS_ZF_BIT)
#define X86_EFLAGS_SF_BIT	7 /* флаг знака */
#define X86_EFLAGS_SF		_ONEBIT32(X86_EFLAGS_SF_BIT)
#define X86_EFLAGS_TF_BIT	8 /* флаг трассировки */
#define X86_EFLAGS_TF		_ONEBIT32(X86_EFLAGS_TF_BIT)
#define X86_EFLAGS_IF_BIT	9 /* флаг разрешение прерывания */
#define X86_EFLAGS_IF		_ONEBIT32(X86_EFLAGS_IF_BIT)
#define X86_EFLAGS_DF_BIT	10 /* флаг направления */
#define X86_EFLAGS_DF		_ONEBIT32(X86_EFLAGS_DF_BIT)
#define X86_EFLAGS_OF_BIT	11 /* флаг переполнения */
#define X86_EFLAGS_OF		_ONEBIT32(X86_EFLAGS_OF_BIT)
#define X86_EFLAGS_IOPL_BIT	12 /* уровень приоритета ввода-вывода */
#define X86_EFLAGS_IOPL		(3UL << X86_EFLAGS_IOPL_BIT)
#define X86_EFLAGS_NT_BIT	14 /* флаг вложенности задач */
#define X86_EFLAGS_NT		_ONEBIT32(X86_EFLAGS_NT_BIT)
#define X86_EFLAGS_RF_BIT	16 /* флаг возобновления */
#define X86_EFLAGS_RF		_ONEBIT32(X86_EFLAGS_RF_BIT)
#define X86_EFLAGS_VM_BIT	17 /* режим виртуального процессора 8086 */
#define X86_EFLAGS_VM		_ONEBIT32(X86_EFLAGS_VM_BIT)
#define X86_EFLAGS_AC_BIT	18 /* проверка выравнивания */
#define X86_EFLAGS_AC		_ONEBIT32(X86_EFLAGS_AC_BIT)
#define X86_EFLAGS_VIF_BIT	19 /* виртуальный флаг разрешения прерывания */
#define X86_EFLAGS_VIF		_ONEBIT32(X86_EFLAGS_VIF_BIT)
#define X86_EFLAGS_VIP_BIT	20 /* ожидающее виртуальное прерывание */
#define X86_EFLAGS_VIP		_ONEBIT32(X86_EFLAGS_VIP_BIT)
#define X86_EFLAGS_ID_BIT	21 /* проверка на доступность инструкции CPUID */
#define X86_EFLAGS_ID		_ONEBIT32(X86_EFLAGS_ID_BIT) 

// управляющий регистр CR0
#define X86_CR0_PE_BIT		0 /* разрешение защиты */
#define X86_CR0_PE		_ONEBIT32(X86_CR0_PE_BIT)
#define X86_CR0_MP_BIT		1 /* контроль сопроцессора */
#define X86_CR0_MP		_ONEBIT32(X86_CR0_MP_BIT)
#define X86_CR0_EM_BIT		2 /* эмуляция сопроцессора */
#define X86_CR0_EM		_ONEBIT32(X86_CR0_EM_BIT)
#define X86_CR0_TS_BIT		3 /* переключение задачи */
#define X86_CR0_TS		_ONEBIT32(X86_CR0_TS_BIT)
#define X86_CR0_ET_BIT		4 /* тип расширения */
#define X86_CR0_ET		_ONEBIT32(X86_CR0_ET_BIT)
#define X86_CR0_NE_BIT		5 /* ошибка сопроцессора */
#define X86_CR0_NE		_ONEBIT32(X86_CR0_NE_BIT)
#define X86_CR0_WP_BIT		16 /* защита от записи */
#define X86_CR0_WP		_ONEBIT32(X86_CR0_WP_BIT)
#define X86_CR0_AM_BIT		18 /* маска выравнивания */
#define X86_CR0_AM		_ONEBIT32(X86_CR0_AM_BIT)
#define X86_CR0_NW_BIT		29 /* запрет сквозной записи */
#define X86_CR0_NW		_ONEBIT32(X86_CR0_NW_BIT)
#define X86_CR0_CD_BIT		30 /* запрет кэширования */
#define X86_CR0_CD		_ONEBIT32(X86_CR0_CD_BIT)
#define X86_CR0_PG_BIT		31 /* страничный режим */
#define X86_CR0_PG		_ONEBIT32(X86_CR0_PG_BIT)

// управляющий регистр CR3
#define X86_CR3_PWT_BIT		3 /* прозрачная запись в таблицы страниц */
#define X86_CR3_PWT		_ONEBIT32(X86_CR3_PWT_BIT)
#define X86_CR3_PCD_BIT		4 /* запрет кэша уровня страниц */
#define X86_CR3_PCD		_ONEBIT32(X86_CR3_PCD_BIT)
#define X86_CR3_PCID_MASK	0x00000fffUL /* PCID Mask */

// управляющий регистр CR4 Pentium
#define X86_CR4_VME_BIT		0 /* расширения режима виртуального процессора 8086 */
#define X86_CR4_VME		_ONEBIT32(X86_CR4_VME_BIT)
#define X86_CR4_PVI_BIT		1 /* виртуальные прерывания защищённого режима */
#define X86_CR4_PVI		_ONEBIT32(X86_CR4_PVI_BIT)
#define X86_CR4_TSD_BIT		2 /* запрет отметки времени */
#define X86_CR4_TSD		_ONEBIT32(X86_CR4_TSD_BIT)
#define X86_CR4_DE_BIT		3 /* отладочные расширения */
#define X86_CR4_DE		_ONEBIT32(X86_CR4_DE_BIT)
#define X86_CR4_PSE_BIT		4 /* расширение размера страниц */
#define X86_CR4_PSE		_ONEBIT32(X86_CR4_PSE_BIT)
#define X86_CR4_PAE_BIT		5 /* расширение физических адресов */
#define X86_CR4_PAE		_ONEBIT32(X86_CR4_PAE_BIT)
#define X86_CR4_MCE_BIT		6 /* разрешение машинного контроля */
#define X86_CR4_MCE		_ONEBIT32(X86_CR4_MCE_BIT)
#define X86_CR4_PGE_BIT		7 /* разрешение глобальных страниц */
#define X86_CR4_PGE		_ONEBIT32(X86_CR4_PGE_BIT)
#define X86_CR4_PCE_BIT		8 /* разрешение счётчика мониторинга производительности */
#define X86_CR4_PCE		_ONEBIT32(X86_CR4_PCE_BIT)
#define X86_CR4_OSFXSR_BIT	9 /* поддержка инструкций FXSAVE и FXRSTOR */
#define X86_CR4_OSFXSR		_ONEBIT32(X86_CR4_OSFXSR_BIT)
#define X86_CR4_OSXMMEXCPT_BIT	10 /* поддержка незамаскированных исключений вещественной арифметики SIMD */
#define X86_CR4_OSXMMEXCPT	_ONEBIT32(X86_CR4_OSXMMEXCPT_BIT)
#define X86_CR4_VMXE_BIT	13 /* разрешение виртуализации */
#define X86_CR4_VMXE		_ONEBIT32(X86_CR4_VMXE_BIT)
#define X86_CR4_SMXE_BIT	14 /* разрешение средств повышения безопасности */
#define X86_CR4_SMXE		_ONEBIT32(X86_CR4_SMXE_BIT)
#define X86_CR4_FSGSBASE_BIT	16 /* разрешение RDWRFSGS поддержки */
#define X86_CR4_FSGSBASE	_ONEBIT32(X86_CR4_FSGSBASE_BIT)
#define X86_CR4_PCIDE_BIT	17 /* разрешение PCID поддержки */
#define X86_CR4_PCIDE		_ONEBIT32(X86_CR4_PCIDE_BIT)
#define X86_CR4_OSXSAVE_BIT	18 /* разрешение xsave и xrestore */
#define X86_CR4_OSXSAVE		_ONEBIT32(X86_CR4_OSXSAVE_BIT)
#define X86_CR4_SMEP_BIT	20 /* разрешение SMEP поддержки */
#define X86_CR4_SMEP		_ONEBIT32(X86_CR4_SMEP_BIT)
#define X86_CR4_SMAP_BIT	21 /* разрешение SMAP поддержки */
#define X86_CR4_SMAP		_ONEBIT32(X86_CR4_SMAP_BIT) 

// управляющий регистр CR8
#define X86_CR8_TPR		0x0000000fUL /* уровень приоритета задачи */

// флаги сегментного дескриптора
#define X86_ACCESSED                0x01 //бит доступа
#define X86_READABLE_CODE           0x02 //бит доступа для чтения дескриптора сегмента кода
#define X86_WRITEABLE_DATA          0x02 //бит доступа для записи дескриптора сегмента данных
#define X86_CONFORMING_CODE         0x04 //бит конформным дескриптора сегмента кода
#define X86_EXPANDABLE_DOWN_DATA    0x04 //бит направление роста дескриптора сегмента данных
#define X86_EXECUTABLE		    0x08	/* Determines meaning of prev 2 bits */
#define X86_SEG_DESCRIPTOR          0x10 //бит указывает, является ли дескриптор системным

// привилегии дескриптора
#define X86_DPL0    0x00
#define X86_DPL1    0x20
#define X86_DPL2    0x40
#define X86_DPL3    0x60

#define X86_PRESENT 0x80 //бит признака присутствия сегмента в памяти

#define X86_A_BIT   0x10 //бит неиспользуемый бит
#define X86_B_BIT   0x40 //бит указывающий разрядность сегмента
#define X86_D_BIT   0x40
#define X86_G_BIT   0x80 //бит гранулярности

// запрошенный уровень привилегий
#define X86_RPL0    0x00
#define X86_RPL1    0x01
#define X86_RPL2    0x02
#define X86_RPL3    0x03

// использование GDT & LDT
#define X86_USE_LDT 0x04

// биты каталога страниц
#define X86_PDE_PRESENT     0x00000001  //бит признака присутствия сегмента в памяти
#define X86_PDE_WRITE       0x00000002  //бит записи/чтения
#define X86_PDE_USER        0x00000004  //бит user/supervisor
#define X86_PDE_WT          0x00000008  //сквозная запись
#define X86_PDE_CD          0x00000010  //отключенный кэш
#define X86_PDE_ACCESSED    0x00000020  //бит обращения к странице 
#define X86_PDE_PS          0x00000080  //размер страницы
#define X86_PDE_GLOBAL      0x00000100  //глобальная

#define X86_PDE_USER1       0x00000200  //зарезервировано
#define X86_PDE_USER2       0x00000400  //зарезервировано
#define X86_PDE_USER3       0x00000800  //зарезервировано

#define X86_PDE_NX          ((u64_t)0x80000000 << 32)
#define X86_4M_PAGESIZE     0x00400000

// биты таблицы страниц
#define X86_PTE_PRESENT     0x00000001  //бит признака присутствия сегмента в памяти
#define X86_PTE_WRITE       0x00000002  //бит записи/чтения
#define X86_PTE_USER        0x00000004  //бит user/supervisor
#define X86_PTE_WT          0x00000008  //сквозная запись
#define X86_PTE_CD          0x00000010  //отключенный кэш
#define X86_PTE_ACCESSED    0x00000020  //бит обращения к странице 
#define X86_PTE_DIRTY       0x00000040  //грязная страница
#define X86_PTE_PAT         0x00000080
#define X86_PTE_GLOBAL      0x00000100  //глобальная

#define X86_PTE_USER1       0x00000200  //зарезервировано
#define X86_PTE_USER2       0x00000400  //зарезервировано
#define X86_PTE_USER3       0x00000800  //зарезервировано

#define X86_PTE_NX          ((u64_t)0x80000000 << 32)


#ifdef CONFIG_VM86
#define X86_VM_MASK X86_EFLAGS_VM
#else
#define X86_VM_MASK 0   // VM86 не поддерживается
#endif 
#endif /* KERNEL_ARCH_X86_CPU_FLAGS_H */