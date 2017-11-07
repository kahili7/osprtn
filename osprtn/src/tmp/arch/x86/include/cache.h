#ifndef ARCH_X86_CACHE_H
#define ARCH_X86_CACHE_H

// кэш первого уровня L1
#define CONFIG_X86_L1_CACHE_SHIFT 5

#define L1_CACHE_SHIFT	(CONFIG_X86_L1_CACHE_SHIFT)
#define L1_CACHE_BYTES	(1 << L1_CACHE_SHIFT)

// отдельная секция read_mostly
#define __read_mostly   __attribute__((__section__(".data..read_mostly")))

#endif /* ARCH_X86_PROCESSOR_H */