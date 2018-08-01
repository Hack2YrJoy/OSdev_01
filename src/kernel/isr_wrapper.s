.file "isr_wrapper.s"
.globl   _isr_wrapper
.globl   _trap_wrapper
.extern _PIC_ISR
.extern _TRAP_ISR
.extern _PIC_clear_ISR
.section .text

_isr_wrapper:
    pushal
    cld
    call _PIC_ISR
    popal
    call _PIC_clear_ISR
    iret

_trap_wrapper:
    push %esp
    push %eax
    push %ebx
    push %ecx
    push %edx
    push %esi
    push %edi
    push %ebp
    pushf
    call _TRAP_ISR

