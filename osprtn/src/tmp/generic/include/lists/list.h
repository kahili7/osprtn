#ifndef GENERIC_LISTS_LIST_H
#define GENERIC_LISTS_LIST_H

#include <stddef.h>
#include <types.h>
#include <poison.h>

#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

static inline void list_head_init(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void __list_add(struct list_head *n, struct list_head *prev, struct list_head *next)
{
    next->prev = n;
    n->next = next;
    n->prev = prev;
    prev->next = n;
}

// добавление в начало списка
static inline void list_add(struct list_head *n, struct list_head *head)
{
    __list_add(n, head, head->next);
}

// добавление в конец списка
static inline void list_add_tail(struct list_head *n, struct list_head *head)
{
    __list_add(n, head->prev, head);
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void __list_del_entry(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

// удаление элемента из списка
static inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = LIST_POISON_NEXT;
    entry->prev = LIST_POISON_PREV;
}

// заменить элемент в списке на новый
static inline void list_replace(struct list_head *old, struct list_head *n)
{
    n->next = old->next;
    n->next->prev = n;
    n->prev = old->prev;
    n->prev->next = n;
}

// заменить и обнулить старый
static inline void list_replace_init(struct list_head *old, struct list_head *n)
{
    list_replace(old, n);
    list_head_init(old);
}

// удалить и обнулить 
static inline void list_del_init(struct list_head *entry)
{
    __list_del_entry(entry);
    list_head_init(entry);
}

// переместить элемент в начало другого списка 
static inline void list_move(struct list_head *list, struct list_head *head)
{
    __list_del_entry(list);
    list_add(list, head);
}

// переместить элемент в конец другого списка 
static inline void list_move_tail(struct list_head *list, struct list_head *head)
{
    __list_del_entry(list);
    list_add_tail(list, head);
}

// тестирует список
static inline int list_is_last(const struct list_head *list, const struct list_head *head)
{
    return list->next == head;
}

// пустой ли список
static inline int list_empty(const struct list_head *head)
{
    return head->next == head;
}

// проверяет, является ли список пустым и не модифицируется
static inline int list_empty_careful(const struct list_head *head)
{
    struct list_head *next = head->next;
    
    return (next == head) && (next == head->prev);
}

// проверяет, что список имеет только одну запись
static inline int list_is_singular(const struct list_head *head)
{
    return !list_empty(head) && (head->next == head->prev);
}

// сдвиг списка влево
static inline void list_rotate_left(struct list_head *head)
{
    struct list_head *first;

    if (!list_empty(head))
    {
        first = head->next;
        list_move_tail(first, head);
    }
}

static inline void __list_cut_position(struct list_head *list, struct list_head *head, struct list_head *entry)
{
    struct list_head *new_first = entry->next;
    
    list->next = head->next;
    list->next->prev = list;
    list->prev = entry;
    entry->next = list;
    head->next = new_first;
    new_first->prev = head;
}

// вырезает список и вставляет в другой
static inline void list_cut_position(struct list_head *list, struct list_head *head, struct list_head *entry)
{
    if (list_empty(head)) return;
    if (list_is_singular(head) && (head->next != entry && head != entry)) return;
    if (entry == head) list_head_init(list);
    else __list_cut_position(list, head, entry);
}

static inline void __list_splice(const struct list_head *list, struct list_head *prev, struct list_head *next)
{
    struct list_head *first = list->next;
    struct list_head *last = list->prev;

    first->prev = prev;
    prev->next = first;

    last->next = next;
    next->prev = last;
}

// соединяет два списка (по методу стека)
static inline void list_splice(const struct list_head *list, struct list_head *head)
{
    if (!list_empty(list)) __list_splice(list, head, head->next);
}

// соединяет два списка (по методу очереди)
static inline void list_splice_tail(struct list_head *list, struct list_head *head)
{
    if (!list_empty(list)) __list_splice(list, head->prev, head);
}

// соединяет два списка (по методу стека) и заново инициализирует старый
static inline void list_splice_init(struct list_head *list, struct list_head *head)
{
    if (!list_empty(list))
    {
        __list_splice(list, head, head->next);
        list_head_init(list);
    }
}

// соединяет два списка (по методу очереди) и заново инициализирует старый
static inline void list_splice_tail_init(struct list_head *list, struct list_head *head)
{
    if (!list_empty(list))
    {
        __list_splice(list, head->prev, head);
        list_head_init(list);
    }
}

// возвращает структуру записи
#define list_entry(ptr, type, member)   container_of(ptr, type, member)

// возвращает первый элемент из списка
#define list_first_entry(ptr, type, member) list_entry((ptr)->next, type, member)
// если пустой возвращает NULL
#define list_first_entry_or_null(ptr, type, member) (!list_empty(ptr) ? list_first_entry(ptr, type, member) : NULL)

// возвращает следующий элемент из списка
#define list_next_entry(pos, member) list_entry((pos)->member.next, typeof(*(pos)), member)
// возвращает предыдущий элемент из списка
#define list_prev_entry(pos, member) list_entry((pos)->member.prev, typeof(*(pos)), member)

// поиск элемента вперед
#define list_for_each(pos, head)        for (pos = (head)->next; pos != (head); pos = pos->next)
// поиск элемента назад
#define list_for_each_prev(pos, head)   for (pos = (head)->prev; pos != (head); pos = pos->prev)

// безопасный поиск элемента вперед, защищен от удаления записи из списка
#define list_for_each_safe(pos, n, head)        for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)
// безопасный поиск элемента назад, защищен от удаления записи из списка
#define list_for_each_prev_safe(pos, n, head)   for (pos = (head)->prev, n = pos->prev; pos != (head); pos = n, n = pos->prev)

// перебрать список заданного типа вперед
#define list_for_each_entry(pos, head, member)\
    for (pos = list_entry((head)->next, typeof(*pos), member);\
        &pos->member != (head); pos = list_entry(pos->member.next, typeof(*pos), member))
//перебрать список заданного типа назад
#define list_for_each_entry_reverse(pos, head, member)\
    for (pos = list_entry((head)->prev, typeof(*pos), member);\
        &pos->member != (head); pos = list_entry(pos->member.prev, typeof(*pos), member))

// подготовка pos
#define list_prepare_entry(pos, head, member)   ((pos) ? : list_entry(head, typeof(*pos), member))

// продолжить итерацию для список заданного типа вперед
#define list_for_each_entry_continue(pos, head, member)\
    for (pos = list_entry(pos->member.next, typeof(*pos), member);\
        &pos->member != (head); pos = list_entry(pos->member.next, typeof(*pos), member))
// продолжить итерацию для список заданного типа назад
#define list_for_each_entry_continue_reverse(pos, head, member)\
    for (pos = list_entry(pos->member.prev, typeof(*pos), member);\
        &pos->member != (head); pos = list_entry(pos->member.prev, typeof(*pos), member))

// перебрать список заданного типа из текущего вперед
#define list_for_each_entry_from(pos, head, member)\
    for (; &pos->member != (head);\
        pos = list_entry(pos->member.next, typeof(*pos), member))
// перебрать список заданного типа из текущего вперед, защищен от удаления записи из списка
#define list_for_each_entry_safe_from(pos, n, head, member)\
    for (n = list_entry(pos->member.next, typeof(*pos), member);\
        &pos->member != (head); pos = n, n = list_entry(n->member.next, typeof(*n), member))

// перебрать список данного типа вперед, защищен от удаления записи из списка
#define list_for_each_entry_safe(pos, n, head, member)\
    for (pos = list_entry((head)->next, typeof(*pos), member), n = list_entry(pos->member.next, typeof(*pos), member);\
        &pos->member != (head); pos = n, n = list_entry(n->member.next, typeof(*n), member))
// продолжить список итерации, защищен от удаления записи из списка
#define list_for_each_entry_safe_continue(pos, n, head, member)\
    for (pos = list_entry(pos->member.next, typeof(*pos), member), n = list_entry(pos->member.next, typeof(*pos), member);\
        &pos->member != (head); pos = n, n = list_entry(n->member.next, typeof(*n), member))
// перебрать список данного типа назад, защищен от удаления записи из списка
#define list_for_each_entry_safe_reverse(pos, n, head, member)\
    for (pos = list_entry((head)->prev, typeof(*pos), member), n = list_entry(pos->member.prev, typeof(*pos), member);\
        &pos->member != (head); pos = n, n = list_entry(n->member.prev, typeof(*n), member))

// сброс старого элемента
#define list_safe_reset_next(pos, n, member)    n = list_entry(pos->member.next, typeof(*pos), member)

#define HLIST_HEAD_INIT { .first = NULL }
#define HLIST_HEAD(name) struct hlist_head name = { .first = NULL }
#define init_hlist_head(ptr) ((ptr)->first = NULL)

static inline void init_hlist_node(struct hlist_node *h)
{
    h->next = NULL;
    h->pprev = NULL;
}

static inline int hlist_unhashed(const struct hlist_node *h)
{
    return !h->pprev;
}

// проверка на пустой список
static inline int hlist_empty(const struct hlist_head *h)
{
    return !h->first;
}

// удаление из списка
static inline void __hlist_del(struct hlist_node *n)
{
    struct hlist_node *next = n->next;
    struct hlist_node **pprev = n->pprev;
    
    *pprev = next;
    
    if (next) next->pprev = pprev;
}

static inline void hlist_del(struct hlist_node *n)
{
    __hlist_del(n);
    n->next = LIST_POISON_NEXT;
    n->pprev = LIST_POISON_PREV;
}

// удалить и обнулить 
static inline void hlist_del_init(struct hlist_node *n)
{
    if (!hlist_unhashed(n))
    {
        __hlist_del(n);
        init_hlist_node(n);
    }
}

// добавление в начало списка
static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    struct hlist_node *first = h->first;
    
    n->next = first;
    
    if (first) first->pprev = &n->next;
    
    h->first = n;
    n->pprev = &h->first;
}

// добавление перед текущего элемента
static inline void hlist_add_before(struct hlist_node *n, struct hlist_node *next)
{
    n->pprev = next->pprev;
    n->next = next;
    next->pprev = &n->next;
    *(n->pprev) = n;
}

// добавление после текущего элемента
static inline void hlist_add_after(struct hlist_node *n, struct hlist_node *next)
{
    next->next = n->next;
    n->next = next;
    next->pprev = &n->next;

    if(next->next) next->next->pprev  = &next->next;
}

static inline void hlist_add_fake(struct hlist_node *n)
{
    n->pprev = &n->next;
}

// перемещение списка
static inline void hlist_move_list(struct hlist_head *old, struct hlist_head *n)
{
    n->first = old->first;
    
    if (n->first) n->first->pprev = &n->first;
    
    old->first = NULL;
}

// возвращает структуру записи
#define hlist_entry(ptr, type, member)  container_of(ptr, type, member)
// возвращает структуру записи, защищен от удаления записи из списка
#define hlist_entry_safe(ptr, type, member) ({ typeof(ptr) ____ptr = (ptr); ____ptr ? hlist_entry(____ptr, type, member) : NULL;})

// поиск элемента вперед
#define hlist_for_each(pos, head)           for (pos = (head)->first; pos ; pos = pos->next)
// поиск элемента вперед, защищен от удаления записи из списка
#define hlist_for_each_safe(pos, n, head)   for (pos = (head)->first; pos && ({ n = pos->next; 1; }); pos = n)

// перебрать список заданного типа вперед
#define hlist_for_each_entry(pos, head, member)\
    for (pos = hlist_entry_safe((head)->first, typeof(*(pos)), member);\
        pos; pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member))

// продолжить итерацию для список заданного типа вперед
#define hlist_for_each_entry_continue(pos, member)\
    for (pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member);\
        pos; pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member))

// перебрать список заданного типа из текущего вперед
#define hlist_for_each_entry_from(pos, member)  for (; pos; pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member))
// перебрать список данного типа вперед, защищен от удаления записи из списка
#define hlist_for_each_entry_safe(pos, n, head, member)\
    for (pos = hlist_entry_safe((head)->first, typeof(*pos), member);\
        pos && ({ n = pos->member.next; 1; }); pos = hlist_entry_safe(n, typeof(*pos), member))
#endif /* GENERIC_LISTS_LIST_H */