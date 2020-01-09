#include "system_calls.h"
#include "rtc.h"
#include "keyboard.h"
#include "paging.h"
#include "lib.h"
#include "filesystem.h"
#include "x86_desc.h"
#include "multiboot.h"
#include "context_switch.h"
#include "terminal.h"

//Various blogabl flags and variables
int exception = 0;
int process_flag = -1;
uint32_t entry_point;
int dont_run = 0;
uint8_t global_flag[SIXW];
uint8_t execute_fix = 0;
extern tss_t tss;
extern uint32_t counter_del;
extern int8_t key_buff[BUFFSIZE];
extern unsigned int counter;
extern uint32_t flag_enter;
extern uint8_t shells_on_start;


/*
 * badcall_open()
 *   DESCRIPTION: bad call for a open system call
 *   INPUTS: filename
 *   RETURN VALUE: -1
 */
int32_t badcall_open(const uint8_t* filename){
  return -1;
}
/*
 * badcall_close()
 *   DESCRIPTION: bad call for a close system call
 *   INPUTS: file descriptor number
 *   RETURN VALUE: -1
 */
int32_t badcall_close(int32_t fd){
  return -1;
}
/*
 * badcall_read()
 *   DESCRIPTION: bad call for a read system call
 *   INPUTS: file descritor number, buffer of character to write, number of bytes written
 *   RETURN VALUE: -1
 */
int32_t badcall_read(int32_t fd, void* buf, int32_t nbytes){
  return -1;
}
/*
 * badcall_write()
 *   DESCRIPTION: bad call for a write system call
 *   INPUTS: file descritor number, buffer of character to write, number of bytes written
 *   RETURN VALUE: -1
 */
int32_t badcall_write(int32_t fd, const void* buf, int32_t nbytes){
  return -1;
}
/*Struct for stdin system calls*/
static sys_calls stdin = {
    badcall_open,
    badcall_close,
    terminal_read,
    badcall_write
};
/*Struct for stdout system calls*/
static sys_calls stdout = {
    badcall_open,
    badcall_close,
    badcall_read,
    terminal_write
};
/*Struct for rtc system calls*/
static sys_calls rtc = {
    rtc_open,
    rtc_close,
    rtc_read,
    rtc_write
};
/*Struct for directory system calls*/
static sys_calls directory = {
    directory_open,
    directory_close,
    directory_read,
    directory_write
};
/*Struct for filesystem system calls*/
static sys_calls filesystem = {
    file_open,
    file_close,
    file_read,
    file_write
};

