#include "process.h"

static struct clist pcbFree;

void initPcbs() {
    static struct pcb_t pcbTable[MAXPROC];

    // @TODO: implement initPcbs
}

struct pcb_t *allocPcb() {
    // @TODO: implement allocPcb
}

void freePcb(struct pcb_t *p) {
    // @TODO: implement freePcb
}