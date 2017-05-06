#include <libuarm.h>

#include "types.h"

#include "initial.h"
#include "exceptions.h"
#include "scheduler.h"
#include "syscalls.h"

void copyState(state_t *src, state_t *dst) {
    dst->a1 = src->a1;
    dst->a2 = src->a2;
    dst->a3 = src->a3;
    dst->a4 = src->a4;
    dst->v1 = src->v1;
    dst->v2 = src->v2;
    dst->v3 = src->v3;
    dst->v4 = src->v4;
    dst->v5 = src->v5;
    dst->v6 = src->v6;
    dst->sl = src->sl;
    dst->fp = src->fp;
    dst->ip = src->ip;
    dst->sp = src->sp;
    dst->lr = src->lr;
    dst->pc = src->pc;
    dst->cpsr = src->cpsr;
    dst->CP15_Control = src->CP15_Control;
    dst->CP15_EntryHi = src->CP15_EntryHi;
    dst->CP15_Cause = src->CP15_Cause;
    dst->TOD_Hi = src->TOD_Hi;
    dst->TOD_Low = src->TOD_Low;
}

#define TLB (state_t *) TLB_OLDAREA, EXCP_TLB_OLD, EXCP_TLB_NEW
#define PGMT (state_t *) PGMTRAP_OLDAREA, EXCP_PGMT_OLD, EXCP_PGMT_NEW
#define SYS (state_t *) SYSBK_OLDAREA, EXCP_SYS_OLD, EXCP_SYS_NEW

void useExcpVec(state_t *area, int excpOld, int excpNew) {
    if(&(nucleus.currentProcess->p_excpvec[excpOld]) != NULL) {
        copyState(&(nucleus.currentProcess->p_excpvec[excpOld]), area);
        LDST(&(nucleus.currentProcess->p_excpvec[excpNew]));
    } else {
        terminateProcess(nucleus.currentProcess);
        scheduler();
    }
}

void tlb_handler() { tprint("tlb_handler\n");
    if(nucleus.currentProcess != NULL) {
        copyState(&(nucleus.currentProcess->p_s), (state_t *) TLB_OLDAREA);
        useExcpVec(TLB);
    }
}

void pgmTrap_handler() { tprint("pgmTrap_handler\n");
    if(nucleus.currentProcess != NULL) {
        copyState(&(nucleus.currentProcess->p_s), (state_t *) PGMTRAP_OLDAREA);
        useExcpVec(PGMT);
    }
}

void sysBk_handler() { tprint("sysBk_handler\n");
    copyState(&(nucleus.currentProcess->p_s), (state_t *) SYSBK_OLDAREA);
}