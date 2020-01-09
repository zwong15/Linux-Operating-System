#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#include "types.h"

#define BLOCK_SIZE 4096
#define FOUR_BYTE 4
#define DIR_ENTRY_SIZE 64
#define FILE_NAME_SIZE 32
#define FILE_NAME_SIZE_MINUS_ONE 31
#define SHIFT_ONE_BYTE 8
#define SHIFT_TWO_BYTE 16
#define SHIFT_THREE_BYTE 24
#define MAX_DIR_NUM 63
#define ONE_MEM_LOCATION 1
#define TWO_MEM_LOCATION 2
#define THREE_MEM_LOCATION 3
#define MAX_NAME_SIZE 32
#define PCPMASK 0xFFE000



//function to initiliaze the boot block pointer
void file_init();

//funtion to open the file by name
extern int32_t file_open(const uint8_t* filename);

//function to close the file
extern int32_t file_close(int32_t fd);

//function to write to the file
extern int32_t file_write(int32_t fd, const void* buf, int32_t nbytes);

//function to read the file
extern int32_t file_read(int32_t fd, void* buf, int32_t nbytes);

//function to open the directory by name
int32_t directory_open(const uint8_t* filename);

//function to read the directory by pointer through read_dentry_by_name
int32_t directory_read(int32_t fd, void* buf, int32_t nbytes);

//function to write to directory
int32_t directory_write();

//function to close directory
int32_t directory_close();

//function to read data from an offset
int32_t read_data (uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length);

//struct for the entries within the directory
typedef struct dentry_t{
  // 24 reserved Bytes = 6 * 32 bits
  uint32_t reserved_5;
  uint32_t reserved_4;
  uint32_t reserved_3;
  uint32_t reserved_2;
  uint32_t reserved_1;
  uint32_t reserved_0;

  // inode # and filetype are 4 Bytes
  uint32_t inode_num;
  uint32_t file_type;

  // 32 Bytes for the file_name characters
  uint8_t name[32];

}dentry_t;

//funciton to read dentry struct by name
extern int32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry);
//function to read dentry struct by index
int32_t read_dentry_by_index (uint32_t index, dentry_t* dentry);
//function to read the files in the directory by index
int32_t directory_read_by_index(uint32_t ind ,uint32_t count, uint8_t* buf);




#endif
