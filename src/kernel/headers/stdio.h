#pragma once

unsigned int width;
unsigned int height;

unsigned char x;
unsigned char y;

typedef struct VRAM_sign {
	unsigned char sign;
	unsigned char color;
	} VRAM_sign;

void printChar(VRAM_sign *VRAM_ptr ,const unsigned char str);
unsigned long pointerToVRAM(unsigned char w, unsigned char h);
void print(VRAM_sign *VRAM_ptr, const unsigned char *str);
void cls(void);
unsigned char* hexToStr(unsigned long);
unsigned char* decToStr(unsigned long);
void updateCursor(unsigned int, unsigned int);
