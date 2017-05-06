#pragma once

#include <uARMconst.h>

#include "clist.h"
#include "pcb.h"

struct kernel_t {
    unsigned short processCount;
    unsigned short softBlockCount;
    struct clist readyQueue;
    struct pcb_t* currentProcess;
    union {
        int semaphores[MAX_DEVICES];
        struct {
            int real[DEV_PER_INT];
            int disk[DEV_PER_INT];
            int tape[DEV_PER_INT];
            int prnt[DEV_PER_INT];
            int trcv[DEV_PER_INT];
            int ttrs[DEV_PER_INT];
            int pclk;
        } semds;
    };
} nucleus;