#include "semaphore.h"

void initASL() {
    static struct semd_t semdTable[MAXPROC];

    // @TODO: implement initASL
}

int insertBlocked(int *semAdd, struct pcb_t *p) {
    // @TODO: implement insertBlocked
}

struct pcb_t *removeBlocked(int *semAdd) {
    // @TODO: implement removeBlocked
}

struct pcb_t *outBlocked(struct pcb_t *p) {
    // @TODO: implement outBlocked
}

struct pcb_t *headBlocked(int *semAdd) {
    // @TODO: implement headBlocked
}
