#pragma once

#include "process.h"

int emptyChild(struct pcb_t *);
void insertChild(struct pcb_t *, struct pcb_t *);
struct pcb_t *removeChild(struct pcb_t *);
struct pcb_t *outChild(struct pcb_t *);