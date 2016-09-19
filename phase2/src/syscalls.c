#include "syscalls.h"

void terminateProcess(struct pcb_t *proc) {
    if(proc == NULL) return;

    if(proc->p_cursem != NULL) {
        
    }
}