/*
* halt(uint8_t status)
*   DESCRIPTION: halts the process
*   INPUTS: status
*   OUTPUTS: none
*   RETURN VALUE: 0
*   SIDE EFFECTS: halts the executing program
* returns control to execute, until last program
*/
int32_t halt(uint8_t status){
  cli();
  int i;
  int process_num;
  int z = 0;
  //obtain pointers to pcb
  if(terminal_1.present){
    for(z = 2; z >= 0; z--){
      if(terminal_1.PID_array[z] != 0){
        process_flag = terminal_1.PID_array[z];
        terminal_1.PID_array[z] = 0;
        // printf("pf: %d\n", process_flag);
        global_flag[process_flag] = 0;
        break;
      }
    }
  }
  if(terminal_2.present){
    for(z = 2; z >= 0; z--){
      if(terminal_2.PID_array[z] != 0){
        process_flag = terminal_2.PID_array[z];
        terminal_2.PID_array[z] = 0;
        global_flag[process_flag] = 0;
        break;
      }
    }
  }
  if(terminal_3.present){
    for(z = 2; z >= 0; z--){
      if(terminal_3.PID_array[z] != 0){
        process_flag = terminal_3.PID_array[z];
        terminal_3.PID_array[z] = 0;
        global_flag[process_flag] = 0;
        break;
      }
    }
    // printf("halting: %d\n", process_flag);

  }
  dont_run = 0;
      // printf("ALASKAN BULLWORN %d\n", status);
  // if(process_flag < 3){
  //   asm volatile(
  //   "jmp ENDOFHALT;"
  //   );
  // }
  // if(global_flag[0] == 0 && global_flag[1] == 0 && global_flag[2] == 0){
  //   return status;
  // }
  pcb * current_control_block;
  pcb * old_control_block;
  if(process_flag > 0){
    current_control_block = (pcb*)(EIGHTMB - (EIGHTKB *(process_flag + PARENTINCREMENT)));
  }
  //clear file descriptor
  int p = 0;

  while(p < NUMBEROFFILE){
    current_control_block->file_descriptor_t[p].pointer_jump = NULL;
    current_control_block->file_descriptor_t[p].inode = -1;
    current_control_block->file_descriptor_t[p].file_position = OFF;
    current_control_block->file_descriptor_t[p].flags = OFF;
    p++;
  }
  //decrement process_flag
  if(process_flag > 0){
    process_flag--;
  }
  if(terminal_1.present){

    // grab the process on terminal 1
    for(i = 3; i >= 1; i--){
      if(terminal_1.PID_array[i-1] != 0){
        process_num = terminal_1.PID_array[i-1];
        break;
      }
      else{
        process_num = 0;
      }
    }
  }

   if(terminal_2.present){

    // grab the process on terminal 2
    for(i = 3; i >= 1; i--){
      if(terminal_2.PID_array[i-1] != 0){
        process_num = terminal_2.PID_array[i-1];
        break;
      }
      else{
        process_num = 1;
      }
    }
  }

  if(terminal_3.present){

    // grab the process on terminal 3
    for(i = 3; i >= 1; i--){
      if(terminal_3.PID_array[i-1] != 0){
        process_num = terminal_3.PID_array[i-1];
        break;
      }
      else{
        process_num = 2;
      }
    }
  }
    old_control_block = (pcb*)(EIGHTMB - (EIGHTKB *(process_num + PARENTINCREMENT)));
  //remap and set esp
  if(process_flag > -1){
  map_128(old_control_block->pid);
  // page_dir[PROCESS_ENTRY].pointer = ((EIGHTMB + (old_control_block->pid * FOMB))>>12);
  // //map_128(process_num);
  // asm(
  //     "movl %cr3, %eax;"
  //     "movl %eax, %cr3;"
  // );

  tss.esp0 = current_control_block->esp;
  //clear the key_buff after halt and set counter to 0
  memset(key_buff, 0, BUFFSIZE);
  counter_del = counter;
  counter = 0;
  //enable enter again
  flag_enter = 0;

//push corresponding values
    asm volatile(
      "mov %0, %%eax;"
       "mov %1, %%ebp;"
       "mov %2, %%esp;"
      :
      : "r"((uint32_t)status), "r"(current_control_block->ebp), "r"(current_control_block->esp)
      : "%eax"
    );
    sti();
//jump back to execute
  asm volatile(
  "jmp ENDOFHALT;"
);
  }
return 0;
}

