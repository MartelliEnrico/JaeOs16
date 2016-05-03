#include <libuarm.h>
#include <uARMtypes.h>

#include "const.h"
#include "clist.h"
#include "pcb.h"
#include "asl.h"

#include "initial.h"
#include "interrupts.h"
#include "exceptions.h"

void initHandler(memaddr addr, void* handler) {
    state_t* mem = (state_t*) addr;
    STST(mem);

    mem->pc = (memaddr) handler;
    mem->sp = RAM_TOP;
    mem->cpsr = STATUS_ALL_INT_DISABLE(mem->cpsr) | STATUS_SYS_MODE;
}

int main() {
    // Populate the four new areas in the ROM reserved frame
    initHandler(INT_NEWAREA, int_handler);
    initHandler(TLB_NEWAREA, tlb_handler);
    initHandler(PGMTRAP_NEWAREA, pgmTrap_handler);
    initHandler(SYSBK_NEWAREA, sysBk_handler);

    // Initialize level2 data structures
    initPcbs();
    initASL();

    // Initialize all nucleus maintained variables
    nucleus.processCount = 0;
    nucleus.softBlockCount = 0;
    nucleus.readyQueue = CLIST_INIT;
    nucleus.currentProcess = NULL;

    // Initialize all nucleus maintained semaphores
    for (int i = 0; i < MAX_DEVICES; i++) {
        nucleus.semaphores[i] = 0;
    }

    return 0;
}