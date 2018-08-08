#pragma once


typedef struct VRAM_sign {
    unsigned char sign;
    unsigned char color;
} VRAM_sign;

typedef struct terminal {
    VRAM_sign *buff;
    unsigned char line_buff[81];
    unsigned short width;
    unsigned short heigth;
    unsigned short x; //actual position on x axis 
    unsigned short y; //actual position on y axis 
}terminal;

terminal initialize_terminal(unsigned short width, unsigned short heigth, VRAM_sign buff[]);
void increment_pos(unsigned char ifTab);
void str_to_buff(const unsigned char* str);
void char_to_buff(const unsigned char chr);
void print_buff(void);
void print_str(const unsigned char *str);
void update_buff(void);
void print_char(const unsigned char chr);
void change_pos(unsigned short x, unsigned short y);
void update_cursor(void);
void initialize_cursor(unsigned short cursor_start, unsigned short cursor_end);
void clear_screen(void);
void clear_buff(void); 
void print_char_from_process_buffer(void);
void update_last_line(void);