/*
* execute(const uint8_t* command)
*   DESCRIPTION: executes a process
*   INPUTS: command: string that is being executed
*   OUTPUTS: none
*   RETURN VALUE: 0
*   SIDE EFFECTS: executes the program to termination
*/
int32_t execute(const uint8_t* command){
  //reset exception flag back to 0
  cli();
  if(shells_on_start < 5){
    shells_on_start++;
  }
  exception = 0;
  int z = 0;
  //limit the processes to 2
  if(process_flag == 5){
    printf("Max Processes Reached. Please Exit.\n");
    return 0;
  }
  //initialize variables to be used

  pcb * parent_control_block;
  pcb * child1_control_block;
  pcb * child2_control_block;
  pcb * child3_control_block;
  pcb * child4_control_block;
  pcb * child5_control_block;
  uint8_t filename[FILENAMESIZE];
  int j, u;
  //fill filename with nulls initially
  for(j = 0; j < FILENAMESIZE; j++){
    filename[j] = '\0';
  }
  uint8_t arguments[MAXARGUMENT];
  int first_word = 0;
  uint32_t i = 0;
  uint32_t counter = 0;
  //check for null command
  if(command == NULL){
    return -1;
  }
  //fill arguments with nulls initially
  for(u = 0; u < MAXARGUMENT; u++){
    arguments[u] = '\0';
  }
  //parse arguments
  while(command[i] != '\0'){
    if(command[i] == ' '){
      first_word = 1;
    }
    if(first_word == 0){
      filename[i] = command[i];
    }
    if(command[i] != ' ' && first_word == 1){
      arguments[counter] = command[i];
      counter++;
    }
    i++;
  }
  //check to see if its executable
  dentry_t check;
  if(read_dentry_by_name((uint8_t*)filename, &check) == -1){
    return -1;
  }
  uint8_t data_buffer[FOURBYT];
  read_data(check.inode_num, 0, data_buffer, FOURBYT);
  if(data_buffer[0] != ELF1 || data_buffer[1] != ELF2 || data_buffer[2] != ELF3 || data_buffer[3] != ELF4){
    return -1;
  }
  //obtain entry point
  read_data(check.inode_num, OFFSETSEARCH, data_buffer, FOURBYT);
  entry_point = *(uint32_t*)data_buffer;
  //set up program paging and pcb pointer
  process_flag++;
  for(z = 0; z < SIXW; z++){
    if(global_flag[z] == 0){
      process_flag = z;
      global_flag[z] = 1;
      // printf("executing: %d\n", process_flag);
      break;
    }
  }
  if(process_flag > 2){
    if(terminal_1.present){
      for(z = 0; z < 3; z++){
        if(terminal_1.PID_array[z] == 0){
          terminal_1.PID_array[z] = process_flag;
          break;
        }
      }
    }
    if(terminal_2.present){
      for(z = 0; z < 3; z++){
        if(terminal_2.PID_array[z] == 0){
          terminal_2.PID_array[z] = process_flag;
          break;
        }
      }
    }
    if(terminal_3.present){
      for(z = 0; z < 3; z++){
        if(terminal_3.PID_array[z] == 0){
          terminal_3.PID_array[z] = process_flag;
          break;
        }
      }
    }
  }
  if(global_flag[3] == 1){
    dont_run = 1;
  }
  if(process_flag == 0){
    parent_control_block = (pcb*)(EIGHTMB - (EIGHTKB *(process_flag + PARENTINCREMENT)));
    uint32_t esp0;
    uint32_t ebp0;
    //obtain esp and store it
    asm volatile(
       "movl %%esp, %0;"
      :"=g"(esp0)
    );
    parent_control_block->esp = esp0;
    //obtain ebp and store it
    asm volatile(
       "movl %%ebp, %0;"
      :"=g"(ebp0)
    );
    parent_control_block->ebp = ebp0;
    map_128(process_flag);
  }
  if(process_flag == 1){
    child1_control_block = (pcb*)(EIGHTMB - (EIGHTKB *(process_flag + PARENTINCREMENT)));
    uint32_t esp0;
    uint32_t ebp0;
    //obtain esp and store it
    asm volatile(
       "movl %%esp, %0;"
      :"=g"(esp0)
    );
    child1_control_block->esp = esp0;
    //obtain ebp and store it
    asm volatile(
       "movl %%ebp, %0;"
      :"=g"(ebp0)
    );
    child1_control_block->ebp = ebp0;
    map_128(process_flag);

  }
  if(process_flag == 2){
    child2_control_block = (pcb*)(EIGHTMB - (EIGHTKB *(process_flag + PARENTINCREMENT)));
    uint32_t esp0;
    uint32_t ebp0;
    //obtain esp and store it
    asm volatile(
       "movl %%esp, %0;"
      :"=g"(esp0)
    );
    child2_control_block->esp = esp0;
    //obtain ebp and store it
    asm volatile(
       "movl %%ebp, %0;"
      :"=g"(ebp0)
    );
    child2_control_block->ebp = ebp0;
    map_128(process_flag);

  }
  if(process_flag == 3){
    child3_control_block = (pcb*)(EIGHTMB - (EIGHTKB *(process_flag + PARENTINCREMENT)));
    uint32_t esp0;
    uint32_t ebp0;
    //obtain esp and store it
    asm volatile(
       "movl %%esp, %0;"
      :"=g"(esp0)
    );
    child3_control_block->esp = esp0;
    //obtain ebp and store it
    asm volatile(
       "movl %%ebp, %0;"
      :"=g"(ebp0)
    );
    child3_control_block->ebp = ebp0;
    map_128(process_flag);

  }
  if(process_flag == 4){
    child4_control_block = (pcb*)(EIGHTMB - (EIGHTKB *(process_flag + PARENTINCREMENT)));
    uint32_t esp0;
    uint32_t ebp0;
    //obtain esp and store it
    asm volatile(
       "movl %%esp, %0;"
      :"=g"(esp0)
    );
    child4_control_block->esp = esp0;
    //obtain ebp and store it
    asm volatile(
       "movl %%ebp, %0;"
      :"=g"(ebp0)
    );
    child4_control_block->ebp = ebp0;
    map_128(process_flag);

  }
  if(process_flag == 5){
    child5_control_block = (pcb*)(EIGHTMB - (EIGHTKB *(process_flag + PARENTINCREMENT)));
    uint32_t esp0;
    uint32_t ebp0;
    //obtain esp and store it
    asm volatile(
       "movl %%esp, %0;"
      :"=g"(esp0)
    );
    child5_control_block->esp = esp0;
    //obtain ebp and store it
    asm volatile(
       "movl %%ebp, %0;"
      :"=g"(ebp0)
    );
    child5_control_block->ebp = ebp0;
    map_128(process_flag);

  }
  //user level program loader
  read_data(check.inode_num, 0, (uint8_t*)PROCCESS_OFFSET, MAXFILESIZE);
  //create pcb
  //store data into pcb
  if(process_flag == 0){
    parent_control_block->pid = process_flag;
    parent_control_block->ep = entry_point;
    parent_control_block->ss0 =  KERNEL_DS;

    int l;
    //store arguments into pcb
    for(l = 0; l < MAXARGUMENT; l++){
      parent_control_block->arg[l] = arguments[l];
    }
    parent_control_block->arg_size = counter;
    parent_control_block->pid = 0;
    int m = 0;
    //initiliaze initial file descriptor
    while(m < NUMBEROFFILE){
      parent_control_block->file_descriptor_t[m].pointer_jump = NULL;
      parent_control_block->file_descriptor_t[m].inode = -1;
      parent_control_block->file_descriptor_t[m].file_position = OFF;
      parent_control_block->file_descriptor_t[m].flags = OFF;
      m++;
    }
    //stdin and stdout
    parent_control_block->file_descriptor_t[0].pointer_jump = (uint32_t*)&stdin;
    parent_control_block->file_descriptor_t[0].flags = ON;
    parent_control_block->file_descriptor_t[1].pointer_jump = (uint32_t*)&stdout;
    parent_control_block->file_descriptor_t[1].flags = ON;
  }
  //create pcb
  //store data into pcb
  if(process_flag == 1){
    child1_control_block->pid = process_flag;
    child1_control_block->ep = entry_point;
    child1_control_block->ss0 =  KERNEL_DS;
    int r;
    for(r = 0; r < MAXARGUMENT; r++){
      child1_control_block->arg[r] = arguments[r];
    }
    child1_control_block->arg_size = counter;
    child1_control_block->pid = 1;
    int p = 0;
    //initialize file descriptor
    while(p < NUMBEROFFILE){
      child1_control_block->file_descriptor_t[p].pointer_jump = NULL;
      child1_control_block->file_descriptor_t[p].inode = -1;
      child1_control_block->file_descriptor_t[p].file_position = OFF;
      child1_control_block->file_descriptor_t[p].flags = OFF;
      p++;
    }
    //stdin and stdout
    child1_control_block->file_descriptor_t[0].pointer_jump = (uint32_t*)&stdin;
    child1_control_block->file_descriptor_t[0].flags = ON;
    child1_control_block->file_descriptor_t[1].pointer_jump = (uint32_t*)&stdout;
    child1_control_block->file_descriptor_t[1].flags = ON;
  }
  if(process_flag == 2){
    child2_control_block->pid = process_flag;
    child2_control_block->ep = entry_point;
    child2_control_block->ss0 =  KERNEL_DS;
    int r;
    for(r = 0; r < MAXARGUMENT; r++){
      child2_control_block->arg[r] = arguments[r];
    }
    child2_control_block->arg_size = counter;
    child2_control_block->pid = 2;
    int p = 0;
    //initialize file descriptor
    while(p < NUMBEROFFILE){
      child2_control_block->file_descriptor_t[p].pointer_jump = NULL;
      child2_control_block->file_descriptor_t[p].inode = -1;
      child2_control_block->file_descriptor_t[p].file_position = OFF;
      child2_control_block->file_descriptor_t[p].flags = OFF;
      p++;
    }
    //stdin and stdout
    child2_control_block->file_descriptor_t[0].pointer_jump = (uint32_t*)&stdin;
    child2_control_block->file_descriptor_t[0].flags = ON;
    child2_control_block->file_descriptor_t[1].pointer_jump = (uint32_t*)&stdout;
    child2_control_block->file_descriptor_t[1].flags = ON;
  }
  if(process_flag == 3){
    child3_control_block->pid = process_flag;
    child3_control_block->ep = entry_point;
    child3_control_block->ss0 =  KERNEL_DS;
    int r;
    for(r = 0; r < MAXARGUMENT; r++){
      child3_control_block->arg[r] = arguments[r];
    }
    child3_control_block->arg_size = counter;
    child3_control_block->pid = 3;
    int p = 0;
    //initialize file descriptor
    while(p < NUMBEROFFILE){
      child3_control_block->file_descriptor_t[p].pointer_jump = NULL;
      child3_control_block->file_descriptor_t[p].inode = -1;
      child3_control_block->file_descriptor_t[p].file_position = OFF;
      child3_control_block->file_descriptor_t[p].flags = OFF;
      p++;
    }
    //stdin and stdout
    child3_control_block->file_descriptor_t[0].pointer_jump = (uint32_t*)&stdin;
    child3_control_block->file_descriptor_t[0].flags = ON;
    child3_control_block->file_descriptor_t[1].pointer_jump = (uint32_t*)&stdout;
    child3_control_block->file_descriptor_t[1].flags = ON;
  }
  if(process_flag == 4){
    child4_control_block->pid = process_flag;
    child4_control_block->ep = entry_point;
    child4_control_block->ss0 =  KERNEL_DS;
    int r;
    for(r = 0; r < MAXARGUMENT; r++){
      child4_control_block->arg[r] = arguments[r];
    }
    child4_control_block->arg_size = counter;
    child4_control_block->pid = 4;
    int p = 0;
    //initialize file descriptor
    while(p < NUMBEROFFILE){
      child4_control_block->file_descriptor_t[p].pointer_jump = NULL;
      child4_control_block->file_descriptor_t[p].inode = -1;
      child4_control_block->file_descriptor_t[p].file_position = OFF;
      child4_control_block->file_descriptor_t[p].flags = OFF;
      p++;
    }
    //stdin and stdout
    child4_control_block->file_descriptor_t[0].pointer_jump = (uint32_t*)&stdin;
    child4_control_block->file_descriptor_t[0].flags = ON;
    child4_control_block->file_descriptor_t[1].pointer_jump = (uint32_t*)&stdout;
    child4_control_block->file_descriptor_t[1].flags = ON;
  }
  if(process_flag == 5){
    child5_control_block->pid = process_flag;
    child5_control_block->ep = entry_point;
    child5_control_block->ss0 =  KERNEL_DS;
    int r;
    for(r = 0; r < MAXARGUMENT; r++){
      child5_control_block->arg[r] = arguments[r];
    }
    child5_control_block->arg_size = counter;
    child5_control_block->pid = 5;
    int p = 0;
    //initialize file descriptor
    while(p < NUMBEROFFILE){
      child5_control_block->file_descriptor_t[p].pointer_jump = NULL;
      child5_control_block->file_descriptor_t[p].inode = -1;
      child5_control_block->file_descriptor_t[p].file_position = OFF;
      child5_control_block->file_descriptor_t[p].flags = OFF;
      p++;
    }
    //stdin and stdout
    child5_control_block->file_descriptor_t[0].pointer_jump = (uint32_t*)&stdin;
    child5_control_block->file_descriptor_t[0].flags = ON;
    child5_control_block->file_descriptor_t[1].pointer_jump = (uint32_t*)&stdout;
    child5_control_block->file_descriptor_t[1].flags = ON;
  }

  //set esp and ss
  tss.esp0 = EIGHTMB-(EIGHTKB*process_flag)-FOURBYT;
  tss.ss0 = KERNEL_DS;
  sti();
  //context switch
  privilege_switch_asm();

  //jump position for halt
asm volatile(
"ENDOFHALT: ;"
);
//check to see if an exception occured
if(exception == 1){
  return EXCEPTIONNUMBER;
}
//leave and return
asm volatile(
  "LEAVE;"
  "RET;"
);

  return 0;
}
/*
 * open()
 *   DESCRIPTION: Provides access to the file system. It finds the correct directory
 *                entry corresponding to the file name and allocates an unused
 *                file descriptor and set up any data necessary for the descriptor.
 *   INPUTS: filename
 *   OUTPUTS: -1 on failure, 2 through 8 success
 *   RETURN VALUE: file descriptor number
 *   SIDE EFFECTS: allocates an unused file descriptor
 */
