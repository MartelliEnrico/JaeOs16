#pragma once

#include "types.h"
#include "clist.h"

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

/*
 * Function: emptyChild
 * --------------------
 * Check if the tree is empty
 *
 * p: pointer to ProcBlk
 *
 * returns: TRUE if the tree is empty,
 *          FALSE otherwise
 */
int emptyChild(struct pcb_t *p);

/*
 * Function: insertChild
 * ---------------------
 * Make (p) a child of ProcBlk (parent)
 *
 * parent: pointer to ProcBlk
 * p: pointer to ProcBlk, child of parent
 */
void insertChild(struct pcb_t *parent, struct pcb_t *p);

/*
 * Function: removeChild
 * ---------------------
 * Make the first child of ProcBlk (p) no longer his child
 *
 * p: pointer to ProcBlk
 *
 * returns: NULL if there are no child of p,
 *          pointer to the removed child
 */
struct pcb_t *removeChild(struct pcb_t *p);

/*
 * Function: outChild
 * ------------------
 * Make the ProcBlk (p) no longer the child of his parent;
 * (p) needs to be the first child of his parent
 *
 * p: pointer to ProcBlk
 *
 * returns: NULL if p has no parent,
 *          otherwise p
 */
struct pcb_t *outChild(struct pcb_t *p);

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