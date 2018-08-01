#include "headers/ISR.h"
#include "headers/PIC.h"
#include "headers/stdio.h"
#include "headers/terminal.h"
#include "headers/keyboard.h"

VRAM_sign buff[80*25];

extern void isr_wrapper(void); //function written in assemby wrapper

extern void trap_wrapper(void); //function written in assemby wrapper

void PIC_ISR(void) { //Function handling all PIC interrupts(IRQ0-IRQ15), not really implemented yet :/
    if(PIC_read_IRQ_in_ISR() == 1) {
        terminal int_console = initialize_terminal(80,25,buff);
        print_char(&int_console, convert_to_ASCII(read_scan_code()));
    }
}

void TRAP_ISR(struct registers regs) { //calling when occurres fatal error like zero division :/
    terminal error_console = initialize_terminal(80,25,buff);
    printf(&error_console, "FATAL ERROR!!!\n\n");
    printf(&error_console, "EAX:   %h\n", regs.eax);
    printf(&error_console, "EBX:   %h\n", regs.ebx);
    printf(&error_console, "ECX:   %h\n", regs.ecx);
    printf(&error_console, "EDX:   %h\n", regs.edx);
    printf(&error_console, "EDI:   %h\n", regs.edi);
    printf(&error_console, "EBP:   %h\n", regs.ebp);
    printf(&error_console, "ESI:   %h\n", regs.esi);
    printf(&error_console, "ESP:   %h\n", regs.esp);
    printf(&error_console, "FLAGS: %h", regs.flags);
    for(;;); //no escape from criticals...(maybe some are skippable, but I won't. Buahahaha!)
}