#include <libuarm.h>
#include <uARMtypes.h>

#include "const.h"
#include "clist.h"
#include "types.h"
#include "pcb.h"
#include "asl.h"

#include "initial.h"
#include "interrupts.h"
#include "exceptions.h"
#include "scheduler.h"

void initHandler(memaddr addr, void handler()) {
    state_t* mem = (state_t*) addr;
    STST(mem);

    mem->pc = (memaddr) handler;
    mem->sp = RAM_TOP;
    mem->cpsr = STATUS_ALL_INT_DISABLE(mem->cpsr | STATUS_SYS_MODE);
}

void initVars() {
    nucleus.processCount = 0;
    nucleus.softBlockCount = 0;
    nucleus.readyQueue = CLIST_INIT;
    nucleus.currentProcess = NULL;
}

void initSemaphores() {
    for (int i = 0; i < MAX_DEVICES; i++) {
        nucleus.semaphores[i] = 0;
    }
}

extern void test();

void initTest() {
    struct pcb_t* process = allocPcb();

    process->p_s.pc = (memaddr) test;
    process->p_s.sp = RAM_TOP - FRAME_SIZE;
    process->p_s.cpsr = STATUS_ALL_INT_ENABLE(process->p_s.cpsr) | STATUS_SYS_MODE;
    process->p_s.CP15_Control = CP15_DISABLE_VM(process->p_s.CP15_Control);

    insertProcQ(&nucleus.readyQueue, process);
    nucleus.processCount++;
}

int main() {
    // Populate the four new areas in the ROM reserved frame
    tprint("Populate the four new areas in the ROM reserved frame\n");
    initHandler(INT_NEWAREA, int_handler);
    initHandler(TLB_NEWAREA, tlb_handler);
    initHandler(PGMTRAP_NEWAREA, pgmTrap_handler);
    initHandler(SYSBK_NEWAREA, sysBk_handler);

    // Initialize level2 data structures
    tprint("Initialize level2 data structures\n");
    initPcbs();
    initASL();

    // Initialize all nucleus maintained variables
    tprint("Initialize all nucleus maintained variables\n");
    initVars();

    // Initialize all nucleus maintained semaphores
    tprint("Initialize all nucleus maintained semaphores\n");
    initSemaphores();

    // Instantiate test process
    tprint("Instantiate test process\n");
    initTest();

    // Call the scheduler
    tprint("Call the scheduler\n");
    scheduler();

    return 0;
}