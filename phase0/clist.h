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

#define in(name) struct clist name

/* constant used to initialize an empty list */
#define CLIST_INIT {NULL}

/* add the structure pointed to by elem as the last element of a circular list */
/* clistp is the address of the tail pointer (struct clist *) */
/* member is the field of *elem used to link this list */
#define clist_enqueue(elem, clistp, member) do { \
    if(clist_empty(*(clistp))) { \
        (elem)->member.next = &((elem)->member); \
    } else { \
        (elem)->member.next = (clistp)->next->next; \
        (clistp)->next->next = &((elem)->member); \
    } \
    (clistp)->next = &((elem)->member); \
} while (0)

/* add the structure pointed to by elem as the first element of a circular list */
/* clistp is the address of the tail pointer (struct clist *) */
/* member is the field of *elem used to link this list */
#define clist_push(elem, clistp, member) do { \
    if(clist_empty(*(clistp))) { \
        (elem)->member.next = &((elem)->member); \
        (clistp)->next = &((elem)->member); \
    } else { \
        (elem)->member.next = (clistp)->next->next; \
        (clistp)->next->next = &((elem)->member); \
    } \
} while (0)

/* clist_empty returns true in the circular list is empty, false otherwise */
/* clistx is a struct clist */
#define clist_empty(clistx) (((clistx).next)==NULL)

/* return the pointer of the first element of the circular queue.
     elem is also an argument to retrieve the type of the element */
/* member is the field of *elem used to link this list */
#define clist_head(elem, clistx, member) container_of((clistx).next->next, typeof(*(elem)), member)

/* return the pointer of the last element of the circular queue.
     elem is also an argument to retrieve the type of the element */
/* member is the field of *elem used to link this list */
#define clist_tail(elem, clistx, member) container_of((clistx).next, typeof(*(elem)), member)

#define clist_next(elem, member) container_of((elem)->member.next, typeof(*(elem)), member)

/* clist_pop and clist__dequeue are synonyms */
/* delete the first element of the list (this macro does not return any value) */
/* clistp is the address of the tail pointer (struct clist *) */
#define clist_pop(clistp) clist_dequeue(clistp)
#define clist_dequeue(clistp) ({int ret = 0; \
    if(clist_empty(*(clistp))) { \
        ret = 1; \
    } else if((clistp)->next == (clistp)->next->next) { \
        (clistp)->next = NULL; \
    } else { \
        (clistp)->next->next = (clistp)->next->next->next; \
    } \
    ret;})

/* delete from a circular list the element whose pointer is elem */
/* clistp is the address of the tail pointer (struct clist *) */
/* member is the field of *elem used to link this list */
#define clist_delete(elem, clistp, member)

/* this macro has been designed to be used as a for instruction,
     the instruction (or block) following clist_foreach will be repeated for each element
     of the circular list. elem will be assigned to each element */
/* clistp is the address of the tail pointer (struct clist *) */
/* member is the field of *elem used to link this list */
/* tmp is a void * temporary variable */
#define clist_foreach(scan, clistp, member, tmp) if(!clist_empty(*(clistp))) \
    for((scan) = clist_head(scan, *(clistp), member), (tmp) = clist_tail(scan, *(clistp), member); ; \
        ({if(&(scan)->member == (clistp)->next) break; \
            else (tmp) = (scan), (scan) = clist_next(scan, member);}))

/* this macro should be used after the end of a clist_foreach cycle
     using the same args. it returns false if the cycle terminated by a break,
     true if it scanned all the elements */
#define clist_foreach_all(scan, clistp, member, tmp) &(scan)->member != (clistp)->next

/* this macro should be used *inside* a clist_foreach loop to delete the
     current element */
#define clist_foreach_delete(scan, clistp, member, tmp) ((typeof(scan))(tmp))->member.next = (scan)->member.next

/* this macro should be used *inside* a clist_foreach loop to add an element
    before the current one */
#define clist_foreach_add(elem, scan, clistp, member, tmp) do { \
    ((typeof(scan))(tmp))->member.next = &(elem)->member; \
    (elem)->member.next = &(scan)->member; \
} while (0)

#endif
