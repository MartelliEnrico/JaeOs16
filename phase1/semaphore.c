#include "semaphore.h"

void initASL() {
    static struct semd_t semdTable[MAXPROC];
    int i;

    for (i = 0; i < MAXPROC; i++) {
        clist_enqueue(&semdTable[i], &semdFree, s_link);
    }
}

static inline struct semd_t *__newSemdFromList(struct semd_t *elem, int *semAdd, struct pcb_t *p) {
    elem = clist_head(elem, semdFree, s_link);
    clist_dequeue(&semdFree);

    elem->s_semAdd = semAdd;
    elem->s_procq = CLIST_INIT;

    clist_enqueue(p, &(elem->s_procq), p_list);
}

int insertBlocked(int *semAdd, struct pcb_t *p) {
    struct semd_t *scan;
    void *tmp = NULL;

    clist_foreach(scan, &aslh, s_link, tmp) {
        if (semAdd == scan->s_semAdd) {
            clist_enqueue(p, &(scan->s_procq), p_list);
            break;
        }

        if (semAdd < scan->s_semAdd) {
            if (clist_empty(semdFree)) {
                return TRUE;
            }

            struct semd_t *elem;
            __newSemdFromList(elem, semAdd, p);

            clist_foreach_add(elem, scan, &aslh, s_link, tmp);
            break;
        }
    }

    if (clist_foreach_all(scan, &aslh, s_link, tmp)) {
        if (clist_empty(semdFree)) {
            return TRUE;
        }

        struct semd_t *elem;
        __newSemdFromList(elem, semAdd, p);

        clist_enqueue(elem, &aslh, s_link);
    }

    return FALSE;
}

struct pcb_t * removeBlocked(int *semAdd) {
    struct semd_t *scan;
    void *tmp = NULL;

    clist_foreach(scan, &aslh, s_link, tmp) {
        if (semAdd == scan->s_semAdd) {
            struct pcb_t *elem;
            elem = clist_head(elem, scan->s_procq, p_list);
            clist_dequeue(&(scan->s_procq));

            if (clist_empty(scan->s_procq)) {
                clist_foreach_delete(scan, &aslh, s_link, tmp);
                clist_enqueue(scan, &semdFree, s_link);
            }

            return elem;
        }
    }

    return NULL;
}

struct pcb_t *outBlocked(struct pcb_t *p) {
    // @TODO: implement outBlocked
}

struct pcb_t *headBlocked(int *semAdd) {
    struct semd_t *scan;
    void *tmp = NULL;

    clist_foreach(scan, &aslh, s_link, tmp) {
        if (semAdd == scan->s_semAdd) {
            if (clist_empty(scan->s_procq)) {
                return NULL;
            }

            struct pcb_t *elem;

            return clist_head(elem, scan->s_procq, p_list);
        }
    }

    return NULL;
}
