#ifndef GENERIC_THREADS_H
#define GENERIC_THREADS_H

// максимальное поддерживаемое количество процессоров
#ifndef CONFIG_MAX_NUM_CPUS
    #define CONFIG_MAX_NUM_CPUS  1
#endif

#define MAX_NUM_CPUS CONFIG_MAX_NUM_CPUS

#endif /* GENERIC_THREADS_H */