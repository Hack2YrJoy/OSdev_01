.file "isr_wrapper.s"
.globl   _isr_wrapper
.extern _PIC_ISR
.extern _PIC_clear_ISR
.section .text

_isr_wrapper:
    pushal
    cld
    call _PIC_ISR
    popal
    call _PIC_clear_ISR
    iret
