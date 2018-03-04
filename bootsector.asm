[BITS 16]
[ORG 0x7C00]
; 0x7C00 is addr where BIOS start Booting.
; 16bit x86 addressing: SEGMENT:OFFSET,
; where: address = SEGMENT * 0x10(16) + OFFSET

;               I   II
; (SEGMENT)CS 07C0 0000
;  (0FFSET)IP 0000 7C00

; both points to the same address
; BIOS can use any of them
; to avoid incompatibility:
	jmp 0x0000:start ; now it is: 0000:7C00(II)
%include "print.asm"
32bit_info: db "You are in 16-bit mode",0x0
start:
;-------------------------------------------------------------------------
; ENTERING PROTECTED MODE
Protected_mode:
	mov eax, 0
	mov ds, ax
	call clear_screen
        ;CHECK IF A20 LINE IS ENABLED
        xor ax, ax ; ax = 0
        mov es, ax
        not ax ; ax = 0xFFFF
        mov ds, ax
        mov di, 0x0500
        mov si, 0x0510
        mov al, byte [es:di]
        push ax 
        mov al, byte [ds:si]
        push ax
        mov byte [es:di], 0x00
        mov byte [ds:si], 0xFF
        cmp byte [es:di], 0xFF
        pop ax
        mov byte [ds:si], al
        pop ax
        mov byte [es:di], al
        mov ax, 0
        jne A20_ENABLED

        in al, 0x92
	or al, 2
	out 0x92, al
A20_ENABLED: 
	cli
	lgdt [cs:GDT_descr]
	mov eax, cr0
	or ax, 1
	mov cr0, eax
	mov ax, 0
	mov ds, ax
	mov fs, ax
	mov es, ax
	mov gs, ax
	jmp GDT32.code:PM

PM:	
	[BITS 32]
	mov ax, GDT32.data
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov ebp, 0x20000
	mov esp, ebp
	jmp $
;-------------------------------------------------------------------------
GDT32:
	; null segment descriptor
	dd 0x0
	dd 0x0
.code equ $ - GDT32
	; CODE SEGMENT DESCRIPTOR
	dw 0xffff
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
	; DATA SEGMENT DESCRIPTOR
.data equ $ - GDT32
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
	GDT32_end:
GDT_descr:
	dw GDT32_end - GDT32 - 1
	dd GDT32

;-------------------------------------------------------------------------
	times 510-($-$$) db 0x0 ; fills file to 510+2bytes(segment size)
	db 0xAA
	db 0x55 ; 0xAA55 -> signature for BIOS closing BootSector(MBR)