int32_t open(const uint8_t* filename){
  /*initialize variables*/
  dentry_t dentry;
  pcb * pcb_open;
  int i;
  sys_calls* system_call;
  file_descriptor_table fd;
  int fd_num = -1;
  //obtain correct pcb
  if(process_flag == -1){
    pcb_open = (pcb*)(EIGHTMB - (EIGHTKB * (process_flag + CHILDINCREMENT)));
  }
  if(process_flag != -1){
    pcb_open = (pcb*)(EIGHTMB - (EIGHTKB *(process_flag + PARENTINCREMENT)));
  }
  /*check if the filename is a valid entry*/
  if(read_dentry_by_name(filename, &dentry) != 0){
      return -1;
  }
  /*Check for earliest unused file descriptor*/
  for(i = CHILDINCREMENT; i < NUMBEROFFILE; ++i){
    /*Check if file descriptor is available*/
      if(pcb_open->file_descriptor_t[i].flags == 0){
          fd_num = i;
          fd.inode = 0;
          /*determine corresponding file type*/
          switch(dentry.file_type){
              case 0:
                  fd.pointer_jump = (uint32_t*)&rtc;
                  break;
              case 1:
                  pcb_open->statics_t[i].directory_files_finished = 1;
                  fd.pointer_jump = (uint32_t*)&directory;
                  break;
              case 2:
                  fd.inode = dentry.inode_num;
                  fd.pointer_jump = (uint32_t*)&filesystem;
                  break;
              default:
                  return -1;
          }
          /*Update member structure values and mark file descriptor as used*/
          fd.file_position = 0;
          fd.flags = 1;
          pcb_open->file_descriptor_t[fd_num] = fd;
          break;
        }
  }
  /*If no file descriptor is available return failure*/
  if(fd_num == -1){
    return -1;
  }
  /*Obtain desired system call*/
  system_call = (sys_calls*)(pcb_open->file_descriptor_t[fd_num].pointer_jump);
  /*Ensure the system call does not generate an error*/
  if(system_call->open(filename) == -1){
      return -1;
  }
  /*return file descriptor number*/
  return fd_num;

}
/*
 * close()
 *   DESCRIPTION: Closes the specified file descriptor and makes it an avaiable
 *                file descriptor for later calls for open
 *   INPUTS: file desciptor number
 *   RETURN VALUE: -1 on failure, 0 on success
 *   SIDE EFFECTS: closes a file descriptor and marks it available.
 */
