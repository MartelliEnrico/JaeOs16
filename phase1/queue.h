#pragma once

#include "process.h"

void insertProcQ(struct clist *, struct pcb_t *);
struct pcb_t *removeProcQ(struct clist *);
struct pcb_t *outProcQ(struct clist *, struct pcb_t *);
struct pcb_t *headProcQ(struct clist *);