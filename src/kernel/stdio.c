#include "headers\stdio.h"

unsigned int width = 80;
unsigned int height = 25;

struct VRAM_sign {
	unsigned char sign;
	unsigned char color;
	};
	
struct VRAM_sign* pointerToVRAM(unsigned int w, unsigned int h) {
	return (struct VRAM_sign*)((width * (h*2)) + (2*w) + 0xB8000);
}

void print(const char *str, unsigned int x, unsigned int y) {
	struct VRAM_sign* VRAM_ptr = (struct VRAM_sign*)pointerToVRAM(x,y);
	int i = 0;
	while(str[i] != 0x00) {
		VRAM_ptr[i].sign = str[i];
		VRAM_ptr[i].color = 0x0f;
    	i++;
	}
}

void cls(void) { //clear screen
	struct VRAM_sign* VRAM_ptr = (struct VRAM_sign*)pointerToVRAM(0,0);
	for(int i = 0; i <= (width*height - 1); i++) { //clear screen
		VRAM_ptr[i].sign = 0x00;    //nul sign
		VRAM_ptr[i].color = 0x0f;   //black color
	}
}

unsigned char* hexToStr(unsigned long x) {
	unsigned int size = 0;
	unsigned long tempX = x; 
	while(tempX != 0x0) {
		tempX /= 0x10;
		size++;
	}
	unsigned char *str;
	str[size] = '\0';
	char signs[] = "0123456789ABCDEF";
	for(int i = (size - 1); i >= 0; i--) {
		str[i] = signs[x & 0xF];
		x >>= 4;
	}
	return str;
}

unsigned char* decToStr(unsigned long x) {
	unsigned long tempX = x;
	unsigned int size = 0;
	while(tempX != 0) {
		tempX /= 10;
		size++;
	}
	unsigned char *c;
	for(int i = 0; i < size; i++) {
		c[i] = 0x30;
	}
	for(int i = 0; i < size; i++) {
		c[size-(i+1)] += x % 10;
		x /= 10;
	}
	c[size] = '\0';
	return c;
}
