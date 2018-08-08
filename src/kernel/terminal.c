#include "headers/terminal.h"
#include "headers/mem.h"
#include "headers/portIO.h"
#include "headers/stdio.h"
#include "headers/process_handler.h"

terminal initialize_terminal(unsigned short width, unsigned short heigth, VRAM_sign buff[]) {
    terminal ter;
    ter.buff = buff;
    ter.width = width;
    ter.heigth = heigth;
    ter.x = 0;
    ter.y = 0;
    return ter;
}

void increment_pos(unsigned char ifTab) {
    terminal *ter = get_current_window();
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
    if(ter->y >= ter->heigth) {
        ter->y--;
        unsigned char line[80];
        update_chr_buff();
        for(int i = 0; i < 25; i++) {
            for(int j = 0; j < 80; j++) {
                if(i == 24) {
                    line[j] = ' ';
                }
                else {
                    line[j] = get_current_process()->core.chr_buff[i+1][j];
                }
            }
            set_chr_buff_line(i, line);
            print_buff();
        }
        //print_buff();
    }
}

void initialize_cursor(unsigned short cursor_start, unsigned short cursor_end) {
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3E0) & 0xE0) | cursor_end);
}

void str_to_buff(const unsigned char* str) {
    int i = 0;
    while(str[i] != '\0') {
    char_to_buff(str[i]);
    i++;
    }
}

void char_to_buff(const unsigned char chr) {
    terminal* ter = get_current_window();
    VRAM_sign sign_struct;
    sign_struct.color = 0x0f; //BLACK
    sign_struct.sign = chr;
    ter->buff[ter->x + (ter->y*ter->width)] = sign_struct;
    increment_pos(0);
}

void print_buff(void) {
    terminal* ter = get_current_window();
     memcopy((void*)0xb8000, ter->buff, (ter->width*ter->heigth)*2);
     update_cursor();
}
void update_buff(void) {
    terminal* ter = get_current_window();
    memcopy(ter->buff, (void*)0xb8000, (ter->width*ter->heigth)*2);
}

void print_char(const unsigned char chr) {
    terminal* ter = get_current_window();
    if(chr == '\n') {
        ter->x = ter->width;
        increment_pos(0);
        update_cursor();
        update_last_line();
    }
    else if(chr == '\t') {
        increment_pos(1);
        update_cursor();
    }
    else {
    VRAM_sign sign;
    sign.color = 0x0f;
    sign.sign = chr;
    VRAM_sign *VRAM_ptr = (VRAM_sign*)(0xb8000+(ter->x + (ter->y*(ter->width)))*2);
    *VRAM_ptr = sign;
    char_to_buff(chr);
    update_chr_buff(); //it can slow down printing on the screen!!!!!
    update_cursor();
    }
}

void print_char_from_process_buffer(void) { //temporary keyboard handler
    unsigned char chr = get_key_from_buffer();

    if(chr == '1') {
        set_current_process_by_ID(1);
    }
    else if(chr == '0') {
        set_current_process_by_ID(0);
    }
     else if(chr == 'p') {
        __asm__ volatile ("int 0x0");
    }
    else if(chr == 'o') {
        printf("%s", get_current_window()->line_buff);
    }
    else {
        print_char(chr);
    }

}

void print_str(const unsigned char *str) {
    int i = 0;
    while(str[i] != '\0') {
        print_char(str[i]);
        i++;
    }
}

void change_pos(unsigned short x, unsigned short y) {
    terminal *ter = get_current_window();
    ter->x = x;
    ter->y = y;
    update_cursor();
}
void update_cursor(void) {
    terminal *ter = get_current_window();
	unsigned long pos = ((ter->y+1) * ter->width) + ter->x; 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

void clear_screen() {
    clear_buff();
    print_buff();
}

void clear_buff(void) {
    terminal *ter = get_current_window();
    for(unsigned short i = 0; i < ter->heigth*ter->width; i++) {
        ter->buff[i].sign = 0x00;
        ter->buff[i].color = 0x0f;
    }
    ter->x=0;
    ter->y=0;
    update_chr_buff();
}

void update_last_line(void) {
    update_chr_buff();
    for(int i = 0; i < 80; i++) {
        get_current_window()->line_buff[i] =  get_current_process()->core.chr_buff[(get_current_window()->y)-1][i];
    }
    get_current_window()->line_buff[80] = '\0';
}


