#ifndef KERNEL_OBJS_TIMER_H
#define KERNEL_OBJS_TIMER_H

#include "kernel/x86_defs.h"
#include "lib/types.h"

// структура описывающая таймер
typedef struct _TIMER {
    struct _TIMER_LINK {
	PTIMER Next;   // указатель на следующий таймер
	PTIMER Prev;   // указатель на предыдущий таймер
    } TIMER_LINK;
    
    PTIMER          Pending;        // указатель на отложенный таймер
    PTIMER_QUEUE    Queue;          // указатель на очередь таймера
    PTHREAD         Thread;         // указатель на поток
    UCHAR           ClockId;        // флаги программного таймера
    UCHAR           Flags;          // флаги таймера
    ITIMER          IntervalTime;   // интервал времени
} TIMER, *PTIMER;

#endif /* KERNEL_OBJS_TIMER_H */