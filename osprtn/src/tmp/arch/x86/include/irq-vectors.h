#ifndef ARCH_X86_IRQ_VECTORS_H
#define ARCH_X86_IRQ_VECTORS_H
/*
 * список векторов прерываний
 * 0 - 31 - аппаратные вектора прерываний
 * 32 - 127 - пользовательские вектора прерываний
 */

#define NMI_VECTOR      0x02    // немаскируемое прерывание

// первый пользовательский вектор
#define FIRST_EXTERNAL_VECTOR   0x20

#define IRQ0_VECTOR         ((FIRST_EXTERNAL_VECTOR + 16) & ~15)
#define IRQ1_VECTOR         (IRQ0_VECTOR + 1)
#define IRQ2_VECTOR         (IRQ0_VECTOR + 2)
#define IRQ3_VECTOR         (IRQ0_VECTOR + 3)
#define IRQ4_VECTOR         (IRQ0_VECTOR + 4)
#define IRQ5_VECTOR         (IRQ0_VECTOR + 5)
#define IRQ6_VECTOR         (IRQ0_VECTOR + 6)
#define IRQ7_VECTOR         (IRQ0_VECTOR + 7)
#define IRQ8_VECTOR         (IRQ0_VECTOR + 8)
#define IRQ9_VECTOR         (IRQ0_VECTOR + 9)
#define IRQ10_VECTOR        (IRQ0_VECTOR + 10)
#define IRQ11_VECTOR        (IRQ0_VECTOR + 11)
#define IRQ12_VECTOR        (IRQ0_VECTOR + 12)
#define IRQ13_VECTOR        (IRQ0_VECTOR + 13)
#define IRQ14_VECTOR        (IRQ0_VECTOR + 14)
#define IRQ15_VECTOR        (IRQ0_VECTOR + 15) 
#endif /* ARCH_X86_IRQ_VECTORS_H */