#include "headers\stdio.h"

char string[] = "this shit is only for test usage, I will destroy it later, buahahahahah!";
void _main(void) {
cls();
print(hexToStr(0xfff),0, 4);
print(decToStr(12345678),0,7);
print(string, 0, 0);
for(;;);
}

