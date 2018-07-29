#include "headers/portIO.h"

inline void outb(int port, unsigned char v) { //sends on port one byte
  __asm__ volatile ("out dx, al\n" : : "a" (v), "d" (port));
}

inline void outw(int port, unsigned short v) { //sends on port one word(2 bytes)
  __asm__ volatile ("out dx, ax\n" : : "a" (v), "d" (port));
}

inline void outd(int port, unsigned int v) { //sends on port one dword(4 bytes)
  __asm__ volatile ("out dx, eax\n" : : "a" (v), "d" (port));
}

inline unsigned char inb(int port) { //reads from port one byte
	unsigned char value;
	__asm__ volatile ("in al, dx\n" : "=a"(value) : "Nd" (port));
	return value; 
}

inline unsigned short inw(int port) { //reads from port one word(2 bytes)
	unsigned short value;
	__asm__ volatile ("in ax, dx\n" : "=a"(value) : "d"(port));
	return value; 
}

inline unsigned int ind(int port) { //reads from port one dword(4 bytes)
	unsigned int value;
	__asm__ volatile ("in eax, dx\n" : "=a"(value) : "d"(port));
	return value; 
}