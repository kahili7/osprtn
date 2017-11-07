#ifndef KERNEL_PROTON_KERNEL_ARGS_H
#define KERNEL_PROTON_KERNEL_ARGS_H

#if !defined(KARGSLOT)
    #define KARGSLOT(arg)   arg
#endif

union _kernel_args {
    // пустая структура
    struct _kernel_args_null {
        KARGSLOT(int32_t dummy);
    } null;
    
    struct _kernel_args_ring0 {
        KARGSLOT(void   (*func)(void *));
        KARGSLOT(void   *arg);
    } ring0;
        
    // --Каналы--
    #include <kernel-args/kernel-args-channel.h>
    
    // --Соединения--
    #include <kernel-args/kernel-args-connect.h>

    // структура с атрибутами канала и соединения
    struct _kernel_args_channel_connect_attr {
        KARGSLOT(int32_t			id);
        KARGSLOT(union _channel_connect_attr    *old_attrs);
        KARGSLOT(union _channel_connect_attr    *new_attrs);
        KARGSLOT(int32_t			flags);
    } channel_connect_attr;
    
    // --Сообщения--
    #include <kernel-args/kernel-args-msg.h>
    
    // --Сигналы--
    #include <kernel-args/kernel-args-signal.h>
    
    // --Потоки--
    #include <kernel-args/kernel-args-thread.h>

    // --Планирование--
    #include <kernel-args/kernel-args-sched.h>

    // --Прерывания--
    #include <kernel-args/kernel-args-interrupt.h>

    // --Синхронизация--
    #include <kernel-args/kernel-args-sync.h>

    // --Часы--
    #include <kernel-args/kernel-args-clock.h>

    // --Таймеры--
    #include <kernel-args/kernel-args-timer.h>

    struct _kernel_args_net_cred {
        KARGSLOT(int32_t		coid);
        KARGSLOT(struct _client_info    *info);
    } net_cred;

    struct _kernel_args_net_vtid {
        KARGSLOT(int32_t            vtid);
        KARGSLOT(struct _vtid_info  *info);
    } net_vtid;

    struct _kernel_args_net_unblock {
        KARGSLOT(int32_t    vtid);
    } net_unblock;

    struct _kernel_args_net_infoscoid {
        KARGSLOT(int32_t    scoid);
        KARGSLOT(int32_t    infoscoid);
    } net_infoscoid;

    struct _kernel_args_trace_event {
        KARGSLOT(uint32_t   *data);
    } trace_event;

    struct _kernel_args_sys_cpupage_get {
        KARGSLOT(int32_t    index);
    } sys_cpupage_get;

    struct _kernel_args_sys_cpupage_set {
        KARGSLOT(int32_t    index);
        KARGSLOT(intptr_t   value);
    } sys_cpupage_set;

    struct _kernel_args_net_signal_kill {
        KARGSLOT(void*              sigdata);
        KARGSLOT(struct _cred_info  *cred);
    } net_signal_kill;
};
#endif /* KERNEL_PROTON_KERNEL_ARGS_H */