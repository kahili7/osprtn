#ifndef KERNEL_OBJS_H
#define KERNEL_OBJS_H

// длина сообщения
#ifndef _SHORT_MSG_LEN
    #define _SHORT_MSG_LEN  256
#endif

// типы объектов
enum {
    TYPE_THREAD,
    TYPE_PULSE,
    TYPE_SIGNAL,
    TYPE_VTHREAD,
    TYPE_CONNECTION,
    TYPE_CHANNEL,
    TYPE_VPULSE,
    TYPE_SYNCEVENT,
    TYPE_TYPE_MASK  = 0x0f,
    TYPE_FLAG_FIRST	= 0x10
};

#define TYPE_MASK(t)    ((t) & TYPE_TYPE_MASK)

struct _sighandler_entry {
    void        (*handler)(_SIG_ARGS);
    unsigned    flags;
    sigset_t    sig_blocked;
};

#define HANDLERS_PER_SIGTABLE	4
struct _sigtable_entry {
    SIGTABLE    *next;
    uint32_t	sig_base;
    SIGHANDLER	handlers[HANDLERS_PER_SIGTABLE];
};

#include <kobjs-vector.h>

#include <kobjs-pril.h>

#include <kobjs-process.h>

#include <kobjs-channel.h>

#include <kobjs-connect.h>

#include <kobjs-net.h>

// --Пульсы--
#include <kobjs-pulse.h>

// --Планирование--
#include <kobjs-ss.h>

// --Потоки--
#include <kobjs-thread.h>
#endif /* KERNEL_OBJS_H */