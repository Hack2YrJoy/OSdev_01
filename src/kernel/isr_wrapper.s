.file "isr_wrapper.s"
.globl   _isr_wrapper
.globl   _trap_wrapper
.globl   _keyboard_wrapper
.extern _PIC_ISR
.extern _keyboard_ISR
.extern _TRAP_ISR
.extern _PIC_clear_ISR
.section .text

_isr_wrapper:
    pushal
    cld
    call _PIC_ISR
    call _PIC_clear_ISR
    popal
    iret

_keyboard_wrapper:
    pushal
    cld
    call _keyboard_ISR
    call _PIC_clear_ISR
    popal
    iret    

_trap_wrapper:
    cli
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

