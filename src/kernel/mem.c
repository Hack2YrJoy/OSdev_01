#include "headers/mem.h"

void memcopy(void *dest, const void *src, unsigned long length) { //copy blocks of memory to other addr
        for(unsigned long i = 0; i < length; i++) {
            *(unsigned char*)dest = *(unsigned char*)src;
            (unsigned char*)src++, (unsigned char*)dest++;
        }
}
void clear_mem(void* dest, unsigned long length) { //fill memory with zeros
    for(unsigned long i = 0; i < length; i++) {
        *(unsigned char*)dest = 0x00;
        (unsigned char*)dest++;
    }
}