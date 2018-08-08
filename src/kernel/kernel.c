#include "headers/idt.h"
#include "headers/terminal.h"
#include "headers/portIO.h"
#include "headers/stdio.h"
#include "headers/process_handler.h"

void _main(void) { //MAIN FUNCTION starting whole fun!
    initialize_cursor(0,0);
    initialize_idt();
    initialize_processes();
    for(;;);
}