int32_t close(int32_t fd){
  /*Initialize variables*/
  pcb * pcb_close;
  /*Point the structure to current address of pcb*/
  pcb_close = (pcb*)(EIGHTMB - (EIGHTKB * (process_flag + PARENTINCREMENT)));
  /*Ensure valid descriptor number*/
  if(fd < 0 || fd >= NUMBEROFFILE){
      return -1;
  }
  /*Check to make sure file descriptor is present*/
  if(pcb_close->file_descriptor_t[fd].flags == 0){
      return -1;
  }
  /*temp variable to hold system call*/
  sys_calls* system_call;
  /*Obtain the desired system call*/
  system_call = (sys_calls*)(pcb_close->file_descriptor_t[fd].pointer_jump);
  /*Ensure corresonding system call does not generate an error*/
  if(system_call->close(fd) == -1){
      return -1;
  }
  pcb_close->file_descriptor_t[fd].pointer_jump = NULL;
  pcb_close->file_descriptor_t[fd].file_position = 0;
  pcb_close->file_descriptor_t[fd].flags = 0;
  return 0;
}

/*
 * read()
 *   DESCRIPTION: Reads data from keyboard, a file, RTC, or directory. It returns
 *                the number of bytes read.
 *   INPUTS: file desciptor number, buffer to put the characters, and number of bytes read
 *   RETURN VALUE: -1 on failure, else number of bytes read
 *   SIDE EFFECTS: reads data
 */
