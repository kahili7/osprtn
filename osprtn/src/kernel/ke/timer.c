
#include "kernel/objs/timer.h"

typedef enum _FIRE_SOURCE {
    FS_INTR,
    FS_ACTIVATE,
    FS_PENDING
} FIRE_SOURCE;

#define TIMER_QUEUE_FLAG_TOD    0x0001  // Time of day
#define TIMER_QUEUE_FLAG_OLD    0x0002

// структура описывающая очередь для таймера
typedef struct _TIMER_QUEUE {
    PTIMER_QUEUE        Next;           // указатель на следующую структуру
    USHORT              Downshift;      // понижение разрядности
    USHORT              Mask;           // маска
    USHORT              CountActive;    // количество таймеров в очереди
    USHORT              Flags;          // флаги очереди
    struct _TIMER_LINK  Slot[1];        // ссылка на список таймеров имеющий переменный размер
} TIMER_QUEUE, *PTIMER_QUEUE;

#define TIMER_QUEUE_MAX_MASK        (127) 
#define TIMER_QUEUE_MAX_SEARCH      100
#define CHECK_LINKAGES(tip) \
    CRASHCHECK((tip)->TIMER_LINK.prev->TIMER_LINK.next != (tip)); \
    CRASHCHECK((tip)->TIMER_LINK.next->TIMER_LINK.prev != (tip)); \
    
// уменьшаем нижние 32 бита из 64 бит наносекунд
#define GET_TIMER_QUEUE_INDEX(q, t) ((((UINT)(t)) >> (q)->Downshift) & (q)->mask)

// добавление элемента старой очереди в новую 
#define ADD_TIMER_IN_NEW_QUEUE(head, old, new) \
    do { \
        (new)->Flags = (old)->Flags; \
        (new)->Next = (old)->Next; \
        (old)->Next = (new); \
        MEM_BARRIER(); \
        *(head) = (new); \
        (old)->Flags |= TIMER_QUEUE_FLAG_OLD; \
    } while(0)

// аналог NULL для таймера
#define PENDING_TIMER_END   ((PTIMER)0x1)

static PTIMER           PendingHead = PENDING_TIMER_END;
static PTIMER_QUEUE     QueueHead;
static PTIMER_QUEUE     QueueDead;

static PTIMER_QUEUE     MONTimers;  // указатель на очередь с относительными таймерами
static PTIMER_QUEUE     TODTimers;  // указатель на очередь с абсолютными таймерами

void TimerInit(void)
{
    TODTimers = NewQueue(4, 0);
    TODTimers->Flags = TIMER_QUEUE_FLAG_TOD;
    
    MONTimers = NewQueue(4, 0);
    MONTimers->Next = TODTimers;
    
    QueueHead = MONTimers;
}

void TimerPeriod(void)
{
    ULONGLONG   inc;
    USHORT      downshift;
    
    downshift = 0;
}

// --- внутренние функции ---
static void NewPeriod(PTIMER_QUEUE *head, USHORT downshift)
{
    PTIMER_QUEUE new;
    PTIMER_QUEUE old;
    
    old = *head;
    
    if(old->Downshift != downshift)
    {
        if(old->CountActive == 0)
        {
            old->Downshift = downshift;
        }
        else
        {
            new = NewQueue(old->Mask + 1, downshift);
            
            if(new != NULL)
            {
                ADD_TIMER_IN_NEW_QUEUE(head, old, new);
            }
        }
    }
}

// создать новую очередь для таймера
static PTIMER_QUEUE NewQueue(USHORT entries, USHORT downshift)
{
    PTIMER_QUEUE        new;
    struct _TIMER_LINK  *link;
    
    if(new != NULL)
    {
        new->Mask = entries - 1;
        new->Downshift = downshift;
        
        do {
            link = &new->Slot[--entries];
            link->Prev = link->Next = (PTIMER)link;
        } while(entries != 0);
    }
    
    return new;
}

static void KillQueue(PTIMER queue)
{
    CRASHCHECK(queue == MONTimers || queue == TODTimers);
}

