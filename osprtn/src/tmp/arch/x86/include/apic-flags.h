#ifndef ARCH_X86_APIC_FLAGS_H
#define ARCH_X86_APIC_FLAGS_H

#define IO_APIC_DEFAULT_PHYS_BASE   0xfec00000
#define	APIC_DEFAULT_PHYS_BASE      0xfee00000      // физический адрес локального APIC

// таблица локальных векторов
#define	APIC_LVT_LID    0x20    // смещение локального APIC ID регистра
#define	APIC_LVT_LVR    0x30    // смещение локального APIC Version регистра
    #define APIC_LVR_MASK           0xFF00FF
    #define APIC_LVR_DIRECTED_EOI   (1 << 24)
    #define GET_APIC_VERSION(x)     ((x) & 0xFFu)
    #define GET_APIC_MAXLVT(x)      (((x) >> 16) & 0xFFu)

#define	APIC_LVT_TASKPRI    0x80    // смещение локального регистра приоритета задачи
    #define APIC_TASKPRI_MASK   0xFFu

#define	APIC_LVT_ARBPRI     0x90    // смещение локального регистра арбитражного приоритета
    #define APIC_ARBPRI_MASK	0xFFu

#define	APIC_LVT_PROCPRI    0xA0
#define	APIC_LVT_EOI        0xB0
    #define APIC_EOI_ACK        0x0

#define	APIC_LVT_RRR        0xC0    // смещение локального регистра Remote Read Register
#define	APIC_LVT_LDR        0xD0    // смещение локального регистра Logical Destination Register
    #define APIC_LDR_MASK		(0xFFu << 24)
    #define GET_APIC_LOGICAL_ID(x)	(((x) >> 24) & 0xFFu)
    #define SET_APIC_LOGICAL_ID(x)	(((x) << 24))
    #define APIC_ALL_CPUS		0xFFu

#define	APIC_LVT_DFR        0xE0    // смещение локального регистра Destination Format Register
    #define APIC_DFR_CLUSTER		0x0FFFFFFFul
    #define APIC_DFR_FLAT		0xFFFFFFFFul 

#define	APIC_LVT_SPIV           0xF0    // смещение локального регистра Spurious Interrupt Vector Register
    #define APIC_SPIV_DIRECTED_EOI	(1 << 12)
    #define APIC_SPIV_FOCUS_DISABLED	(1 << 9)
    #define APIC_SPIV_APIC_ENABLED	(1 << 8)

#define	APIC_LVT_ISR_31         0x100       // смещение локального регистра In-Service Register (ISR); bits 31:0
#define	APIC_LVT_ISR_63         0x110       // смещение локального регистра In-Service Register (ISR); bits 63:32
#define	APIC_LVT_ISR_95         0x120       // смещение локального регистра In-Service Register (ISR); bits 95:64
#define	APIC_LVT_ISR_127	0x130       // смещение локального регистра In-Service Register (ISR); bits 127:96
#define	APIC_LVT_ISR_159	0x140       // смещение локального регистра In-Service Register (ISR); bits 159:128
#define	APIC_LVT_ISR_191	0x150       // смещение локального регистра In-Service Register (ISR); bits 191:160
#define	APIC_LVT_ISR_223	0x160       // смещение локального регистра In-Service Register (ISR); bits 223:192
#define	APIC_LVT_ISR_255	0x170       // смещение локального регистра In-Service Register (ISR); bits 255:224

#define	APIC_LVT_TMR_31         0x180       // смещение локального регистра Trigger Mode Register (TMR); bits 31:0
#define	APIC_LVT_TMR_63         0x190       // смещение локального регистра Trigger Mode Register (TMR); bits 63:32
#define	APIC_LVT_TMR_95         0x1A0       // смещение локального регистра Trigger Mode Register (TMR); bits 95:64
#define	APIC_LVT_TMR_127	0x1B0       // смещение локального регистра Trigger Mode Register (TMR); bits 127:96
#define	APIC_LVT_TMR_159	0x1C0       // смещение локального регистра Trigger Mode Register (TMR); bits 159:128
#define	APIC_LVT_TMR_191	0x1D0       // смещение локального регистра Trigger Mode Register (TMR); bits 191:160
#define	APIC_LVT_TMR_223	0x1E0       // смещение локального регистра Trigger Mode Register (TMR); bits 223:192
#define	APIC_LVT_TMR_255	0x1F0       // смещение локального регистра Trigger Mode Register (TMR); bits 255:224

#define	APIC_LVT_IRR_31         0x200       // смещение локального регистра Interrupt Request Register (IRR); bits 31:0
#define	APIC_LVT_IRR_63         0x210       // смещение локального регистра Interrupt Request Register (IRR); bits 63:32
#define	APIC_LVT_IRR_95         0x220       // смещение локального регистра Interrupt Request Register (IRR); bits 95:64
#define	APIC_LVT_IRR_127	0x230       // смещение локального регистра Interrupt Request Register (IRR); bits 127:96
#define	APIC_LVT_IRR_159	0x240       // смещение локального регистра Interrupt Request Register (IRR); bits 159:128
#define	APIC_LVT_IRR_191	0x250       // смещение локального регистра Interrupt Request Register (IRR); bits 191:160
#define	APIC_LVT_IRR_223	0x260       // смещение локального регистра Interrupt Request Register (IRR); bits 223:192
#define	APIC_LVT_IRR_255	0x270       // смещение локального регистра Interrupt Request Register (IRR); bits 255:224