int32_t read(int32_t fd, void* buf, int32_t nbytes){
  /*Initialize variables*/
  pcb * pcb_read;
  /*point to current address of pcb*/
  pcb_read = (pcb*)(EIGHTMB - (EIGHTKB * (process_flag + PARENTINCREMENT)));
  /*Ensure it is a valid file descriptor*/
  if(fd < 0 || fd >= NUMBEROFFILE){
      return -1;
  }
  /*Ensure file descriptor is present*/
  if(pcb_read->file_descriptor_t[fd].flags == 0){
      return -1;
  }
    /*Return the number of bytes read from the desired read system call*/
  return ((sys_calls*)(pcb_read->file_descriptor_t[fd].pointer_jump))->read(fd, buf, nbytes);

}
/*
 * write()
 *   DESCRIPTION: Writes data to the terminal or to a device (RTC). For the terminal, all data will
 *                be displayed to the screen immediately. For the RTC it should only accept a 4-Byte
 *                integer specifying the desired interrupt rate.
 *   INPUTS: file descriptor number, buffer of characters to write to screen, number of bytes written
 *   RETURN VALUE: -1 on failure, else number of bytes written
 *   SIDE EFFECTS: writes to screen or device
 */
int32_t write(int32_t fd, const void* buf, int32_t nbytes){
  /*Initialize variables*/
  pcb * pcb_write;
  /*Point to address of current pcb*/
  pcb_write = (pcb*)(EIGHTMB - (EIGHTKB * (process_flag + PARENTINCREMENT)));
  /*ensure a file descriptor number is given*/
  if(fd < 0 || fd >= NUMBEROFFILE){
      return -1;
  }
  /*Ensure file descriptor is present*/
  if(pcb_write->file_descriptor_t[fd].flags == 0){
      return -1;
  }
  /*Return number of bytes from the desired write system call*/
  return ((sys_calls*)(pcb_write->file_descriptor_t[fd].pointer_jump))->write(fd, buf, nbytes);

}

