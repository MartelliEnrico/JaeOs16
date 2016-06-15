#include <libuarm.h>

#include "const.h"
#include "clist.h"

#include "scheduler.h"
#include "initial.h"

unsigned int sliceTime = 0;
unsigned int clockTime = 0;
unsigned int processTime = 0;

void tick() {
    unsigned int time = getTODLO();
    int deltaSlice = SCHED_TIME_SLICE + sliceTime - time;
    int deltaClock = SCHED_PSEUDO_CLOCK + clockTime - time;

    if (deltaSlice <= 0) {
        sliceTime = time;
        deltaSlice = SCHED_TIME_SLICE;
    }

    if (deltaClock <= 0) {
        clockTime = time;
        deltaClock = SCHED_PSEUDO_CLOCK;
    }

    if (deltaClock <= deltaSlice) {
        setTIMER(deltaClock);
    } else {
        setTIMER(deltaSlice);
    }
}

void deadlock() {
    PANIC();
}

void scheduler() {
    tick();

    if (nucleus.currentProcess == NULL) {
        if (clist_empty(nucleus.readyQueue)) {
            if (nucleus.processCount == 0) {
                HALT();
            } else if (nucleus.softBlockCount == 0) {
                deadlock();
            } else {
                setSTATUS(STATUS_ALL_INT_ENABLE(getSTATUS()));
                WAIT();
            }
        }

        nucleus.currentProcess = removeProcQ(&nucleus.readyQueue);
    }

    processTime = getTODLO();

    LDST(&nucleus.currentProcess->p_s);
}