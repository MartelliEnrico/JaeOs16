#ifndef _CLIST_H
#define _CLIST_H

//typedef unsigned int    size_t;

#define container_of(ptr, type, member) ({      \
            const typeof( ((type *)0)->member ) *__mptr = (ptr);  \
            (type *)( (char *)__mptr - offsetof(type,member) );})

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

/* struct clist definition. It is at the same time the type of the tail
     pointer of the circular list and the type of field used to link the elements */
struct clist {
    struct clist *next;
};

#define in(...) struct clist __VA_ARGS__

/* constant used to initialize an empty list */
#define CLIST_INIT {NULL}

/* clist_empty returns true in the circular list is empty, false otherwise */
/* clistx is a struct clist */
#define clist_empty(clistx) ((clistx).next == NULL)

static inline void __clist_add(struct clist *elem, struct clist* list) {
    if (clist_empty(*list)) {
        elem->next = elem;
    } else {
        elem->next = list->next->next;
        list->next->next = elem;
    }
}

/* add the structure pointed to by elem as the last element of a circular list */
/* clistp is the address of the tail pointer (struct clist *) */
/* member is the field of *elem used to link this list */
#define clist_enqueue(elem, clistp, member) __clist_enqueue(&((elem)->member), clistp)

static inline void __clist_enqueue(struct clist *elem, struct clist* list) {
    __clist_add(elem, list);
    list->next = elem;
}

/* add the structure pointed to by elem as the first element of a circular list */
/* clistp is the address of the tail pointer (struct clist *) */
/* member is the field of *elem used to link this list */
#define clist_push(elem, clistp, member) __clist_push(&((elem)->member), clistp)

static inline void __clist_push(struct clist *elem, struct clist *list) {
    __clist_add(elem, list);
    if (clist_empty(*list)) {
        list->next = elem;
    }
}

/* return the pointer of the first element of the circular queue.
     elem is also an argument to retrieve the type of the element */
/* member is the field of *elem used to link this list */
#define clist_head(elem, clistx, member) container_of((clistx).next->next, typeof(*(elem)), member)

#define clist_head_safe(elem, clistx, member) ({(clistx).next != NULL && (clistx).next->next ? \
    clist_head(elem, clistx, member) : NULL;})

/* return the pointer of the last element of the circular queue.
     elem is also an argument to retrieve the type of the element */
/* member is the field of *elem used to link this list */
#define clist_tail(elem, clistx, member) container_of((clistx).next, typeof(*(elem)), member)

#define clist_tail_safe(elem, clistx, member) ({(clistx).next != NULL ? \
    clist_tail(elem, clistx, member) : NULL;})

#define clist_next(elem, member) container_of((elem)->member.next, typeof(*(elem)), member)

/* clist_pop and clist__dequeue are synonyms */
/* delete the first element of the list (this macro does not return any value) */
/* clistp is the address of the tail pointer (struct clist *) */
#define clist_pop(clistp) clist_dequeue(clistp)
#define clist_dequeue(clistp) __clist_dequeue(clistp)

static inline void __clist_dequeue(struct clist *list) {
    if (clist_empty(*list)) return;
    if (list->next == list->next->next) {
        list->next = NULL;
    } else {
        list->next->next = list->next->next->next;
    }
}

/* delete from a circular list the element whose pointer is elem */
/* clistp is the address of the tail pointer (struct clist *) */
/* member is the field of *elem used to link this list */
#define clist_delete(elem, clistp, member) __clist_delete_first(&((elem)->member), clistp)

static inline int __clist_delete(struct clist *elem, struct clist *list, struct clist *head) {
    if (list->next == head) return 1;
    if (list->next->next == elem) {
        list->next->next = list->next->next->next;
        return 0;
    }
    return __clist_delete(elem, list->next, head);
}

static inline int __clist_delete_first(struct clist *elem, struct clist *list) {
    if (clist_empty(*list)) return 1;
    if (list->next == list->next->next) {
        if (list->next == elem) {
            list->next = NULL;
            return 0;
        }
        return 1;
    }
    return __clist_delete(elem, list->next, list);
}

/* this macro has been designed to be used as a for instruction,
     the instruction (or block) following clist_foreach will be repeated for each element
     of the circular list. elem will be assigned to each element */
/* clistp is the address of the tail pointer (struct clist *) */
/* member is the field of *elem used to link this list */
/* tmp is a void * temporary variable */
#define clist_foreach(scan, clistp, member, tmp) if(!clist_empty(*(clistp))) \
    for((scan) = clist_head(scan, *(clistp), member), (tmp) = (clistp)->next; ; \
        ({if(clist_empty(*(clistp)) || &(scan)->member == (clistp)->next) {(tmp) = NULL; break;} \
            else (tmp) = &((scan)->member), (scan) = clist_next(scan, member);}))

/* this macro should be used after the end of a clist_foreach cycle
     using the same args. it returns false if the cycle terminated by a break,
     true if it scanned all the elements */
#define clist_foreach_all(scan, clistp, member, tmp) clist_empty(*(clistp)) || (tmp) == NULL

/* this macro should be used *inside* a clist_foreach loop to delete the
     current element */
#define clist_foreach_delete(scan, clistp, member, tmp) __clist_foreach_delete(&((scan)->member), clistp, (struct clist *)(tmp))

static inline void __clist_foreach_delete(struct clist *scan, struct clist *list, struct clist *tmp) {
    if (list->next == list->next->next) {
        list->next = NULL;
    } else {
        tmp->next = scan->next;
    }
}

/* this macro should be used *inside* a clist_foreach loop to add an element
    before the current one */
#define clist_foreach_add(elem, scan, clistp, member, tmp) __clist_foreach_add(&((elem)->member), &((scan)->member), (struct clist *)(tmp))

static inline void __clist_foreach_add(struct clist *elem, struct clist *scan, struct clist *tmp) {
    elem->next = scan;
    tmp->next = elem;
    tmp = elem;
}

#endif
