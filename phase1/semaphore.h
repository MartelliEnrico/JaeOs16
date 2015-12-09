#pragma once

#include "process.h"

/*
 * Function: initASL
 * -----------------
 * Initialize the semdTable array with MAXPROC empty elements
 */
void initASL();

/*
 * Function: insertBlocked
 * -----------------------
 * Insert ProcBlk (p) as the tail of the queue associated with the
 * semaphore (semAdd), and set the semaphore address of (p) to
 * (semAdd).
 * If the semaphore is currently not active (no descriptor inside
 * ASL), allocate a new one from semdTable, initialize it and procede
 * as usual.
 *
 * semAdd: pointer to a semaphore
 * p: pointer to a ProcBlk
 *
 * returns: TRUE if you need to allocate and semdTable is empty,
 *          FALSE otherwise
 */
int insertBlocked(int *semAdd, struct pcb_t *p);

/*
 * Function: removeBlocked
 * -----------------------
 * Search the ASL for a descriptor of this semaphore. If found,
 * remove the head ProcBlk from the process queue of the found
 * semaphore descriptor and return a pointer to it.
 * If the process queue become empty, remove the sempahore
 * descriptor from the ASL, and return it to semdFree list.
 *
 * semAdd: pointer to a semaphore
 *
 * returns: NULL if the head process is not found,
 *          pointer to ProcBlk head of the address queue
 */
struct pcb_t *removeBlocked(int *semAdd);

/*
 * Function: outBlocked
 * --------------------
 * Remove the ProcBlk (p) from the process queue associated
 * with (p) semaphore on the ASL.
 *
 * p: pointer to a ProcBlk
 *
 * returns: NULL if the ProcBlk (p) is not found,
 *          (p) otherwise
 */
struct pcb_t *outBlocked(struct pcb_t *p);

/*
 * Function: headBlocked
 * ---------------------
 * Return a pointer to the ProcBlk head of the process queue
 * associated with the semaphore (semAdd).
 *
 * semAdd: pointer to a semaphore
 *
 * returns: NULL if (semAdd) is not found in the ASL
 *          or if the process queue is empty,
 *          the pointer to the ProcBlk head
 */
struct pcb_t *headBlocked(int *semAdd);