#define	APIC_LVT_ESR	0x280
    #define APIC_ESR_SEND_CS        0x00001
    #define APIC_ESR_RECV_CS        0x00002
    #define APIC_ESR_SEND_ACCEPT    0x00004
    #define APIC_ESR_RECV_ACCEPT    0x00008
    #define APIC_ESR_REDIRECT_IPI   0x00010
    #define APIC_ESR_SEND_ILLEGAL   0x00020
    #define APIC_ESR_RECV_ILLEGAL   0x00040
    #define APIC_ESR_ILLEGAL_REG_A  0x00080

#define APIC_LVT_CMCI	0x2f0   // смещение локального LVT CMCI регистра (переполнение машинной проверки)
#define	APIC_LVT_ICR	0x300   // смещение командного регистра прерывания  (0-31)
    #define APIC_ICR_DEST_LOGICAL       0x00800
    #define APIC_ICR_DEST_PHYSICAL      0x00000
    
    #define APIC_ICR_DM_FIXED		0x00000
    #define APIC_ICR_DM_FIXED_MASK	0x00700
    #define APIC_ICR_DM_LOWEST		0x00100
    #define APIC_ICR_DM_SMI		0x00200
    #define APIC_ICR_DM_REMRD		0x00300
    #define APIC_ICR_DM_NMI		0x00400
    #define APIC_ICR_DM_INIT		0x00500
    #define APIC_ICR_DM_STARTUP		0x00600
    #define APIC_ICR_DM_EXTINT		0x00700
    
    #define APIC_DEST_SELF		0x40000
    #define APIC_DEST_ALL_INCLUDE       0x80000
    #define APIC_DEST_ALL_EXCLUDE       0xC0000
#define	APIC_LVT_ICR2	0x310
    #define GET_APIC_DEST_FIELD(x)      (((x) >> 24) & 0xFF)
    #define SET_APIC_DEST_FIELD(x)	((x) << 24)

#define	APIC_LVT_TIMER	0x320   // смещение локального LVT Timer регистра
#define	APIC_LVT_THMR	0x330   // смещение локального LVT Thermal Monitor Register регистра
#define	APIC_LVT_PC	0x340   // смещение локального LVT Performance Counter Register регистра
#define	APIC_LVT_LINT0	0x350   // смещение локального LVT LINT0 Register регистра
#define	APIC_LVT_LINT1	0x360   // смещение локального LVT LINT1 Register регистра
#define	APIC_LVT_ERR	0x370   // смещение локального LVT ERROR Register регистра
    // флаги таблицы локальных векторов
    #define APIC_LVT_TIMER_MD_ONESHOT       (0 << 17)
    #define APIC_LVT_TIMER_MD_PERIODIC      (1 << 17)
    #define APIC_LVT_TIMER_MD_TSCDEADLINE   (2 << 17)

    #define APIC_LVT_MASKED                 (1 << 16)
    #define APIC_LVT_LEVEL_TRIGGER          (1 << 15)
    #define APIC_LVT_REMOTE_IRR             (1 << 14)
    #define APIC_LVT_INPUT_POLARITY         (1 << 13)
    #define APIC_LVT_SEND_PENDING           (1 << 12)

    #define GET_APIC_DELIVERY_MODE(x)       (((x) >> 8) & 0x7)
    #define SET_APIC_DELIVERY_MODE(x, y)    (((x) & ~0x700) | ((y) << 8))
    #define APIC_DM_FIXED        0x0
    #define APIC_DM_NMI          0x4
    #define APIC_DM_EXTINT       0x7

#define	APIC_LVT_TIMER_ICR      0x380   // смещение локального Initial Count Register (for Timer)
#define	APIC_LVT_TIMER_CCR	0x390   // смещение локального Current Count Register (for Timer)

#define	APIC_LVT_TIMER_DCR      0x3E0   // смещение локального Divide Configuration Register (for Timer)
    #define APIC_TIMER_DCR_DIV_TMBASE   (1 << 2)
    #define APIC_TIMER_DCR_DIV_1    0xB
    #define APIC_TIMER_DCR_DIV_2    0x0
    #define APIC_TIMER_DCR_DIV_4    0x1
    #define APIC_TIMER_DCR_DIV_8    0x2
    #define APIC_TIMER_DCR_DIV_16   0x3
    #define APIC_TIMER_DCR_DIV_32   0x8
    #define APIC_TIMER_DCR_DIV_64   0x9
    #define APIC_TIMER_DCR_DIV_128  0xA
#endif /* ARCH_X86_APIC_FLAGS_H */