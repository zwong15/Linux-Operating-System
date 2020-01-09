#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "types.h"
//function that reads screen to buf
int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes);

int32_t terminal_write(int32_t fd, const void* buf, int32_t nbytes);
int32_t terminal_close (int32_t fd);
int32_t terminal_open (const uint8_t* filename);

typedef struct curr_terminal{
    int8_t terminal_number;
    int8_t curr_key_buff[BUFFSIZE];
		int curr_screen_x;
    int8_t present;
		int curr_screen_y;
		uint8_t PID_array[3];
    uint32_t write_len_term;
    uint32_t counter_del_term;
} curr_terminal;

curr_terminal terminal_1;
curr_terminal terminal_2;
curr_terminal terminal_3;



#define NUM_PROCESS     2
#define LENGTH          19

#endif
