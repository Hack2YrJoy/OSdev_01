#include "headers\\stdio.h"

struct VRAM_sign {
	unsigned char sign;
	unsigned char color;
	};

struct VRAM_sign* VRAM_ptr = (struct VRAM_sign*)0xB8000;

void print(const char *str) {
	int i = 0;
	while(str[i] != 0x00) {
		VRAM_ptr[i].sign = str[i];
		VRAM_ptr[i].color = 0x0f;
    	i++;
	}
}

void cls(void) { //clear screen
	for(int i = 0; i <= 1999; i++) { //clear screen 80x25(80*25-1)
		VRAM_ptr[i].sign = 0x00;    //nul sign
		VRAM_ptr[i].color = 0x0f;   //black color
	}
}
