#pragma once
#include "terminal.h"

typedef struct thread {
 unsigned char exists;
unsigned char is_active;
 unsigned long ID;
 unsigned char KeyboardBuffer[8];
 void (*keyboard_handler_addr)(void);
 terminal window;
 VRAM_sign buff[25*80]; //size of window
 unsigned char chr_buff[25][80];
 } Thread;


typedef struct process {
    Thread core;
} Process;

void initialize_processes(void);
void create_process(void);
Process* find_free_memory_for_process(void);
void generate_process(Process *process);
void generate_window(Process *process);
Process* get_current_process(void);
void set_current_process_by_ID(int ID);
void set_current_process_by_ptr(Process* process);
void set_process_keyboard_handler(Process* process, void (*keyboard_handler_addr)(void)); 
void delete_process(Process* process);
terminal* get_window(Process* process);
terminal* get_current_window(void);
unsigned char get_key_from_buffer(void);
void add_key_to_buffer(unsigned char key);
void run_keyboard_handler(void);
void update_chr_buff(void);
void update_buff_with_chr_buff(void);
void set_chr_buff_line(int y, unsigned char* line);
void update_specyfic_chr_buff(Process* process);
void clear_specific_buff(Process* process);