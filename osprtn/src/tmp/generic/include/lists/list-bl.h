#ifndef GENERIC_LISTS_LIST_BL_H
#define GENERIC_LISTS_LIST_BL_H

#include <lists/list.h>
#include <sync/bit-spinlock.h>

/*
 * cпециальная версия списков, где голова списка имеет блокировку младший бит
 */

#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
    #define LIST_BL_LOCKMASK    1UL
#else
    #define LIST_BL_LOCKMASK    0UL
#endif

#ifdef CONFIG_DEBUG_LIST
    #define LIST_BL_BUG_ON(x) BUG_ON(x)
#else
    #define LIST_BL_BUG_ON(x)
#endif

struct hlist_bl_head {
    struct hlist_bl_node *first;
};

struct hlist_bl_node {
    struct hlist_bl_node *next, **pprev;
};

#define HLIST_BL_HEAD_INIT(ptr) ((ptr)->first = NULL)
#define hlist_bl_entry(ptr, type, member) container_of(ptr, type, member)

static inline void hlist_bl_node_init(struct hlist_bl_node *h)
{
    h->next = NULL;
    h->pprev = NULL;
}

// установить первый элемент
static inline struct hlist_bl_node *hlist_bl_first(struct hlist_bl_head *h)
{
    return (struct hlist_bl_node *)((unsigned long)h->first & ~LIST_BL_LOCKMASK);
}

static inline int hlist_bl_unhashed(const struct hlist_bl_node *h)
{
    return !h->pprev;
}

// установить первый элемент в список и установка бита блокировки
static inline void hlist_bl_set_first(struct hlist_bl_head *h, struct hlist_bl_node *n)
{
    LIST_BL_BUG_ON((unsigned long)n & LIST_BL_LOCKMASK);
    LIST_BL_BUG_ON(((unsigned long)h->first & LIST_BL_LOCKMASK) != LIST_BL_LOCKMASK);
    h->first = (struct hlist_bl_node *)((unsigned long)n | LIST_BL_LOCKMASK);
}

// первый элемент пустой
static inline int hlist_bl_empty(const struct hlist_bl_head *h)
{
    return !((unsigned long)h->first & ~LIST_BL_LOCKMASK);
}

// добавление узла в голову списка
static inline void hlist_bl_add_head(struct hlist_bl_node *n, struct hlist_bl_head *h)
{
	struct hlist_bl_node *first = hlist_bl_first(h);

	n->next = first;
        
	if (first) first->pprev = &n->next;
        
	n->pprev = &h->first;
	hlist_bl_set_first(h, n);
}

// удаление узла
static inline void __hlist_bl_del(struct hlist_bl_node *n)
{
    struct hlist_bl_node *next = n->next;
    struct hlist_bl_node **pprev = n->pprev;

    LIST_BL_BUG_ON((unsigned long)n & LIST_BL_LOCKMASK);
    *pprev = (struct hlist_bl_node *)((unsigned long)next | ((unsigned long)*pprev & LIST_BL_LOCKMASK));
    
    if (next) next->pprev = pprev;
}

static inline void hlist_bl_del(struct hlist_bl_node *n)
{
    __hlist_bl_del(n);
    n->next = LIST_POISON_NEXT;
    n->pprev = LIST_POISON_PREV;
}

static inline void hlist_bl_del_init(struct hlist_bl_node *n)
{
    if (!hlist_bl_unhashed(n))
    {
        __hlist_bl_del(n);
        HLIST_BL_HEAD_INIT(n);
    }
}

static inline void hlist_bl_lock(struct hlist_bl_head *b)
{
    bit_spin_lock(0, (unsigned long *)b);
}

static inline void hlist_bl_unlock(struct hlist_bl_head *b)
{
    __bit_spin_unlock(0, (unsigned long *)b);
}

static inline bool hlist_bl_is_locked(struct hlist_bl_head *b)
{
    return bit_spin_is_locked(0, (unsigned long *)b);
}

// перебрать список заданного типа
#define hlist_bl_for_each_entry(tpos, pos, head, member)\
        for (pos = hlist_bl_first(head); pos && ({ tpos = hlist_bl_entry(pos, typeof(*tpos), member); 1;}); pos = pos->next)

// перебрать список данного типа защищены от удаления записи из списка
#define hlist_bl_for_each_entry_safe(tpos, pos, n, head, member)\
        for (pos = hlist_bl_first(head); pos && ({ n = pos->next; 1; }) && ({ tpos = hlist_bl_entry(pos, typeof(*tpos), member); 1;}); pos = n)

#endif /* GENERIC_LISTS_LIST_BL_H */