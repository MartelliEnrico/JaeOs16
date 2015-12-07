#include "process.h"

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

    struct pcb_t *elem;
    elem = clist_head(elem, pcbFree, p_list);
    clist_dequeue(&pcbFree);

    elem->p_parent = NULL;
    elem->p_cursem = NULL;
    elem->p_s = NULL;
    elem->p_list = CLIST_INIT;
    elem->p_children = CLIST_INIT;
    elem->p_siblings = CLIST_INIT;

    return elem;
}

void freePcb(struct pcb_t *p) {
    clist_enqueue(p, &pcbFree, p_list);
}