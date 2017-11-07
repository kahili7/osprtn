#ifndef GENERIC_LISTS_PLIST_H
#define GENERIC_LISTS_PLIST_H

#include <kernel.h>
#include <lists/list.h>

/*
 * приоритетный список
 */

struct plist_head {
    struct list_head node_list;
};

struct plist_node {
    int			prio;
    struct list_head	prio_list;
    struct list_head	node_list;
};

// инициализация головы списка и узла списка
#define PLIST_HEAD_INIT(head)   { .node_list = LIST_HEAD_INIT((head).node_list)	}
#define PLIST_HEAD(head)        struct plist_head head = PLIST_HEAD_INIT(head)
#define PLIST_NODE_INIT(node, __prio)\
        {\
            .prio  = (__prio),\
            .prio_list = LIST_HEAD_INIT((node).prio_list),\
            .node_list = LIST_HEAD_INIT((node).node_list),\
        }

static inline void plist_head_init(struct plist_head *head)
{
    list_head_init(&head->node_list);
}

static inline void plist_node_init(struct plist_node *node, int prio)
{
    node->prio = prio;
    list_head_init(&node->prio_list);
    list_head_init(&node->node_list);
}

// перебирать список
#define plist_for_each(pos, head)               list_for_each_entry(pos, &(head)->node_list, node_list)

// продолжать перебирать список, продолжая после текущей позиции
#define plist_for_each_continue(pos, head)      list_for_each_entry_continue(pos, &(head)->node_list, node_list)

// перебирайте список в каталоге данного типа, защищены от удаления записи из списка
#define plist_for_each_safe(pos, n, head)	list_for_each_entry_safe(pos, n, &(head)->node_list, node_list)

// перебрать список заданного типа
#define plist_for_each_entry(pos, head, mem)	list_for_each_entry(pos, &(head)->node_list, mem.node_list)

// перебрать список заданного типа, продолжая после текущей позиции
#define plist_for_each_entry_continue(pos, head, mem)   list_for_each_entry_continue(pos, &(head)->node_list, mem.node_list)

// перебрать список данного типа, защищены от удаления записи из списка
#define plist_for_each_entry_safe(pos, n, head, mem)    list_for_each_entry_safe(pos, n, &(head)->node_list, mem.node_list)

// возвращает !0, если список пустой
static inline int plist_head_empty(const struct plist_head *head)
{
    return list_empty(&head->node_list);
}

// возвращает !0, если узел пустой
static inline int plist_node_empty(const struct plist_node *node)
{
    return list_empty(&node->node_list);
}

// получить структуру для первой записи
#define plist_first_entry(head, type, member)   container_of(plist_first(head), type, member)

// получить структуру для последней записи
#define plist_last_entry(head, type, member)   container_of(plist_last(head), type, member)

// получить следующую запись
#define plist_next(pos)     list_next_entry(pos, node_list)

// получить предыдущую запись
#define plist_prev(pos)     list_prev_entry(pos, node_list)

// возвращает первый узел
static inline struct plist_node *plist_first(const struct plist_head *head)
{
    return list_entry(head->node_list.next, struct plist_node, node_list);
}

// возвращает последний узел
static inline struct plist_node *plist_last(const struct plist_head *head)
{
    return list_entry(head->node_list.prev, struct plist_node, node_list);
}
#endif /* GENERIC_LISTS_PLIST_H */