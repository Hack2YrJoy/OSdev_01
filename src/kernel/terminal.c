#include "headers/terminal.h"
#include "headers/mem.h"
#include "headers/portIO.h"

terminal initialize_terminal(unsigned short width, unsigned short heigth, VRAM_sign buff[]) {
    terminal ter;
    ter.buff = buff; //min value is 25*80
    ter.width = width;
    ter.heigth = heigth;
    ter.x = 0;
    ter.y = 0;
    clear_buff(&ter);
    return ter;
}

void increment_pos(terminal *ter, unsigned char ifTab) {
    if(ifTab == 0) {
        ter->x++;
        if(ter->x > ter->width) {
            ter->x = 0;
            ter->y++;
        }
    }
    else {
        ter->x += 8;
        if(ter->x > 80) {
            ter->x %= 10;
            ter->y++;
        }
    }
    if(ter->y > ter->heigth) {
        ter->y--; //implement scrolling you moron!!!!
    }
}

void enable_cursor(unsigned short cursor_start, unsigned short cursor_end) {
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3E0) & 0xE0) | cursor_end);
}

void str_to_buff(terminal *ter, const unsigned char* str) {
    int i = 0;
    while(str[i] != '\0') {
    char_to_buff(ter, str[i]);
    i++;
    }
}

void char_to_buff(terminal *ter, const unsigned char chr) {
    VRAM_sign sign_struct;
    sign_struct.color = 0x0f; //BLACK
    sign_struct.sign = chr;
    ter->buff[ter->x + (ter->y*ter->width)] = sign_struct;
    increment_pos(ter, 0);
}

void print_buff(terminal *ter) {
     memcopy((void*)0xb8000, ter->buff, (ter->width*ter->heigth)*2);
     update_cursor(ter);
}
void update_buff(terminal *ter) {
    memcopy(ter->buff, (void*)0xb8000, (ter->width*ter->heigth)*2);
}

void print_char(terminal *ter, const unsigned char chr) {
    if(chr == '\n') {
        ter->x = ter->width;
        increment_pos(ter, 0);
        update_cursor(ter);
    }
    else if(chr == '\t') {
        increment_pos(ter, 1);
        update_cursor(ter);
    }
    else {
    VRAM_sign sign;
    sign.color = 0x0f;
    sign.sign = chr;
    VRAM_sign *VRAM_ptr = (VRAM_sign*)(0xb8000+(ter->x + (ter->y*(ter->width)))*2);
    *VRAM_ptr = sign;
    char_to_buff(ter, chr);
    update_cursor(ter);
    }
}

void print_str(terminal *ter, const unsigned char *str) {
    int i = 0;
    while(str[i] != '\0') {
            if(str[i] == '\n') {
                ter->x = ter->width;
                increment_pos(ter, 0);
                update_cursor(ter);
            }
            else if(str[i] == '\t') {
                ter->x = ter->width;
                increment_pos(ter, 1);
                update_cursor(ter);
            }
            else print_char(ter, str[i]);
            i++;
        }
}

void change_pos(terminal *ter, unsigned short x, unsigned short y) {
    ter->x = x;
    ter->y = y;
    update_cursor(ter);
}
void update_cursor(terminal *ter) {
	unsigned long pos = ((ter->y+1) * ter->width) + ter->x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

void clear_screen(terminal *ter) {
    clear_buff(ter);
    print_buff(ter);
}

void clear_buff(terminal *ter) {
    for(unsigned short i = 0; i < ter->heigth*ter->width; i++) {
        ter->buff[i].sign = 0x00;
        ter->buff[i].color = 0x0f;
    }
    ter->x=0;
    ter->y=0;
}


