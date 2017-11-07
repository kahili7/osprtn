#include <lists/plist.h>
#include <sync/spinlock.h>

#define plist_check_head(h)     do {} while (0)

// добавление узла в список
void plist_add(struct plist_node *node, struct plist_head *head)
{
    struct plist_node *first, *iter, *prev = NULL;
    struct list_head *node_next = &head->node_list;

    plist_check_head(head);
    //WARN_ON(!plist_node_empty(node));
    //WARN_ON(!list_empty(&node->prio_list));

    if (plist_head_empty(head)) goto ins_node;

    first = iter = plist_first(head);

    do {
        if (node->prio < iter->prio)
        {
            node_next = &iter->node_list;
            break;
        }

        prev = iter;
        iter = list_entry(iter->prio_list.next, struct plist_node, prio_list);
    } while (iter != first);

    if (!prev || prev->prio != node->prio) list_add_tail(&node->prio_list, &iter->prio_list);

ins_node:
    list_add_tail(&node->node_list, node_next);
    plist_check_head(head);
}