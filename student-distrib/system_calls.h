#ifndef _SYSTEM_CALLS_H
#define _SYSTEM_CALLS_H

#include "syscall_handler.h"
#include "rtc.h"
#include "keyboard.h"
#include "paging.h"
#include "lib.h"
#include "filesystem.h"
#include "x86_desc.h"
#include "multiboot.h"
#include "context_switch.h"
#include "tss_switch.h"


#define PROCCESS_OFFSET     0x08048000
#define VID_MEM_OFFSET      0x084B8000
#define EIGHTMB             0x800000
#define EIGHTKB             0x2000
#define OFF                 0x0000
#define ON                  0x0001
#define MAXFILESIZE         0x3B8000
#define MAXARGUMENT         128
#define OFFSETSEARCH        24
#define ELF1                0x7f
#define ELF2                0x45
#define ELF3                0x4c
#define ELF4                0x46
#define BOTRANGE            0x8000000
#define TOPRANGE            0x8400000
#define FILENAMESIZE        32
#define BUFSIZE             1024
#define NUMBEROFFILE        8
#define FOURBYT             4
#define EXCEPTIONNUMBER     256
#define CHILDINCREMENT      2
#define PARENTINCREMENT     1
#define SIXW                 6

/*Struct of system calls function pointers to determine
  which system call is desired*/
typedef struct sys_calls{
    int32_t (*open)(const uint8_t* filename);
    int32_t (*close)(int32_t fd);
    int32_t (*read)(int32_t fd, void* buf, int32_t nbytes);
    int32_t (*write)(int32_t fd, const void* buf, int32_t nbytes);
} sys_calls;

/* This is a file descriptor  It goes in the PCB. */
typedef struct file_descriptor_table{
  uint32_t * pointer_jump;
  uint32_t inode;
  uint32_t file_position;
  uint32_t flags;
}file_descriptor_table;
/* This is a struct for statics  It goes in the PCB. */
typedef struct statics{
  uint32_t read_bytes;
  uint8_t * read_start_of_db_ptr;
  uint8_t* inode_pointer;
  uint8_t* cur_datablock_ptr;
  uint32_t num_inodes;
  uint32_t num_data_blocks;
  dentry_t cur_dentry;
  uint32_t datablocks_filled;
  module_t* mod;
  uint8_t* boot_block_ptr;
  uint8_t recognized;
  uint8_t interrupt_flag;
  uint8_t* directory_ptr;
  uint32_t total_files_read;
  uint32_t directory_files_finished;
  uint32_t file_size;
  uint32_t total_bytes_read;
}statics;

/* This is the PCB struct. */
typedef struct pcb{
  file_descriptor_table file_descriptor_t[NUMBEROFFILE];
  statics statics_t[NUMBEROFFILE];
  uint32_t pid;
  uint8_t arg[MAXARGUMENT];
  uint32_t esp;
  uint32_t ss0;
  uint32_t ebp;
  uint32_t ep;
  uint32_t arg_size;
}pcb;


/*Function headers for each file are specified in .c file*/
//bad calls for various system calls
extern int32_t badcall_open(const uint8_t* filename);
extern int32_t badcall_close(int32_t fd);
extern int32_t badcall_read(int32_t fd, void* buf, int32_t nbytes);
extern int32_t badcall_write(int32_t fd, const void* buf, int32_t nbytes);

//halts the process
extern int32_t halt(uint8_t status);

//executes a process
extern int32_t execute(const uint8_t* command);

//Reads data from keyboard, a file, RTC, or directory. It returns
//the number of bytes read.
extern int32_t read(int32_t fd, void* buf, int32_t nbytes);

//Writes data to the terminal or to a device (RTC). For the terminal, all data will
//be displayed to the screen immediately. For the RTC it should only accept a 4-Byte
//integer specifying the desired interrupt rate.
extern int32_t write(int32_t fd, const void* buf, int32_t nbytes);

//Provides access to the file system. It finds the correct directory
//entry corresponding to the file name and allocates an unused
//file descriptor and set up any data necessary for the descriptor.
extern int32_t open(const uint8_t* filename);

//Closes the specified file descriptor and makes it an avaiable
//file descriptor for later calls for open
extern int32_t close(int32_t fd);

//Reads the program's command line arguments into a user-level
//buffer
extern int32_t getargs(uint8_t* buf, int32_t nbytes);

//Sets up the screen_start to point to the video memory through
//a pointer that we created
extern int32_t vidmap(uint8_t** screen_start);

//Extra Credit system call. Not currently implemented
extern int32_t set_handler(int32_t signum, void* handler_address);

//Extra Credit system call. Not currently implemented
extern int32_t sigreturn(void);

#endif
