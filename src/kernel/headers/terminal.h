#pragma once

typedef struct VRAM_sign {
    unsigned char sign;
    unsigned char color;
} VRAM_sign;

typedef struct terminal {
    VRAM_sign *buff;
    unsigned short width;
    unsigned short heigth;
    unsigned short x; //actual position on x axis 
    unsigned short y; //actual position on y axis 
}terminal;

terminal initialize_terminal(unsigned short width, unsigned short heigth, VRAM_sign buff[]);
void increment_pos(terminal *ter, unsigned char ifTab);
void str_to_buff(terminal *ter, const unsigned char* str);
void char_to_buff(terminal *ter, const unsigned char chr);
void print_buff(terminal *ter);
void print_str(terminal *ter, const unsigned char *str);
void update_buff(terminal *ter);
void print_char(terminal *ter, const unsigned char chr);
void change_pos(terminal *ter, unsigned short x, unsigned short y);
void update_cursor(terminal *ter);
void enable_cursor(unsigned short cursor_start, unsigned short cursor_end);
void clear_screen(terminal *ter);
void clear_buff(terminal *ter); 
