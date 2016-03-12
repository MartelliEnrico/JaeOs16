#include "tree.h"
#include "clist.h"
#include "types.h"

int emptyChild(struct pcb_t *p) {
    return clist_empty(p->p_children) ? TRUE : FALSE;
}

void insertChild(struct pcb_t *parent, struct pcb_t *p) {
    clist_enqueue(p, &(parent->p_children), p_siblings);
    p->p_parent = parent;
}

struct pcb_t *removeChild(struct pcb_t *p) {
    if (clist_empty(p->p_children)) {
        return NULL;
    }

    struct pcb_t *elem = clist_head(elem, p->p_children, p_siblings);
    clist_dequeue(&(p->p_children));

    elem->p_parent = NULL;

    return elem;
}

struct pcb_t *outChild(struct pcb_t *p) {
    if (clist_delete(p, &(p->p_parent->p_children), p_siblings) == 0) {
        p->p_parent = NULL;

        return p;
    }

    return NULL;
}
