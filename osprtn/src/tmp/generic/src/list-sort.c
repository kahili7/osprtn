#include <kernel.h>
#include <export.h>
#include <string.h>
#include <lists/list-sort.h>
#include <lists/list.h>

#define MAX_LIST_LENGTH_BITS 20

static struct list_head *merge(void *priv, int (*cmp)(void *priv, struct list_head *a, struct list_head *b), struct list_head *a, struct list_head *b)
{
    struct list_head head;
    struct list_head *tail = &head;

    while (a && b)
    {
        /* if equal, take 'a' -- important for sort stability */
        if ((*cmp)(priv, a, b) <= 0)
        {
            tail->next = a;
            a = a->next;
        }
        else
        {
            tail->next = b;
            b = b->next;
        }
        
        tail = tail->next;
    }
    
    tail->next = a ? : b;
    return head.next;
}

static void merge_and_restore_back_links(void *priv, int (*cmp)(void *priv, struct list_head *a, struct list_head *b), struct list_head *head, struct list_head *a, struct list_head *b)
{
    struct list_head *tail = head;
    _Uint8t count = 0;

    while (a && b)
    {
        if ((*cmp)(priv, a, b) <= 0)
        {
            tail->next = a;
            a->prev = tail;
            a = a->next;
        }
        else
        {
            tail->next = b;
            b->prev = tail;
            b = b->next;
        }
        
        tail = tail->next;
    }
    
    tail->next = a ? : b;

    do {
        if (unlikely(!(++count))) (*cmp)(priv, tail->next, tail->next);

        tail->next->prev = tail;
        tail = tail->next;
    } while (tail->next);

    tail->next = head;
    head->prev = tail;
}

void list_sort(void *priv, struct list_head *head, int (*cmp)(void *priv, struct list_head *a, struct list_head *b))
{
    struct list_head *part[MAX_LIST_LENGTH_BITS + 1];
    struct list_head *list;
    int i;
    int max_i = 0;
    
    if (list_empty(head)) return;

    memset(part, 0, sizeof(part));
    head->prev->next = NULL;
    list = head->next;

    while (list)
    {
        struct list_head *cur = list;
        
        list = list->next;
        cur->next = NULL;

        for (i = 0; part[i]; i++)
        {
            cur = merge(priv, cmp, part[i], cur);
            part[i] = NULL;
        }
        
        if (i > max_i)
        {
            if (unlikely(i >= ARRAY_SIZE(part)-1))
            {
                printk_once(KERN_DEBUG "list too long for efficiency\n");
                i--;
            }
            
            max_i = i;
        }
        
        part[i] = cur;
    }

    for (i = 0; i < max_i; i++)
    {
        if (part[i]) list = merge(priv, cmp, part[i], list);
    }
    
    merge_and_restore_back_links(priv, cmp, head, part[max_i], list);
}
EXPORT_SYMBOL(list_sort);