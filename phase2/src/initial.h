#pragma once

struct kernel_t {
    short processCount;
    short softBlockCount;
    struct clist readyQueue;
    struct pcb_t* currentProcess;
} nucleus;