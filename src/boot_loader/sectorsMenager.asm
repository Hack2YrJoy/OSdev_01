read_sectors:       ;reads sector to memory
	mov ax, 0x4000 ;read sectors to physical address 0x40000
	mov es, ax
	xor ax, ax
	mov bx, 0x0000
	mov ah, 2  ; read sector to memory parameter
	mov al, 10 ; 10*512B (Sectors to read count)
	mov ch, 0  ; cylider
	mov cl, 2  ; sector
	mov dh, 0  ; head
	int 13h    ; BIOS interrupt for low level disk service
	ret        ;return: CF Flag(set if error), AH(return code), AL(Actual Sectors Read Count)