static void TimerInsert(PTIMER tip, FIRE_SOURCE src)
{
    PTIMER          fore;
    PTIMER          back;
    PTIMER_QUEUE    *head;
    PTIMER_QUEUE    queue;
    PTIMER_QUEUE    new;
    
    USHORT          index;
    USHORT          max_search;
    
    queue = *head;
    
LRETRY: 
    tip->Queue = queue;
    
    if(src == FS_INTR)
    {
        max_search = 0;
    }
    else if(queue->CountActive >= (2 * TIMER_QUEUE_MAX_SEARCH) * (queue->Mask + 1))
    {
        max_search = 1;
    }
    else max_search = TIMER_QUEUE_MAX_SEARCH;
    
    index = GET_TIMER_QUEUE_INDEX(queue, tip->IntervalTime);
    back = fore = (PTIMER)&queue->Slot[index];
    
    if(fore->TIMER_LINK.Next != back)
    {
        for(;;)
        {
            CHECK_LINKAGES(fore);
            CHECK_LINKAGES(back);
            
            fore = fore->TIMER_LINK.Next;
            back = back->TIMER_LINK.Prev;
            
            if((--max_search == 0) && (queue->Mask < TIMER_QUEUE_MAX_MASK))
            {
                new = NewQueue((queue->Mask + 1) << 2, queue->Downshift);
                
                if(new != NULL)
                {
                    // добавление нового таймера в очередь
                    ADD_TIMER_IN_NEW_QUEUE(head, queue, new);
                    queue = new;
                    goto LRETRY;
                }
            }
            
            if(tip->IntervalTime.NSecond >= back->IntervalTime.NSecond) goto LINSERT_AFTER;
            if(tip->IntervalTime.NSecond <  fore->IntervalTime.NSecond) goto LINSERT_BEFORE;
        }
    }
    
LINSERT_AFTER:
    tip->TIMER_LINK.Next = back->TIMER_LINK.Next;
    tip->TIMER_LINK.Prev = back;
    back->TIMER_LINK.Next->TIMER_LINK.Prev = tip;
    back->TIMER_LINK.Next = tip;
    
    CHECK_LINKAGES(tip);
    CHECK_LINKAGES(back);
    
    queue->CountActive += 1;
    return;
    
LINSERT_BEFORE:
    tip->TIMER_LINK.Prev = fore->TIMER_LINK.Prev;
    tip->TIMER_LINK.Next = fore;
    fore->TIMER_LINK.Prev->TIMER_LINK.Next = tip;
    fore->TIMER_LINK.Prev = tip;
    
    CHECK_LINKAGES(tip);
    CHECK_LINKAGES(fore);
    
    queue->CountActive += 1;
    return;
}

// перевооружать таймер
static void TimerRearm(PTIMER tip, FIRE_SOURCE src)
{
    ULONGLONG   interval;
    PTIMEBASE   tb;
    
    if(src != FS_ACTIVATE)
    {
        tip->TIMER_LINK.Next->TIMER_LINK.Prev = tip->TIMER_LINK.Prev;
        tip->TIMER_LINK.Prev->TIMER_LINK.Next = tip->TIMER_LINK.Next;
        
        CHECK_LINKAGES(tip->TIMER_LINK.Prev);
        CHECK_LINKAGES(tip->TIMER_LINK.Next);
        
        tip->Queue->CountActive -= 1;
    }
    
    tip->Pending = NULL;
    
    if(tip->IntervalTime.Interval_NSecond == 0)
    {
        // таймер истек
        tip->Flags = (tip->Flags & ~PROTON_TIMER_ACTIVE) | PROTON_TIMER_EXPIRED;
        tip->Queue = NULL;
        return;
    }
    
    // интервальный таймер, активировать с нового времени.
    tb = TimeBasePtr;
    
    // следующей проверкой предотвращаются бесконечные циклы
    interval = tip->IntervalTime.Interval_NSecond;
    
    if(interval < tb->NSecondInc)
    {
        interval = tb->NSecondInc;
    }
    
    // пересчитать время пуска
    tip->IntervalTime.Interval_NSecond += interval;
    
    if(tip->ClockId == CLOCK_SOFTTIME)
    {
        
    }
    
    TimerInsert(tip, src);
}