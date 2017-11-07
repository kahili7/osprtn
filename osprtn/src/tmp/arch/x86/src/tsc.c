#include <platform.h>
#include <kernel.h>
#include <cache.h>
#include <percpu.h>

#include _SOS_CPU_HDR_DIR_(msr.h)

unsigned int __read_mostly cpu_khz;     // частота процессора в килогерцах
unsigned int __read_mostly tsc_khz;     // частота TSC в килогерцах

static int __read_mostly tsc_unstable;          // нестабильная частота TSC
static int __read_mostly tsc_disabled = -1;     // включен ли TSC

// чтение счетчика TSC и значение возвращается в регистрах EDX:EAX
unsigned long long native_read_tsc(void)
{
    return __native_read_tsc();
}

// проверить стабильность TSC
int check_tsc_unstable(void)
{
    return tsc_unstable;
}

// проверить включена ли возможность TSC
int check_tsc_disabled(void)
{
    return tsc_disabled;
}