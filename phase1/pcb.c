#include "pcb.h"

#include "types.h"
#include "clist.h"

static struct clist pcbFree;

void initPcbs() {
    static struct pcb_t pcbTable[MAXPROC];
    int i;

    for (i = 0; i < MAXPROC; i++) {
        clist_enqueue(&pcbTable[i], &pcbFree, p_list);
    }
}

struct pcb_t *allocPcb() {
    if (clist_empty(pcbFree)) {
        return NULL;
    }

    struct pcb_t *elem = clist_head(elem, pcbFree, p_list);
    clist_dequeue(&pcbFree);

    // Reset all struct parameters to defaults value to prevent data leaks
    // and unexpected behaviours.
    elem->p_parent = NULL;
    elem->p_cursem = NULL;
    elem->p_list = CLIST_INIT;
    elem->p_children = CLIST_INIT;
    elem->p_siblings = CLIST_INIT;

    return elem;
}

void freePcb(struct pcb_t *p) {
    clist_enqueue(p, &pcbFree, p_list);
}

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

void insertProcQ(struct clist *q, struct pcb_t *p) {
    clist_enqueue(p, q, p_siblings);
}

struct pcb_t *removeProcQ(struct clist *q) {
    if (clist_empty(*q)) {
        return NULL;
    }

    struct pcb_t *elem = clist_head(elem, *q, p_siblings);
    clist_dequeue(q);

    return elem;
}

struct pcb_t *outProcQ(struct clist *q, struct pcb_t *p) {
    if (clist_delete(p, q, p_siblings) == 0) {
        return p;
    }

    return NULL;
}

struct pcb_t *headProcQ(struct clist *q) {
    if (clist_empty(*q)) {
        return NULL;
    }

    struct pcb_t *elem = clist_head(elem, *q, p_siblings);

    return elem;
}