#ifndef GENERIC_LISTS_LLIST_H
#define GENERIC_LISTS_LLIST_H

#include <kernel.h>
#include _SOS_CPU_HDR_DIR_(sync/cmpxchg.h)
/*
 * блокирующий односвязный список
 */

struct llist_head {
    struct llist_node *first;
};

struct llist_node {
    struct llist_node *next;
};

#define LLIST_HEAD_INIT(name)           { NULL }
#define LLIST_HEAD(name)                struct llist_head name = LLIST_HEAD_INIT(name)
#define llist_entry(ptr, type, member)  container_of(ptr, type, member)

static inline void llist_head_init(struct llist_head *list)
{
    list->first = NULL;
}

// пройтись по списку
#define llist_for_each(pos, node)   for ((pos) = (node); pos; (pos) = (pos)->next)

// перебрать список заданного типа
#define llist_for_each_entry(pos, node, member)\
	for ((pos) = llist_entry((node), typeof(*(pos)), member); &(pos)->member != NULL; (pos) = llist_entry((pos)->member.next, typeof(*(pos)), member))

// перебрать список данного типа защищены от удаления записи из списка
#define llist_for_each_entry_safe(pos, n, node, member)\
	for (pos = llist_entry((node), typeof(*pos), member); &pos->member != NULL && (n = llist_entry(pos->member.next, typeof(*n), member), true); pos = n)

// первый элемент пустой
static inline int llist_empty(const struct llist_head *head)
{
    return ACCESS_ONCE(head->first) == NULL;
}

// следующий элемент 
static inline struct llist_node *llist_next(struct llist_node *node)
{
    return node->next;
}

// добавить новую запись
extern int llist_add_batch(struct llist_node *new_first, struct llist_node *new_last, struct llist_head *head);

static inline int llist_add(struct llist_node *n, struct llist_head *head)
{
    return llist_add_batch(n, n, head);
}

// удалить все записи из замка-меньше список
static inline struct llist_node *llist_del_all(struct llist_head *head)
{
    return xchg(&head->first, NULL);
}

// удалить первую запись
extern struct llist_node *llist_del_first(struct llist_head *head);

// обратный порядок цепочки списка
struct llist_node *llist_reverse_order(struct llist_node *head);
#endif /* GENERIC_LISTS_LLIST_H */