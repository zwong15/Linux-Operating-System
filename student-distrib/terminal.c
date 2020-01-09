#include "lib.h"
#include "keyboard.h"
#include "handlers.h"
#include "system_calls.h"
#include "terminal.h"
#include "pit.h"

extern uint8_t sched_count;
extern int process_flag;
extern uint32_t counter_del;
extern unsigned int counter;
extern uint8_t global_flag[6];
extern uint8_t key_buff[BUFFSIZE];
extern uint8_t execute_fix;
uint32_t write_len = 0;
uint32_t ready[NUM_PROCESS];
uint32_t flag_enter = 0;
extern uint8_t sched_count;
/*
 * terminal_close(int32_t fd)
 *   DESCRIPTION: return 0
 *   INPUTS: fd--name of file directory
 *   OUTPUTS: None
 *   RETURN VALUE: None
 *   SIDE EFFECTS: none
 */
int32_t terminal_close (int32_t fd){
	return 0;
}

/*
 * terminal_open(const uint8_t* filename)
 *   DESCRIPTION: return 0
 *   INPUTS: filename--name of file
 *   OUTPUTS: None
 *   RETURN VALUE: None
 *   SIDE EFFECTS: none
 */
int32_t terminal_open (const uint8_t* filename){
	return 0;
	}

/*
 * terminal_write(int32_t fd, const void* buf, int32_t nbytes)
 *   DESCRIPTION: writes to screen
 *   INPUTS: fd-- unused
             buf-- the buffer that we will writes
             nbytes-- how many bytes we want to write
 *   OUTPUTS: None
 *   RETURN VALUE: None
 *   SIDE EFFECTS: the keyboard buffer will be equal to key_buff
 */
extern int32_t terminal_write(int32_t fd, const void* buf, int32_t nbytes){
	uint8_t * buffer = (uint8_t*)buf;
  ready[process_flag] = 0;
	int i;
	for(i = 0; i < nbytes; i++){
		putc(buffer[i]);
	}
	//printf("%s", buf);
  write_len = nbytes;
  // memset(buf, 0, nbytes);
	return nbytes;
 }

/* int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes)
 * DESCRIPTION: reads screen to buf
 * Inputs: fd-- unused
           buf-- the buffer that we will write to
           nbytes-- how many bytes we want to write
 * Return Value: none
 * Function: reads the current line and puts it on buffer
 */
int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes){
	//set interrupts
  sti();
	//wait for enter
  while(!ready[process_flag]){
}
if(terminal_1.present){
	while(sched_count != 1){
	}


}
if(terminal_2.present){
	while(sched_count != 2){
	}

}
if(terminal_3.present){
	while(sched_count != 0){
	}
}
	//put the chars onto the buffer
	//memset(buf, '\0', BUFFSIZE);
	//printf("%s\n", buf);
  memcpy(buf,key_buff,BUFFSIZE);
	//check for exit, if exit reboot shell, zero is the first letter in key_buff, 1 is the second, etc...
	if(key_buff[0] == 'e' && key_buff[1] == 'x' && key_buff[2] == 'i' && key_buff[3] == 't'){
		if(terminal_1.present){
		 if(terminal_1.PID_array[0] == 0 && terminal_1.PID_array[1] == 0 && terminal_1.PID_array[2] == 0){
		 	memset(key_buff, 0, BUFFSIZE);
			global_flag[0] = 0;
		 	execute((uint8_t*)"shell");
		}
	 }
	 if(terminal_2.present){
		if(terminal_2.PID_array[0] == 0 && terminal_2.PID_array[1] == 0 && terminal_2.PID_array[2] == 0){
			memset(key_buff, 0, BUFFSIZE);
			global_flag[1] = 0;
			execute((uint8_t*)"shell");
		}
	}
	if(terminal_3.present){
		if(terminal_3.PID_array[0] == 0 && terminal_3.PID_array[1] == 0 && terminal_3.PID_array[2] == 0){
		 memset(key_buff, 0, BUFFSIZE);
		 global_flag[2] = 0;
		 execute((uint8_t*)"shell");
	 }
 }
}
	//check for fish, disable enter to preserve image, zero is the first letter in key_buff, 1 is the second, etc...
	if(key_buff[0] == 'f' && key_buff[1] == 'i' && key_buff[2] == 's' && key_buff[3] == 'h' && process_flag != 1){
		flag_enter = 1;
	}
  //clear the key_buff
  memset(key_buff, 0, BUFFSIZE);
	//flag_enter_for_pit = 0;
  //clear interrupts
  cli();
	return strlen(buf);
}
