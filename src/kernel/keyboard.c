#include "headers/keyboard.h"
#include "headers/portIO.h"

unsigned char read_scan_code(void) {
    return inb(0x60);
}

unsigned char convert_to_ASCII(unsigned char key) {
   char* row_1 = "qwertyuiop[]";
   char* row_2 = "asdfghjkl;'";
   char* row_3 = "zxcvbnm,./";
   char* num = "1234567890-=";
   char chr;

    if(key >= 0x02 && key <= 0x0d) {
       chr = num[key-0x02];
   }
    else if(key >= 0x10 && key <= 0x1e) {
       chr = row_1[key-0x10];
   }
    else if(key >= 0x1e && key <= 0x28) {
       chr = row_2[key-0x1e];
   }
    else if(key >= 0x2c && key <= 0x35) {
       chr = row_3[key-0x2c];
   }
   return chr;
}