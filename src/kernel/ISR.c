#include "headers/ISR.h"
#include "headers/PIC.h"
#include "headers/stdio.h"

extern void isr_wrapper(void); //function written in assemby wrapper

void PIC_ISR(void) { //Function handling all PIC interrupts(IRQ0-IRQ15), not really implemented yet :/

    unsigned char a = PIC_read_IRQ_in_ISR();
    if(x >= 80) {
        y++;
        x = 0;
    }
    else {
        x++;
    } 
    VRAM_sign *VRAM_ptr = (VRAM_sign*)pointerToVRAM(x,y);
    print(VRAM_ptr, decToStr(a)); //write down which IRQ occurred
}