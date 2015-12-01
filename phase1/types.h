#pragma once

#include "../phase0/clist.h"

typedef unsigned int size_t;

struct pcb_t {
    struct pcb_t *p_parent; /* pointer to parent */
    struct semd_t *p_cursem; /* pointer to the semd_t on which process blocked */
    state_t p_s; /* processor state */
    in(p_list, p_children, p_siblings);
};

struct semd_t {
    int *s_semAdd; /* pointer to the semaphore */
    in(s_link, s_procq);
};