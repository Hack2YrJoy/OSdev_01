#pragma once
#include "terminal.h"

void printf(terminal *ter, const char* str, ...);
unsigned char* hexToStr(unsigned long x, unsigned char zeros_fill);
unsigned char* HexToStr(unsigned long x, unsigned char zeros_fill);
unsigned char* decToStr(unsigned long x);
