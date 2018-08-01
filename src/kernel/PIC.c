#include "headers/PIC.h"
#include "headers/portIO.h"

//8259A PIC DRIVER//

void PIC_clear_ISR(void) { //used to clear ISR when EOI mode activated(unusable in AEOI)
	outb(0x20, 0b00100000);
	outb(0xA0, 0b00100000);
}
void PIC_set_mask(unsigned short mask) { //setting mask where 2 low bytes are Master, and 2 high are Slave
	outb(0x21, (mask & 0x00FF));
	outb(0xA1, (mask & 0xFF00) >> 8);
}
unsigned short PIC_read_mask(void) { //return mask where 2 low bytes are Master, and 2 high are Slave
	return ((unsigned short)((inb(0xA1) << 8) + inb(0x21)));
}
void PIC_enable_IRQ_line(unsigned char IRQ) { //takes value from 0-15 which represents IRQ line to make enabled
	if(IRQ > 7) { // DO FOR SLAVE
		IRQ -= 8;
		unsigned char value = inb(0xA1) & ~(1 << IRQ);
		outb(0xA1, value); // clear bit on IMR map to enable interrupt
	}
	else { // DO FOR MASTER
		unsigned char value = inb(0x21) & ~(1 << IRQ);
		outb(0x21, value); // clear bit on IMR map to enable interrupt
	}
}
void PIC_disable_IRQ_line(unsigned char IRQ) { //takes value from 0-15 which represents IRQ line to make dicabled
	if(IRQ > 7) { // DO FOR SLAVE
		IRQ -= 8;
		unsigned char value = inb(0xA1) | (1 << IRQ);
    	outb(0xA1, value); // set bit on IMR map to disable interrupt
	}
	else { // DO FOR MASTER
		unsigned char value = inb(0x21) | (1 << IRQ);
    	outb(0x21, value); // set bit on IMR map to disable interrupt
	}
}
unsigned char PIC_read_IRQ_in_ISR(void) {
	unsigned char IRQ = 0;
	outb(0xA0, 0b00001011);
	unsigned char ISR_value = inb(0xA0);
	if(ISR_value != 0) { // WHEN THERE IS AN INTERRUPT ON SLAVE
    	while(ISR_value != 1) {
			ISR_value >>= 1;
			IRQ++;
		}
		return IRQ+8;
	}
	else {
 /* WHEN THERE IS AN INTERRUPT ON MASTER(what is always true when interrupt is raised)
    there is an interrupt raised on SLAVE either. It is because SLAVE is wired using IRQ2 line on MASTER.
	So when we have interrupt raised by SLAVE than we have interrupt on MASTER either(IRQ2).
	We have to check first SLAVE to make it correct(if statement- "ISR_value != 0"), than if we get 0, check MASTER
	or check if on MASTER it is IRQ2 raised, than check SLAVE(if true).
	*/ 
		outb(0x20, 0b00001011);
		ISR_value = inb(0x20);
		while(ISR_value != 1 && ISR_value != 0) {
			ISR_value >>= 1;
			IRQ++;
		}
		return IRQ;
	}
}

void PIC_initialize(void) {
	outb(0x20, 0b00010001);//send ICW1 informing PIC that there will be ICW4(MASTER)
	outb(0xA0, 0b00010001);//send ICW1 informing PIC that there will be ICW4(SLAVE)

    outb(0x21, 0x20);//send ICW2 which sets PICs IRQ offset. It starts IRQ0 from 0x20th interrupt in IDT(MASTER)
	outb(0xA1, 0x28);//send ICW2 which sets PICs IRQ offset. It starts IRQ8 from 0x28th interrupt in IDT(SLAVE)

	outb(0x21, 0b00000100);//send ICW3 which sets PICs 2nd interrupt(IRQ2) to be used for connection SLAVE to MASTER(MASTER)
	outb(0xA1, 0b00000010);//send ICW3 which sets PICs information that its cascade identity(SLAVE)

	outb(0x21, 0b00000001);//send ICW4 which sets PICs mode to 8086/88(MASTER)
    outb(0xA1, 0b00000001);//send ICW4 which sets PICs mode to 8086/88(SLAVE)

}
