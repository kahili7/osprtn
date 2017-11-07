#include <kernel.h>
#include <export.h>
#include <lists/llist.h>

// добавить несколько связанных записей в пакете
int llist_add_batch(struct llist_node *new_first, struct llist_node *new_last, struct llist_head *head)
{
    struct llist_node *first;

    do {
        new_last->next = first = ACCESS_ONCE(head->first);
    } while (cmpxchg_smp(&head->first, first, new_first) != first);

    return !first;
}
EXPORT_SYMBOL_GPL(llist_add_batch);

// удалить первую запись из замка-меньше список
struct llist_node *llist_del_first(struct llist_head *head)
{
    struct llist_node *entry, *old_entry, *next;

    entry = head->first;
    
    for (;;)
    {
        if (entry == NULL) return NULL;
        
        old_entry = entry;
        next = entry->next;
        entry = cmpxchg_smp(&head->first, old_entry, next);
        
        if (entry == old_entry) break;
    }

    return entry;
}
EXPORT_SYMBOL_GPL(llist_del_first);

// обратный порядок цепочки списка
struct llist_node *llist_reverse_order(struct llist_node *head)
{
    struct llist_node *new_head = NULL;

    while (head)
    {
        struct llist_node *tmp = head;
        
        head = head->next;
        tmp->next = new_head;
        new_head = tmp;
    }

    return new_head;
}
EXPORT_SYMBOL_GPL(llist_reverse_order);