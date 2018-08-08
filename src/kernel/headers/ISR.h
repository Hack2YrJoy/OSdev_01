#pragma once

struct registers {
  unsigned short flags;
  unsigned long ebp;
  unsigned long edi;
  unsigned long esi;
  unsigned long edx;
  unsigned long ecx;
  unsigned long ebx;
  unsigned long eax;
  unsigned long esp;
};

void isr_wrapper(void);
void keyboard_wrapper(void);
void PIC_ISR(void);
void TRAP_ISR(struct registers regs);
void trap_wrapper(void);