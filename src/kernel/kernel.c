#include "headers/stdio.h"
#include "headers/idt.h"

void _main(void) { //MAIN FUNCTION starting whole fun!
    VRAM_sign *VRAM_ptr = (VRAM_sign*)pointerToVRAM(0,0); //setting up structure pointing on terminal(still needs better concept :/)
    cls();
    updateCursor(79,24);  
    initialize_idt();
    for(;;);
}


