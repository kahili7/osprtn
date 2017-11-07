#ifndef GENERIC_LISTS_LIST_NULLS_H
#define GENERIC_LISTS_LIST_NULLS_H

#include <poison.h>

/*
 * Специальная версия списков, где конец списка-это не нулевой указатель,
 * но 'обнуляет' маркер, который может иметь много разных значений.
 * (до 2^31 разных значений гарантируется на всех платформах)
 */

struct hlist_nulls_head {
    struct hlist_nulls_node *first;
};

struct hlist_nulls_node {
    struct hlist_nulls_node *next, **pprev;
};

#define HLIST_NULLS_HEAD_INIT(ptr, nulls)       ((ptr)->first = (struct hlist_nulls_node *) (1UL | (((long)nulls) << 1)))
#define hlist_nulls_entry(ptr, type, member)    container_of(ptr, type, member)

// тестирует если указатель не нуль
static inline int is_a_nulls(const struct hlist_nulls_node *ptr)
{
    return ((unsigned long)ptr & 1);
}

// получить "обнуляет" значение на конец цепочки
static inline unsigned long get_nulls_value(const struct hlist_nulls_node *ptr)
{
    return ((unsigned long)ptr) >> 1;
}

static inline int hlist_nulls_unhashed(const struct hlist_nulls_node *h)
{
    return !h->pprev;
}

// проверяет пустой ли список
static inline int hlist_nulls_empty(const struct hlist_nulls_head *h)
{
    return is_a_nulls(h->first);
}

// добавление узла в голову списка
static inline void hlist_nulls_add_head(struct hlist_nulls_node *n, struct hlist_nulls_head *h)
{
    struct hlist_nulls_node *first = h->first;

    n->next = first;
    n->pprev = &h->first;
    h->first = n;
    
    if (!is_a_nulls(first)) first->pprev = &n->next;
}

// удаление узла
static inline void __hlist_nulls_del(struct hlist_nulls_node *n)
{
    struct hlist_nulls_node *next = n->next;
    struct hlist_nulls_node **pprev = n->pprev;
    
    *pprev = next;
    
    if (!is_a_nulls(next)) next->pprev = pprev;
}

static inline void hlist_nulls_del(struct hlist_nulls_node *n)
{
    __hlist_nulls_del(n);
    n->pprev = LIST_POISON_PREV;
}

// перебрать список заданного типа
#define hlist_nulls_for_each_entry(tpos, pos, head, member)\
	for (pos = (head)->first; (!is_a_nulls(pos)) && ({ tpos = hlist_nulls_entry(pos, typeof(*tpos), member); 1;}); pos = pos->next)

// перебрать список данного типа от текущей позиции
#define hlist_nulls_for_each_entry_from(tpos, pos, member)\
	for (; (!is_a_nulls(pos)) && ({ tpos = hlist_nulls_entry(pos, typeof(*tpos), member); 1;}); pos = pos->next)
#endif /* GENERIC_LISTS_LIST_NULLS_H */