/*
 *   getargs(uint8_t* buf, int32_t nbytes)
 *   DESCRIPTION: Reads the program's command line arguments into a user-level
 *                buffer
 *   INPUTS: buf - buffer to hold the command line arguments
 *           nbytes - number of bytes of buffer
 *   RETURN VALUE: -1 failure, 0 for success
 *   SIDE EFFECTS: none
 */
int32_t getargs(uint8_t* buf, int32_t nbytes){

    /*initialize loop variable*/
    int i;

    /*Declare pcb*/
    pcb * pcb_getargs;

    /*Set pcb to exisiting pcb*/
    pcb_getargs = (pcb*)(EIGHTMB - (EIGHTKB * (process_flag + PARENTINCREMENT)));

    /*Boundary check, check to make sure buffer does not point to NULL*/
    if(buf == NULL){
        return -1;
    }

    /*Make sure argument size does not exceed the buffer size*/
    if(pcb_getargs->arg_size > nbytes){
        return -1;
    }

    /*Initialize buffer*/
    for(i = 0; i < BUFSIZE; i++){
        buf[i] = '\0';
    }

    /*Move arguments into buffer*/
    for(i = 0; i < MAXARGUMENT; i++){
      buf[i] = pcb_getargs->arg[i];
    }

    return 0;

}

/*
 *   vidmap(uint8_t** screen_start)
 *   DESCRIPTION: Sets up the screen_start to point to the video memory through
 *                a pointer that we created
 *   INPUTS: screen_start - double pointer we want to point to video memory
 *   RETURN VALUE: -1 for invalid address, 0 for success
 *   SIDE EFFECTS: none
 */
int32_t vidmap(uint8_t** screen_start){
  // if the screen_start is not in valid range in our virtual memory, return -1
  if(screen_start < (uint8_t**)BOTRANGE || screen_start >= (uint8_t**)TOPRANGE || screen_start == NULL){
    return -1;
  }


  // set the user_mem_pointer to our page directory entry location
  uint8_t* user_mem_pointer = (uint8_t*)VID_MEM_OFFSET;

  // checking for dereferenced NULL
  if(*user_mem_pointer == NULL){
    return -1;
  }
  // set the dereferenced screen_start to our user_mem_pointer
  *screen_start = (user_mem_pointer);
  return VID_MEM_OFFSET;
}

/*
 *   set_handler(int32_t signum, void* handler_address)
 *   DESCRIPTION: Extra Credit system call. Not currently implemented
 *   INPUTS: signum - signal number
 *           handler_address - address of handler
 *   RETURN VALUE: -1 not implemented yet
 *   SIDE EFFECTS: none
 */
int32_t set_handler(int32_t signum, void* handler_address){
  return -1;
}

/*
 *   sigreturn(void)
 *   DESCRIPTION: Extra Credit system call. Not currently implemented
 *   RETURN VALUE: -1 not implemented yet
 *   SIDE EFFECTS: none
 */
int32_t sigreturn(void){
    return -1;
}
