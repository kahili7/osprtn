#ifndef GENERIC_MQUEUE_H
#define GENERIC_MQUEUE_H

#include <platform.h>
#include <types.h>

/*
 * очередь сообщений
 */

// непрозрачный дескриптор очереди cообщений
#ifndef _MQD_T
#define _MQD_T     __kernel_mqd_t
    typedef _MQD_T mqd_t;
#undef _MQD_T
#endif
    
// атрибуты очереди сообщений
struct mq_attr {
    long mq_flags;      // флаги очереди сообщений
    long mq_msgsize;    // максимальная длина сообщения
    long mq_maxmsg;     // максимальное количество сообщений   
    long mq_curmsgs;    // текущее количество сообщений, хранящихся
    long mq_sendwait;   // число процессов, ожидающих отправки
    long mq_recvwait;   // число процессов, ожидающих получения
};

extern mqd_t mq_open(const char *__name, int __oflag, ...);


#endif /* GENERIC_MQUEUE_H */