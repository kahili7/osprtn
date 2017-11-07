// структура сигнала на убийство
struct _kernel_args_signal_kill {
    KARGSLOT(uint32_t	nd);
    KARGSLOT(pid_t	pid);
    KARGSLOT(int32_t	tid);
    KARGSLOT(int32_t	signo);
    KARGSLOT(int32_t	code);
    KARGSLOT(int32_t	value);
} signal_kill;

// структура сигнала на возврат
struct _kernel_args_signal_return {
    KARGSLOT(SIGSTACK 	*s);
} signal_return;

// структура сигнала на действии
struct _kernel_args_signal_action {
    KARGSLOT(pid_t		pid);
    KARGSLOT(void		(*sigstub)());
    KARGSLOT(int32_t		signo);
    KARGSLOT(struct sigaction	*act);
    KARGSLOT(struct sigaction	*oact);
} signal_action;

// структура сигнала маскирование процесса
struct _kernel_args_signal_procmask {
    KARGSLOT(pid_t	pid);
    KARGSLOT(int32_t	tid);
    KARGSLOT(int32_t	how);
    KARGSLOT(sigset_t	*sig_blocked);
    KARGSLOT(sigset_t	*old_sig_blocked);
} signal_procmask;

// структура сигнала на приостановление
struct _kernel_args_signal_suspend {
    KARGSLOT(sigset_t	*sig_blocked);
} signal_suspend;

// структура сигнала на ожидание
struct _kernel_args_signal_wait {
    KARGSLOT(sigset_t	*sig_wait);
    KARGSLOT(siginfo_t	*sig_info);
} signal_wait;

// структура сигнала на ошибку
struct _kernel_args_signal_fault {
    KARGSLOT(unsigned	sigcode);
    KARGSLOT(void	*regs);
    KARGSLOT(uintptr_t	addr);
} signal_fault;
