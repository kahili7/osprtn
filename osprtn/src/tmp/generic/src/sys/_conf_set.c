#include <errno-defs.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/conf.h>

int _conf_set(long **plist, int cmd, int name, long value, const char *str)
{
    long *list = *plist;
    int pos = 0;
    
    if((list = *plist))
    {
        long lst_item;
        
        while((lst_item = *list++) != _CONF_END)
        {
            int match;
            
            switch(lst_item & _CONF_CMD_MASK)
            {
                case _CONF_VALUE:
                    match = lst_item & _CONF_NAME_MASK;
                    
                    if(match == _CONF_NAME_LONG) match = *list++;
                    
                    if(match == name)
                    {
                        if(str && (lst_item & _CONF_STR))
                        {
                            char *p;

                            if(!(p = realloc((char **)*list, value + 1))) return ENOMEM;
                          
                            strncpy(p, str, value);
                            p[value] = '\0';
                            *(char **)list = p;
                            return EOK;
                        }
                        
                        if(!str && (lst_item & _CONF_NUM))
                        {
                            *list = value;
                            return EOK;
                        }
                    }
                    
                case _CONF_CALL:
                case _CONF_LINK:
                    list++;
                    break;
                default:
                    break;
            }
        }
        
        pos = (list - *plist) - 1;
    }
    
    if(str)
    {
        char *s;

        if(!(cmd & _CONF_STR))
        {
            return EINVAL;
        }
        
        if(!(s = malloc(value + 1)))
        {
            return ENOMEM;
        }
        
        strncpy(s, str, value);
        s[value] = '\0';
        value = (intptr_t)s;
    }
    else if(!(cmd & _CONF_NUM)) return EINVAL;
    
    if(!(list = realloc(*plist, (pos + (name >= _CONF_NAME_LONG ? 4 : 3)) * sizeof *list)))
    {
        if(str) free((void *)value);

        return ENOMEM;
    }
    
    *plist = list;
    list += pos;

    if(name >= _CONF_NAME_LONG)
    {
        list[1] = name;
        list[2] = value;
        list[3] = _CONF_END;
        name = _CONF_NAME_LONG;
    }
    else
    {
        list[1] = value;
        list[2] = _CONF_END;
    }
    
    list[0] = name | (cmd & ~_CONF_NAME_LONG) | _CONF_VALUE;
    return EOK;
}