/* schedule.c - Functions to interact with the scheduler */

#include "schedule.h"
#include "keyboard.h"
#include "system_calls.h"

extern int process_flag;

int32_t switch_screen(unsigned char scan_code){
  pcb * current_control_block;
  if(scan_code == F1){
    current_control_block = (pcb*)(EIGHTMB - (EIGHTKB *(process_flag + PARENTINCREMENT)));
    asm volatile(
       "mov %0, %%ebp;"
       "mov %1, %%esp;"
      :
      : "r"(current_control_block->ebp), "r"(current_control_block->esp)
    );
    //set esp and ss
    tss.esp0 = EIGHTMB-(EIGHTKB*process_flag)-FOURBYT;
    tss.ss0 = KERNEL_DS;
    sti();
    //context switch
    privilege_switch_asm();
  }
  if(scan_code == F2){
    current_control_block = (pcb*)(EIGHTMB - (EIGHTKB *(process_flag + PARENTINCREMENT)));
    asm volatile(
       "mov %0, %%ebp;"
       "mov %1, %%esp;"
      :
      : "r"(current_control_block->ebp), "r"(current_control_block->esp)
    );
    //set esp and ss
    tss.esp0 = EIGHTMB-(EIGHTKB*process_flag)-FOURBYT;
    tss.ss0 = KERNEL_DS;
    sti();
    //context switch
    privilege_switch_asm();
  }
  if(scan_code == F3){
    current_control_block = (pcb*)(EIGHTMB - (EIGHTKB *(process_flag + PARENTINCREMENT)));
    asm volatile(
       "mov %0, %%ebp;"
       "mov %1, %%esp;"
      :
      : "r"(current_control_block->ebp), "r"(current_control_block->esp)
    );
    //set esp and ss
    tss.esp0 = EIGHTMB-(EIGHTKB*process_flag)-FOURBYT;
    tss.ss0 = KERNEL_DS;
    sti();
    //context switch
    privilege_switch_asm();
  }
  return 0;
}
