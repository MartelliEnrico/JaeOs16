#pragma once

#include "const.h"
#include "types.h"

#include "queue.h"
#include "tree.h"
#include "semaphore.h"

static struct clist pcbFree[MAXPROC];

void initPcbs();
struct pcb_t *allocPcb();
void freePcb(struct pcb_t *);