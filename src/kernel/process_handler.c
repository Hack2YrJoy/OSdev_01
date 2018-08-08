#include "headers/process_handler.h"
#include "headers/mem.h"

void initialize_processes(void) {
    clear_mem((void*)0x100000, 0xE00000); //clear 14MiB for processes on 0x100000 address
    create_process();
    set_current_process_by_ID(0); //process with ID 0 is major terminal(SHELL)
}

void create_process(void) {
    Process* process = find_free_memory_for_process();
    if(process == 0) {
        __asm__ volatile("int 0x0"); //handle error when there is no space for process!
    }
    else {
        generate_process(process);
        clear_specific_buff(process);
        
    }
}

Process* find_free_memory_for_process(void) {
    char (*process_ptr)[0x20000] = (char(*)[])0x100000;
    unsigned int ID = 0;
    for(int i = 0; i <= 111; i++) { //go throw all processes to get free space
        if(process_ptr[0][0] == 0) {
            Process* process = (Process*)process_ptr;
            Thread* core = &(*process).core;
            core->ID = ID;
            return process;
        }
        else {
            process_ptr++;
            ID++;
        }
    }
    return 0;
}

void generate_process(Process* process) {
    generate_window(process);
    Thread* core = &(*process).core;
    core->exists = 1;
    core->is_active = 0;
    core->keyboard_handler_addr = &print_char_from_process_buffer; //function handling keyboard must return void and take no arguments!
}

void generate_window(Process *process) {
    Thread *core = &(*process).core;
    terminal *window = &(*core).window;
    *window = initialize_terminal(80, 25, core->buff);
}

Process* get_current_process(void) {
        char (*process_ptr)[0x20000] = (char(*)[])0x100000;
        for(int i = 0; i <= 111; i++) {
        if(process_ptr[0][1] == 1) {
            return (Process*)process_ptr;
        }
        else {
            process_ptr++;
        }
    }
    return (void*)0x0; //it only happens when it is created first process
}

void set_current_process_by_ID(int ID) {
    Process* last_current_process = get_current_process();
    if(last_current_process != 0) { //basically, it check if it is first process
        (*last_current_process).core.is_active = 0;
    } 
    char (*process_ptr)[0x20000] = (char(*)[])(0x100000 + (ID*0x20000));
    Process* process;
    process = (Process*)process_ptr;
    (*process).core.is_active = 1;
    print_buff();
}

void set_current_process_by_ptr(Process* process) {
    Process* last_current_process = get_current_process();
    if(last_current_process != 0) { //basically, it check if it is first process
        (*last_current_process).core.is_active = 0;
    } 
    (*process).core.is_active = 1;
    print_buff();
}

void set_process_keyboard_handler(Process* process, void (*keyboard_handler_addr)(void)) {
    (*process).core.keyboard_handler_addr = keyboard_handler_addr;
}

void delete_process(Process* process) {
    if((*process).core.ID == 0) { //SHELL
        //turn of system
    }
    else if((*process).core.is_active == 1){ //if you delete current process
        set_current_process_by_ID(0); //set current process to SHELL
        clear_mem(process, 0x20000);
    }
    else {
        clear_mem(process, 0x20000);
    }
}

terminal* get_window(Process* process) {
    return &(*process).core.window;
}

terminal* get_current_window(void) {
    Process* process = get_current_process();
    return &(*process).core.window;
}

unsigned char get_key_from_buffer(void) {
    Process *process = get_current_process();
    unsigned char key = (*process).core.KeyboardBuffer[0];
    for(int i = 0; i < 7; i++) {
        (*process).core.KeyboardBuffer[i] = (*process).core.KeyboardBuffer[i+1];
    }
    (*process).core.KeyboardBuffer[7] = 0;
    return key;
}

void add_key_to_buffer(unsigned char key) {
    Process* process = get_current_process();
    for(int i = 0; i < 8; i++) {
        if((*process).core.KeyboardBuffer[i] == 0) {
            (*process).core.KeyboardBuffer[i] = key;
            return;
        }
    }
    (*process).core.KeyboardBuffer[7] = key; //if buffer is full, put char on the end
}

void run_keyboard_handler(void) {
    Process* process = get_current_process();
    void (*keyboard_handler)(void) = (*process).core.keyboard_handler_addr;
    (*keyboard_handler)();
}

void update_chr_buff(void) {
    Process* process = get_current_process();
    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 80; j++) {
            (*process).core.chr_buff[i][j] = (*process).core.buff[(i*80)+j].sign;
        }
    }
}
void update_buff_with_chr_buff(void) {
    Process* process = get_current_process();
    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 80; j++) {
            (*process).core.buff[(i*80)+j].sign = (*process).core.chr_buff[i][j];
        }
    }
    print_buff();
}
void set_chr_buff_line(int y, unsigned char* line) {
    Process* process = get_current_process();
    for(int j = 0; j < 80; j++) {
            (*process).core.chr_buff[y][j] = line[j];
            (*process).core.buff[(y*80)+j].sign = (*process).core.chr_buff[y][j];
        }
        print_buff();
}
void update_specyfic_chr_buff(Process* process) {
    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 80; j++) {
            (*process).core.chr_buff[i][j] = (*process).core.buff[(i*80)+j].sign;
        }
    }
}
void clear_specific_buff(Process* process) {
    terminal *ter = &(*process).core.window;
    for(unsigned short i = 0; i < ter->heigth*ter->width; i++) {
        ter->buff[i].sign = 0x00;
        ter->buff[i].color = 0x0f;
    }
    ter->x=0;
    ter->y=0;
    update_specyfic_chr_buff(process);
}
