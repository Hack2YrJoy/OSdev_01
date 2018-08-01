#include "headers/idt.h"
#include "headers/terminal.h"
#include "headers/portIO.h"
#include "headers/stdio.h"

VRAM_sign terminal_buffer[80*25];

void _main(void) { //MAIN FUNCTION starting whole fun!
    terminal shell = initialize_terminal(80, 25, terminal_buffer);
    enable_cursor(0,0);
    initialize_idt();
    printf(&shell, "hello new(better) terminal! :)");
    print_buff(&shell);
    for(;;);
}


