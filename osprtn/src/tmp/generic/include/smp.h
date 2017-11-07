#ifndef GENERIC_SMP_H
#define GENERIC_SMP_H
/*
 * поддержка SMP
 * определяем к какому CPU обращаться 
 */

#ifdef CONFIG_SMP
#else
// единственный CPU
#define raw_smp_processor_id()  0


#endif /* CONFIG_SMP */

// возвращает текущий CPU ID
#define smp_processor_id() raw_smp_processor_id()

#endif /* GENERIC_SMP_H */