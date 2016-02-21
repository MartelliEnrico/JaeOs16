#include "semaphore.h"
#include "clist.h"
#include "types.h"

static struct clist semdFree;

static struct clist aslh;

void initASL() {
    static struct semd_t semdTable[MAXPROC];
    int i;

    for (i = 0; i < MAXPROC; i++) {
        clist_enqueue(&semdTable[i], &semdFree, s_link);
    }
}

int insertBlocked(int *semAdd, struct pcb_t *p) {
    struct semd_t *scan;
    void *tmp = NULL;

    struct semd_t * getSemaphoreAndInit() {
        struct semd_t *elem = clist_head(elem, semdFree, s_link);
        clist_dequeue(&semdFree);

        // Reset parameters to default values.
        elem->s_semAdd = semAdd;
        elem->s_procq = CLIST_INIT;

        p->p_cursem = elem;
        clist_enqueue(p, &(elem->s_procq), p_list);

        return elem;
    }

    clist_foreach(scan, &aslh, s_link, tmp) {
        if (semAdd == scan->s_semAdd) {
            p->p_cursem = scan;
            clist_enqueue(p, &(scan->s_procq), p_list);
            break;
        }

        if (semAdd < scan->s_semAdd) {
            if (clist_empty(semdFree)) {
                return TRUE;
            }

            clist_foreach_add(getSemaphoreAndInit(), scan, &aslh, s_link, tmp);
            break;
        }
    }

    if (clist_foreach_all(scan, &aslh, s_link, tmp)) {
        if (clist_empty(semdFree)) {
            return TRUE;
        }

        clist_enqueue(getSemaphoreAndInit(), &aslh, s_link);
    }

    return FALSE;
}

struct pcb_t * removeBlocked(int *semAdd) {
    struct semd_t *scan;
    void *tmp = NULL;

    clist_foreach(scan, &aslh, s_link, tmp) {
        if (semAdd == scan->s_semAdd) {
            struct pcb_t *elem = clist_head(elem, scan->s_procq, p_list);
            clist_dequeue(&(scan->s_procq));

            if (clist_empty(scan->s_procq)) {
                // Move semaphore from the active list, to the free list.
                clist_foreach_delete(scan, &aslh, s_link, tmp);
                clist_enqueue(scan, &semdFree, s_link);
            }

            elem->p_cursem = NULL;

            return elem;
        }
    }

    return NULL;
}

struct pcb_t *outBlocked(struct pcb_t *p) {
    if (p->p_cursem == NULL) {
        return NULL;
    }

    clist_delete(p, &(p->p_cursem->s_procq), p_list);

    if (clist_empty(p->p_cursem->s_procq)) {
        // Move semaphore from the active list, to the free list.
        clist_delete(p->p_cursem, &aslh, s_link);
        clist_enqueue(p->p_cursem, &semdFree, s_link);
    }

    p->p_cursem = NULL;

    return p;
}

struct pcb_t *headBlocked(int *semAdd) {
    struct semd_t *scan;
    void *tmp = NULL;

    clist_foreach(scan, &aslh, s_link, tmp) {
        if (semAdd == scan->s_semAdd) {
            if (clist_empty(scan->s_procq)) {
                return NULL;
            }

            struct pcb_t *elem = clist_head(elem, scan->s_procq, p_list);

            return elem;
        }
    }

    return NULL;
}
