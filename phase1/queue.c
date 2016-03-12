#include "queue.h"
#include "clist.h"
#include "types.h"

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
    struct pcb_t *scan;
    void *tmp = NULL;

    if (clist_delete(p, q, p_siblings)) {
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
