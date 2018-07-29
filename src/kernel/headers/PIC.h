#pragma once

void PIC_set_mask(unsigned short mask);
unsigned short PIC_read_mask(void);
void PIC_enable_IRQ_line(unsigned char IRQ);
void PIC_disable_IRQ_line(unsigned char IRQ);
void PIC_initialize(void);
unsigned char PIC_read_IRQ_in_ISR(void);
void PIC_clear_ISR(void);