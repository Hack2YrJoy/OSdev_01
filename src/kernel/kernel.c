#include "headers\stdio.h"

unsigned char string[] = "this shit is only for test usage, I will destroy it later, buahahahahah!";
void _main(void) {
cls();
print(hexToStr(0xdeadbeef),0, 24);
print(decToStr(1234567),0,7);
print(string, 0, 0);
updateCursor(79,24);
for(;;);
}


