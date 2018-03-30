#pragma once

unsigned int width;
unsigned int height;

void print(const unsigned char*, unsigned int, unsigned int);
void cls(void);
unsigned char* hexToStr(unsigned long);
unsigned char* decToStr(unsigned long);
void updateCursor(unsigned int, unsigned int);