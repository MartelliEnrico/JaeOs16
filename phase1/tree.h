#pragma once

#include "process.h"

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