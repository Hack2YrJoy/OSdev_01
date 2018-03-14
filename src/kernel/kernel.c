void _main(void) {

struct VRAM_sign {
	unsigned char sign;
	unsigned char color;
}; 
struct VRAM_sign character;
character.color = 0x20;
character.sign = 0x45;
struct VRAM_sign *VRAM_addr = (struct VRAM_sign *)0xb8000;
*VRAM_addr = character;

for(;;);
}

