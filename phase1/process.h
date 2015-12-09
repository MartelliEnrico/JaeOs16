#pragma once

#include "const.h"
#include "types.h"

#include "queue.h"
#include "tree.h"
#include "semaphore.h"

/*
 * Function: initPcbs
 * ------------------
 * Initialize the pcbFree array with MAXPROC empty elements
 */
void initPcbs();

/*
 * Function: allocPcb
 * ------------------
 * Allocate a new ProcBlk from the pcbFree array
 *
 * returns: NULL if the pcbFree array is empty,
 *          pointer to ProcBlk
 */
struct pcb_t *allocPcb();

/*
 * Function: pcbFree
 * -----------------
 * Return unused ProcBlk to the pcbFree array
 *
 * p: ProcBlk pointer to free
 */
void freePcb(struct pcb_t *p);