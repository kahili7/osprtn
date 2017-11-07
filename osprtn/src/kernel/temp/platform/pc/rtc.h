#ifndef KERNEL_PLATFORM_PC_RTC_H
#define KERNEL_PLATFORM_PC_RTC_H

// часы реального времени, которые от батарейки

#include DIR_ARCH(ioport.h)

typedef struct rtc {
    u16_t base;
} rtc_t;

u8_t rtc_read(rtc_t *s, const u8_t reg)
{
    out_u8(s->base, reg);
    return in_u8(s->base + 1);
};

void rtc_write(rtc_t *s, const u8_t reg, const u8_t val)
{
    out_u8(s->base, reg);
    out_u8(s->base+1, val);
};

INLINE void wait_for_second_tick()
{
    rtc_t *t;
    
    t->base = 0x70;

    // отк. бита
    while (rtc_read(t, 0x0a) & 0x80);

    // читать второе значение
    word_t secstart = rtc_read(t, 0);

    // ждать до тех пор пока изменится второе значение
    while (secstart == rtc_read(t, 0));
}
#endif /* KERNEL_PLATFORM_PC_RTC_H */