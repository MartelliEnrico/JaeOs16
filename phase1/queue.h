#pragma once

#include "process.h"

/*
 * Function: inserProcQ
 * --------------------
 * Insert the ProcBlk p into the list (q)
 *
 * q: tail pointer to a list of ProcBlk
 * p: pointer to ProcBlk to insert inside the list
 */
void insertProcQ(struct clist *q, struct pcb_t *p);

/*
 * Function: removeProcQ
 * ---------------------
 * Remove the first element from the list (q)
 *
 * q: tail pointer to a list of ProcBlk
 *
 * returns: NULL if the list is empty,
 *          the pointer of the removed ProcBlk
 */
struct pcb_t *removeProcQ(struct clist *q);

/*
 * Function: outProcQ
 * ------------------
 * Remove the ProcBlk (p) from the list (q)
 *
 * q: tail pointer to a list of ProcBlk
 * p: pointer to ProcBlk to insert inside the list
 *
 * returns: NULL if the element is not in the list,
 *          otherwise p
 */
struct pcb_t *outProcQ(struct clist *q, struct pcb_t *p);

/*
 * Function: headProcQ
 * -------------------
 * Return the first element of the list (q)
 *
 * q: tail pointer to a list of ProcBlk
 *
 * returns: NULL if the list is empty,
 *          the pointer of the first ProcBlk
 */
struct pcb_t *headProcQ(struct clist *q);