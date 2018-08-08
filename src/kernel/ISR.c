#include "headers/ISR.h"
#include "headers/stdio.h"
#include "headers/keyboard.h"
#include "headers/process_handler.h"

extern void isr_wrapper(void); //function written in assemby wrapper

extern void trap_wrapper(void); //function written in assemby wrapper

extern void keyboard_wrapper(void); //function written in assemby wrapper

void PIC_ISR(void) { //Function handling all PIC interrupts(IRQ1-IRQ15), not really implemented yet :/

}

void keyboard_ISR(void) {
    if(read_key() != 128) {
    add_key_to_buffer(read_key());
    run_keyboard_handler();
    }

}

void TRAP_ISR(struct registers regs) { //calling when occurres fatal error like zero division :/
    clear_screen();
    printf("FATAL ERROR!!!\n\n");
    printf("EAX:   %R\n", regs.eax);
    printf("EBX:   %R\n", regs.ebx);
    printf("ECX:   %R\n", regs.ecx);
    printf("EDX:   %R\n", regs.edx);
    printf("EDI:   %R\n", regs.edi);
    printf("EBP:   %R\n", regs.ebp);
    printf("ESI:   %R\n", regs.esi);
    printf("ESP:   %R\n", regs.esp);
    printf("FLAGS: %R", regs.flags);
    for(;;); //no escape from criticals...(maybe some are skippable, but I won't. Buahahaha!)
}