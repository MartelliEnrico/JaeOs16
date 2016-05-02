#include <libuarm.h>
#include "pcb.h"
#include "asl.h"

int main() {
    initPcbs();
    initASL();

    tprint("It works!\n");

    return 0;
}