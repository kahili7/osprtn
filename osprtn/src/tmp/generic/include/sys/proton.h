#ifndef GENERIC_SYS_PROTON_H
#define GENERIC_SYS_PROTON_H

#include <platform.h>

// спин блокировка прерывания
typedef struct _intrspin {
    volatile unsigned value;
} intrspin_t;

// информация о сообщении
struct _msg_info {              /* _msg_info	_server_info */
    _Uint32t    nd;             /* client   server */   // узел дескриптора клиентского компьютера, если смотреть со стороны сервера
    _Uint32t	srvnd;          /* server   n/a */      // узел дескриптора сервера, глазами клиента
    pid_t	pid;            /* client   server */   // ID процесса отправляющего поток
    _Int32t	tid;            /* thread   n/a */      // ID потока направляющего поток
    _Int32t	chid;           /* server   server */   // ID канала, что сообщение было получено на
    _Int32t	coid;           /* client   client */   // ID соединения клиента
    _Int32t	scoid;          /* server   server */   // Сервер ID соединения
    _Int32t	msglen;         /* msg      n/a */      // число байт, полученных
    _Int32t	srcmsglen;	/* thread   n/a */      // длина исходного сообщения в байтах
    _Int32t	dstmsglen;	/* thread   n/a */      // длину клиента ответить буфера, в байтах
    _Int16t	priority;	/* thread   n/a */      // приоритет посылающего потока
    _Int16t	flags;		/* n/a      client */   // клиент имеет разблокировать ожидании
    _Uint32t	reserved;
};

#define _server_info    _msg_info

// cтруктура, которая описывает пользователя и группу, с правами
struct _cred_info {
    uid_t       ruid;       // реальный id юзера 
    uid_t	euid;       // эффективный id юзера
    uid_t	suid;       // сохраненный id юзера
    gid_t	rgid;       // реальный id группы
    gid_t	egid;       // эффективный id группы
    gid_t	sgid;       // сохраненный id группы
    _Uint32t	ngroups;    // число групп, на самом деле хранится в grouplist
    gid_t	grouplist[__NGROUPS_MAX];       // в дополнительных идентификаторов групп
};

// структура с информацией о клиенте  
struct _client_info {
    _Uint32t            nd;     // ID узла клиента
    pid_t		pid;    // ID процесса клиента
    pid_t		sid;
    _Uint32t		flags;
    struct _cred_info	cred;   // ID пользователь & группы и учетные данные
};

// структура с информацией о планировщике
struct _sched_info {
    int         priority_min;
    int		priority_max;
    _Uint64t	interval;
    int		priority_priv;
    int		reserved[11];
};

// структура периода времени
struct _clockperiod {
    unsigned long   nsec;
    long            fract;  //часть
};
/*
 * прототипы системных функций
 */

// планировщик

extern int ptn_SchedGet(pid_t __pid, int __tid, struct sched_param *__param);
extern int ptn_SchedGet_r(pid_t __pid, int __tid, struct sched_param *__param);
#endif /* GENERIC_SYS_PROTON_H */