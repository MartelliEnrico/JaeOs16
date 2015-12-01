#pragma once

#include "process.h"

static struct semd_t semdTable[MAXPROC];

void initASL();
int insertBlocked(int *, struct pcb_t *);
struct pcb_t *removeBlocked(int *);
struct pcb_t *outBlocked(struct pcb_t *);
struct pcb_t *headBlocked(int *);