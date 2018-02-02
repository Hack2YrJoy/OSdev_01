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
jmp word 0x0000:start ; now it is: 0000:7C00(II)
start:

mov ah, 0x02
mov al, 0x01
mov ch, 0x0
int 0x13

jmp $
times 510-($-$$) db 0x0
db 0x55
db 0xAA
