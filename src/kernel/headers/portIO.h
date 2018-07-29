#pragma once 

void outb(int port, unsigned char v);
void outw(int port, unsigned short v);
void outd(int port, unsigned int v);

unsigned char inb(int port);
unsigned short inw(int port);
unsigned int ind(int port);