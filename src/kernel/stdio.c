#include "headers/stdio.h"
#include "headers/portIO.h"
#include "headers/terminal.h"
#include <stdarg.h>

void printf(terminal *ter, const char* str, ...) {
	va_list args;
	va_start(args, str);
	while(*str != '\0') {
		if(*str == '%') {
			str++;
			switch(*str) {
				case 'h':
				print_str(ter, hexToStr(va_arg(args, unsigned long), 0));
				break;

				case 'r': //'r' is meant to be abbreviation for "register" because it fill with zeros to 32bits value
				print_str(ter, hexToStr(va_arg(args, unsigned long), 1));
				break;

				case 'H': //print captital letters hex
				print_str(ter, HexToStr(va_arg(args, unsigned long), 0));
				break;

				case 'R': //print captital letters hex
				print_str(ter, HexToStr(va_arg(args, unsigned long), 1));
				break;

				case 'c':
				print_char(ter, va_arg(args, int));
				break;

				case 's':
				print_str(ter, va_arg(args, unsigned char*));
				break;

				case 'i':
				case 'd':
				print_str(ter, decToStr(va_arg(args, unsigned long)));
				break;

				case '%':
				print_char(ter, '%');
				break;

				default:
				print_char(ter, *str);
				break;
			}
		}
		else {
			print_char(ter, *str);
		}
	str++;
	}
	va_end(args);
}

unsigned char* hexToStr(unsigned long x, unsigned char zeros_fill) { //fills with zeros when value is other than 0
	unsigned char buffer[9] = {0};
	unsigned int size = 0;
	unsigned long tempX = x; 
	while(tempX != 0x0) {
		tempX /= 0x10;
		size++;
	}
	if(size == 0) size = 1;
	unsigned char *str = buffer;
	str[8] = '\0';
	char signs[] = "0123456789abcdef";

	if(zeros_fill == 0) {
		for(int i = (size - 1); i >= 0; i--) {
		str[i] = signs[x & 0xF];
		x >>= 4;
		}
	}

	else {
		for(int i = (8 - 1); i >= 0; i--) {
		str[i] = signs[x & 0xF];
		x >>= 4;
		}
	}
	return str;
}

unsigned char* HexToStr(unsigned long x, unsigned char zeros_fill) { //fills with zeros when value is other than 0
	unsigned char buffer[9] = {0};
	unsigned int size = 0;
	unsigned long tempX = x; 
	while(tempX != 0x0) {
		tempX /= 0x10;
		size++;
	}
	if(size == 0) size = 1;
	unsigned char *str = buffer;
	str[8] = '\0';
	char signs[] = "0123456789ABCDEF";

	if(zeros_fill == 0) {
		for(int i = (size - 1); i >= 0; i--) {
		str[i] = signs[x & 0xF];
		x >>= 4;
		}
	}
	else {
		for(int i = (8 - 1); i >= 0; i--) {
		str[i] = signs[x & 0xF];
		x >>= 4;
		}
	}
	return str;
}

unsigned char* decToStr(unsigned long x) {
	if(x == 0) {
		return (unsigned char*)"0";
	}
	unsigned char buff[14] = {0};
	unsigned char *p = buff;
	while(x != 0){
		p--;
		*p = '0'+(x % 10);
		x /= 10;
	}
	return p;
}

