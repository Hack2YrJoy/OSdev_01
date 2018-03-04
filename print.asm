print16: ;put address string to SI register befor call
lodsb
mov cl, al
cmp cl, 0
jnz print16_chr
mov ax, 0
mov word [x_axis], ax
mov ax, [y_axis]
inc ax
mov word [y_axis], ax
ret

print16_chr: ;char goes to CL
mov di, 0
mov ch, 0x0f
mov ax, [x_axis]
cmp ax, 80 
jnz next
mov word [x_axis], 0
mov dx, [y_axis]
add dx, 1 
mov word [y_axis], dx
next:
mov bx, [x_axis]
shl bx, 1
mov ax, [y_axis]
mov dx, 160
mul dx
add ax, bx
mov di, ax
mov ax, 0xB800
mov es, ax
mov ax, cx
add word [x_axis], 1
stosw
jmp print16

;------------------------------

clear_screen:
mov bx, 160*80
mov ax, 0xB800
mov es, ax
mov di, 0
mov ax, 0x0f00
loop:
stosw
cmp di, bx
jnz loop
ret

x_axis dw 0
y_axis dw 0

