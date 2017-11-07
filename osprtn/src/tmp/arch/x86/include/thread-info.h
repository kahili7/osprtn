#ifndef ARCH_X86_THREAD_INFO_H
#define ARCH_X86_THREAD_INFO_H

#include <compiler.h>
#include _SOS_CPU_HDR_DIR_(page.h)
/*
 * низкоуровневая информация о потоке
 */

#ifndef __ASSEMBLY__
    struct task_struct;
    
    #include _SOS_CPU_HDR_DIR_(processor.h)
    #include <sync/atomic.h>

    // информация о потоке
    struct thread_info_struct {
        struct task_struct          *task;   // главная структура задач
        //struct exec_domain_struct *exec_domain;
        _Uint32t                    flags;  // низкоуровневые флаги
        _Uint32t                    status; // флаги синхронизации потока
        _Uint32t                    cpu;    // текущий CPU
        int                         preempt_count;  // зарезервированный счетчик 0 - вытесняемая; <0 - баг
        mm_segment_t                addr_limit; // адрес
        struct restart_block_struct restart_block;  // перезагрузка блока
    };
    

#endif
    
#ifdef CONFIG_X86_32   
    #define STACK_WARN  (THREAD_SIZE/8)

    #ifndef __ASSEMBLY__
        // указатель на стэк
        register unsigned long current_stack_pointer asm("esp") __used;
        
        static inline struct thread_info_struct *current_thread_info(void)
        {
            return (struct thread_info_struct *) (current_stack_pointer & ~(THREAD_SIZE - 1));
        }
    #else
        #define GET_THREAD_INFO(reg)\
	movl $-THREAD_SIZE, reg;\
	andl %esp, reg

        #define GET_THREAD_INFO_WITH_ESP(reg)\
	andl $-THREAD_SIZE, reg
    #endif
#endif

#endif /* ARCH_X86_THREAD_INFO_H */