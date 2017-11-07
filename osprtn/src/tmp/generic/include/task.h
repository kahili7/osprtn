#ifndef GENERIC_TASK_H
#define GENERIC_TASK_H

struct task_struct {  
    volatile long state;    // -1 - незапущено; 0 - запущено; >0 - остановлено 
};
#endif /* GENERIC_TASK_H */