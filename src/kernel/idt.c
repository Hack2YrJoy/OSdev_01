#include "headers/idt.h"
#include "headers/ISR.h"
#include "headers/PIC.h"
#include "headers/mem.h"

inline void initialize_idt(void) { //setting IDT on 0x500 addr(GUARANTEED FREE BY BIOS)
	clear_mem((void*)0x500, 256*8);
	struct idt_structure (*idt_ptr)[256] = (struct idt_structure(*)[])0x500;
	struct lidt_record lidt;
	lidt.base = (unsigned long)idt_ptr;
	lidt.limit = (8*256)-1;
	__asm__("lidt [%0]"::"m"(lidt));

	for(unsigned short i = 0x20; i <= 0x2F; i++) { //sets all needed IDTs(0x20-0x2F) for PIC 8259A(Master and Slave)
		set_idt(i, (unsigned long)&isr_wrapper, 0x8, 0b10001110); //flags(10001110) describes Interrupt gate with ring 0 privileges(kernel)
	}

	set_idt(0x21, (unsigned long)&keyboard_wrapper, 0x8, 0b10001110);

	for(unsigned short i = 0; i <= 0x1F; i++) {
		set_idt(i, (unsigned long)&trap_wrapper, 0x8, 0b10001111);
	}

	PIC_initialize(); //makes PIC works
	__asm__ volatile ("sti"); //flag in FLAG register(x86 arch) setting Interrupt flag(makes interrupts work)
	PIC_set_mask(0x0001); //set mask to block only system clock(IRQ0)
}

void set_idt(unsigned short idx, //idx express interrupt number in IDT
			  unsigned long base,
			  unsigned short seg_selector,
			  unsigned char flags) {
	 struct idt_structure *idt = (struct idt_structure*)0x500;
	 idt[idx].low_base = (base & 0xffff);
	 idt[idx].high_base = (base >> 16) & 0xffff;
	 idt[idx].seg_selector = seg_selector;
	 idt[idx].zero_field = 0;
	 idt[idx].flags = flags;
}
