#include <stdlib.h>
#include <string.h>
#include <sys/conf.h>

// возвращает результат списка команд
int _conf_get(const long *list, int name, long *value, char *str)
{
    long lst_item;
    
    while((lst_item = *list++) != _CONF_END)
    {
        int cmd;
        int match;
        long num;
        
        switch(cmd = (lst_item & _CONF_CMD_MASK))
        {
            // пустая команда
            case _CONF_NOP:
		break;
            
            // значения
            case _CONF_VALUE:
                match = lst_item & _CONF_NAME_MASK;
                
                if(match == _CONF_NAME_LONG)
                {
                    match = *list++;
                }
                
                if((lst_item & (_CONF_NUM | _CONF_STR)) == 0) break;
                
                if(name != match)
                {
                    list++;
                    break;
                }
                
            case _CONF_CALL:
            case _CONF_LINK:             
                num = *list++;
                
                if(((lst_item & _CONF_STR) && !str) || ((lst_item & _CONF_NUM) && str)) break;              
                if(lst_item & _CONF_INDIRECT) num = *(long *)num;
                
                if(cmd == _CONF_VALUE)
                {
                    if(lst_item & _CONF_NUM)
                    {
                        long i;

                        if(lst_item & _CONF_FCN)
                        {
                            long (*func)(int name);

                            if(!(func = (void *)num)) break;

                            num = func(name);
                        }

                        i = *value;
                        
                        switch(lst_item & _CONF_MOD_MASK)
                        {
                            case _CONF_NUM_MIN:
                                *value = (i == -1) ? num : min(i, num);
                                break;
                                    
                            case _CONF_NUM_MAX:
                                *value = (i == -1) ? num : max(i, num);
                                break;
                                
                            case _CONF_NUM_ADD:
                                *value = (i == -1) ? num : i + num;
                                break;
                                
                            default:
                                *value = num;
                                return 0;
                        }
                    }
                    else
                    {
                        if(lst_item & _CONF_FCN)
                        {
                            size_t (*func)(int name, char *buff, size_t len);

                            if(!(func = (void *)num)) break;

                            *value = func(name, str, *value);
                        }
                        else
                        {
                            char *ptr = (char *)num;
                            size_t len = strlen(ptr) + 1;
                        
                            strncpy(str, ptr, min((size_t)*value, len));
                            *value = len;
                        }
                        
                        return 0;
                    }
                    
                    break;
                }
                else
                {
                    if(lst_item & _CONF_FCN)
                    {
                        int (*func)(int name, long *value, char *str);

                        if((func = (void *)num))
                        {
                            int status;

                            if((status = func(name, value, str)) != -1 || cmd == _CONF_LINK)
                            {
                                    return status;
                            }
                        }
                    }
                    else if(cmd == _CONF_LINK)
                    {
                        list = (long *)num;
                    }
                    else if(num)
                    {
                        int status;

                        if((status = _conf_get((long *)num, name, value, str)) != -1)
                        {
                            return status;
                        }
                    }
                }
		
                break;
                
            case _CONF_END:
            default:
                return -1;
	}
        
	return -1;
    }
}