#include "headers/stdio.h"
#include "headers/portIO.h"

unsigned int width = 80;
unsigned int height = 25;

unsigned char x = 0;
unsigned char y = 0;

unsigned long pointerToVRAM(unsigned char w, unsigned char h) {
	return ((width * (h*2)) + (2*w) + 0xB8000);
}

void print(VRAM_sign *VRAM_ptr, const unsigned char *str) {
	unsigned int i = 0;
	while(str[i] != 0x00) {
		VRAM_ptr[i].sign = str[i];
		VRAM_ptr[i].color = 0x0f;
    	i++;
	}
}
void printChar(VRAM_sign *VRAM_ptr ,const unsigned char str) {
	VRAM_ptr[0].sign = str;
	VRAM_ptr[0].color = 0x0f;
}

void cls(void) { //clear screen
	VRAM_sign* VRAM_ptr = (VRAM_sign*)pointerToVRAM(0,0);
	for(unsigned int i = 0; i <= (width*height - 1); i++) { //clear screen
		VRAM_ptr[i].sign = 0x00;    //nul sign
		VRAM_ptr[i].color = 0x0f;   //black color
	}
}

unsigned char* hexToStr(unsigned long x) {
	unsigned char buffer[32];
	unsigned int size = 0;
	unsigned long tempX = x; 
	while(tempX != 0x0) {
		tempX /= 0x10;
		size++;
	}
	if(size == 0) size = 1;
	unsigned char *str = buffer;
	str[size] = '\0';
	char signs[] = "0123456789ABCDEF";
	for(int i = (size - 1); i >= 0; i--) {
		str[i] = signs[x & 0xF];
		x >>= 4;
	}
	return str;
}

unsigned char* decToStr(unsigned long x) {
	unsigned char buffer[32];
	unsigned long tempX = x;
	unsigned int size = 0;
	while(tempX != 0) {
		tempX /= 10;
		size++;
	}
	if(size == 0) size = 1;
	unsigned char *c = buffer;
	for(unsigned int i = 0; i < size; i++) {
		c[i] = 0x30;
	}
	for(unsigned int i = 0; i < size; i++) {
		c[size-(i+1)] += x % 10;
		x /= 10;
	}
	c[size] = '\0';
	return c;
}

void updateCursor(unsigned int x,unsigned int y) {
	unsigned long pos = y * width + x;
	outw(0x3D4, 0x0F);
	outw(0x3D5, (unsigned char)(pos & 0xFF));
	outw(0x3D4, 0x0E);
	outw(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}
