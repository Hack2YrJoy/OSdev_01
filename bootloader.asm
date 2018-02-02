[ORG 0x7C00]
[BITS 16]
section hang
hang:

times 510-($-$$) db 0x0
db 0x55
db 0xAA
