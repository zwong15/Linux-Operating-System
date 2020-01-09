#include "filesystem.h"
#include "multiboot.h"
#include "lib.h"
#include "x86_desc.h"
#include "system_calls.h"

// our dentry struct
static dentry_t cur_dentry;

// pointer for the module struct
static module_t* mod;

// boot_block_ptr holds the pointer to the boot block
static uint8_t* boot_block_ptr;


/*
* read_dentry_by_name(const uint8_t* fname, dentry_t* dentry)
*   DESCRIPTION: finds a file by the fname passed in and if it exists,
*                adds its information to cur_dentry
*   INPUTS: fname - pointer to string holding the name of the file we are looking
*                   for
*           dentry - the pointer to our dentry struct to update
*   OUTPUTS: none
*   RETURN VALUE: 0 on success, -1 on failure
*   SIDE EFFECTS: adds information about the file to cur_dentry
*/
int32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry){
    int i;
    int32_t check;

    //if the fname is a NULL pointer, return -1 for fail
    if(fname == NULL){
      printf("NULL pointer");
      return -1;
    }

    // put the pointer to the boot block into cur_address
    uint8_t * cur_address = boot_block_ptr;

    // put the number of chars in fname into fname_size
    int32_t fname_size = strlen((int8_t*)fname);

    // if the fname is larger than 32 bytes, return -1
    if(fname_size > MAX_NAME_SIZE){
      printf("name is too large\n");
      return -1;
    }

    // get the number of total directory entries
    uint32_t dir_num = ((*cur_address)) + ((*(cur_address+ONE_MEM_LOCATION)) << SHIFT_ONE_BYTE) + ((*(cur_address+TWO_MEM_LOCATION)) << SHIFT_TWO_BYTE) + (*(cur_address+THREE_MEM_LOCATION) << SHIFT_THREE_BYTE);

    // if we have over 63 directory entries, return -1
    if(dir_num > MAX_DIR_NUM){
      return -1;
    }

    for(i = 0; i < dir_num; i++){
      // go to the correct location for the next directory entry
      cur_address += DIR_ENTRY_SIZE;

      // compare the fname to the name in memory and if they do not match up,
      // go to the next directory entry
      check = strncmp((int8_t*)fname, (int8_t*)cur_address, (uint8_t)fname_size);
      if(check != 0){
        continue;
      }

      // we need to check if the size of fname is 32 bytes or if the next
      // char in memory is the end of string
      if(fname_size != MAX_NAME_SIZE && *(cur_address+fname_size) != '\0'){
        continue;
      }

      int a;
      for(a = 0; a < FILE_NAME_SIZE; a++){
        dentry->name[a] = '\0';
      }

      int b;
      for(b = 0; b < FILE_NAME_SIZE; b++){
        dentry->name[b] = *(cur_address +(FILE_NAME_SIZE_MINUS_ONE-b));
      }


      // put the file type into dentry
      dentry->file_type = *(cur_address+ FILE_NAME_SIZE);

      // put the inode number into dentry
      dentry->inode_num = (*(cur_address + FILE_NAME_SIZE + FOUR_BYTE)) + (*(cur_address + FILE_NAME_SIZE + FOUR_BYTE+ONE_MEM_LOCATION) << SHIFT_ONE_BYTE) + (*(cur_address + FILE_NAME_SIZE + FOUR_BYTE+TWO_MEM_LOCATION) << SHIFT_TWO_BYTE) + (*(cur_address + FILE_NAME_SIZE + FOUR_BYTE+THREE_MEM_LOCATION) << SHIFT_THREE_BYTE);
      return 0;

    }

    // we did not find the directory entry with that name
    return -1;
}

/*
* file_init()
*   DESCRIPTION: initializes the filesystem by setting the pointer to the bootblock
*   INPUTS: none
*   OUTPUTS: none
*   RETURN VALUE: none
*   SIDE EFFECTS: sets the boot_block_ptr static variable to point to the bootblock
*/
void file_init(){
  extern multiboot_info_t * mbi;
  mod =(module_t*) mbi->mods_addr;
  boot_block_ptr = (uint8_t*)mod->mod_start;
}

/*
* file_open(uint8_t* name)
*   DESCRIPTION: opens a file and sets static variables to begin reading a file
*   INPUTS: name - the pointer to the name of file to open
*   OUTPUTS: none
*   RETURN VALUE: returns 0 if success and -1 if failed
*   SIDE EFFECTS: sets static variables to values corresponding to the file if
*                 the file exists
*/
int32_t file_open(const uint8_t* filename){

    // call read_dentry_by_name and if the file was not found, set recognize low
    // and return -1
     if(read_dentry_by_name(filename, &cur_dentry) == -1){
       //recognized = 0;
       return -1;
     }

     return 0;

}


/*
* file_close()
*   DESCRIPTION: closes a file
*   INPUTS: none
*   OUTPUTS: none
*   RETURN VALUE: returns 0
*   SIDE EFFECTS: set recognized to 0 so we cannot read the directory
*/
int32_t file_close(int32_t fd){
  // set recognized to 0 so that we cannot read it
  //recognized = 0;
  return 0;
}

/*
* file_write()
*   DESCRIPTION: writes to a file
*   INPUTS: none
*   OUTPUTS: none
*   RETURN VALUE: returns -1 since we have a read-only file system
*   SIDE EFFECTS: none
*/
int32_t file_write(int32_t fd, const void* buf, int32_t nbytes){
  return -1;
}



/*
* directory_open(uint8_t* name)
*   DESCRIPTION: opens the directory
*   INPUTS: name - pointer to the name of the directory to look for
*   OUTPUTS: none
*   RETURN VALUE: 0 if found the file and succeeded and -1 if fail
*   SIDE EFFECTS: sets static variables
*/
int32_t directory_open(const uint8_t* filename){

  // if the file was not found, set recognized low and return -1
  if(read_dentry_by_name(filename, &cur_dentry) == -1){
    return -1;
  }

  // if the file type was not a directory type file, return -1
  if(cur_dentry.file_type != 1){
    printf("not a directory\n");
    return -1;
  }
  return 0;

}

/*
* directory_read(uint32_t count, uint8_t* buf)
*   DESCRIPTION: reads the filenames from the directory
*   INPUTS: count - how many bytes to read
            buf - pointer to buffer to put the bytes that were read
*   OUTPUTS: none
*   RETURN VALUE: returns number of bytes read or 0 if finished the file name
                  and -1 if could not read file
*   SIDE EFFECTS: prints file name to terminal
*/
int32_t directory_read(int32_t fd, void* buf, int32_t nbytes){
  //type cast buffer
    uint8_t* buffer = (uint8_t*)buf;

    // set pcb_ptr to point to beginning of the pcb
    pcb* pcb_ptr = (pcb*)(tss.esp0 & PCPMASK);

    // set up pointers and base values
    uint32_t file_pos = pcb_ptr->file_descriptor_t[fd].file_position;
    uint32_t files_read = pcb_ptr->statics_t[fd].directory_files_finished;
    uint8_t * cur_address = boot_block_ptr;
    uint32_t dir_num = ((*cur_address)) + ((*(cur_address+ONE_MEM_LOCATION)) << SHIFT_ONE_BYTE) + ((*(cur_address+TWO_MEM_LOCATION)) << SHIFT_TWO_BYTE) + (*(cur_address+THREE_MEM_LOCATION) << SHIFT_THREE_BYTE);
    //if we read all the files finish, -1 because dir starts at 1
    if(files_read -1 >= dir_num){
      return 0;
    }

    //initialize variables
    int i = 0;
    int j;

    uint32_t chars_read = 0;// = 1;

    //go to the correct starting address
    while(i < files_read){
      cur_address += DIR_ENTRY_SIZE;
      i++;
    }

    // put null into buffer
    for(j = 0; j < FILE_NAME_SIZE; j++){
      buffer[j] = '\0';
    }

    // go through the chars in buf nbyte times
    for(i = 0; i < nbytes; i++){

      //if we get to a null, we are at the 32nd position, or we have already read 31 bytes
      if(*(cur_address + file_pos + i) == '\0' || file_pos+i > FILE_NAME_SIZE_MINUS_ONE || chars_read > FILE_NAME_SIZE_MINUS_ONE){
        //set pcb values and return
        pcb_ptr->statics_t[fd].directory_files_finished++;
        pcb_ptr->file_descriptor_t[fd].file_position = 0;
        return chars_read;
      }
      //put character in buff and increment chars_read
      buffer[i] = *(cur_address + file_pos + i);
      chars_read++;
    }

    // if we read all 32 bytes, we set the file_pos to 0 and return
    if(chars_read == FILE_NAME_SIZE){
      pcb_ptr->statics_t[fd].directory_files_finished++;
      pcb_ptr->file_descriptor_t[fd].file_position = 0;
      return chars_read;
    }

    // adjust the file_pos and return
    pcb_ptr->statics_t[fd].directory_files_finished++;
    pcb_ptr->file_descriptor_t[fd].file_position += nbytes;
    return chars_read;
  }




/*
* directory_write()
*   DESCRIPTION: writes to a directory
*   INPUTS: none
*   OUTPUTS: none
*   RETURN VALUE: returns -1 since we have a read-only file system
*   SIDE EFFECTS: none
*/
int32_t directory_write(){
  return -1;
}


/*
* directory_close()
*   DESCRIPTION: closes a file
*   INPUTS: none
*   OUTPUTS: none
*   RETURN VALUE: returns 0
*   SIDE EFFECTS: set recognized to 0 so we cannot read the directory
*/
int32_t directory_close(){
  return 0;
}

 /*
 * read_dentry_by_index (uint32_t index, dentry_t* dentry)
 *   DESCRIPTION: reads the dentry by index.
 *   INPUTS: index - the index in regards to the directory
 *           dentry - the directory that we are accessing
 *   OUTPUTS: none
 *   RETURN VALUE: 0 on success, -1 on failure
 *   SIDE EFFECTS: assigns the inode number, file type, and name
 *                 to the directory entry
 */
int32_t read_dentry_by_index (uint32_t index, dentry_t* dentry){

  // put the pointer to the boot block into cur_address
  uint8_t * cur_address = boot_block_ptr;

  // get the number of directory entries
  uint32_t dir_num = ((*cur_address)) + ((*(cur_address+ONE_MEM_LOCATION)) << SHIFT_ONE_BYTE) + ((*(cur_address+TWO_MEM_LOCATION)) << SHIFT_TWO_BYTE) + (*(cur_address+THREE_MEM_LOCATION) << SHIFT_THREE_BYTE);
  //check to see that index is valid
  if(index < 0 || index >= dir_num){
    return -1;
  }
  cur_address = cur_address + ((index + 1) * DIR_ENTRY_SIZE);

    int d;
    for(d = 0; d < 32; d++){
      dentry->name[d] = *(cur_address + 31-d);
    }

//set the file type
    dentry->file_type = *(cur_address+ FILE_NAME_SIZE);
//set the inode number
    dentry->inode_num = (*(cur_address + FILE_NAME_SIZE + FOUR_BYTE)) + (*(cur_address + FILE_NAME_SIZE + FOUR_BYTE+ONE_MEM_LOCATION) << SHIFT_ONE_BYTE) + (*(cur_address + FILE_NAME_SIZE + FOUR_BYTE+TWO_MEM_LOCATION) << SHIFT_TWO_BYTE) + (*(cur_address + FILE_NAME_SIZE + FOUR_BYTE+THREE_MEM_LOCATION) << SHIFT_THREE_BYTE);
    //return 0 upon success
return 0;

}

int32_t read_data (uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length){
  // keep track of how many bytes we have read
  uint32_t i = 0;

  // set the number of inodes
  uint32_t num_inodes2 = (*(boot_block_ptr + FOUR_BYTE)) + (*(boot_block_ptr + FOUR_BYTE +ONE_MEM_LOCATION) << SHIFT_ONE_BYTE)+(*(boot_block_ptr + FOUR_BYTE+TWO_MEM_LOCATION) << SHIFT_TWO_BYTE)+(*(boot_block_ptr + FOUR_BYTE+THREE_MEM_LOCATION) << SHIFT_THREE_BYTE);

  // set the pointer to inode block
  uint8_t * inode_pointer2 = boot_block_ptr + (inode+1) * BLOCK_SIZE;

  // See how many bytes this file has
  uint32_t file_size = (*(inode_pointer2)) +(*(inode_pointer2+ONE_MEM_LOCATION) << SHIFT_ONE_BYTE) +(*(inode_pointer2+TWO_MEM_LOCATION) << SHIFT_TWO_BYTE) + (*(inode_pointer2+THREE_MEM_LOCATION) << SHIFT_THREE_BYTE);

  // if the offset is greater than the total size of the file, return 0
  if(offset >= file_size){
    return 0;
  }

  // total number of datablocks in this file. Add one since we want the ceiling
  uint32_t num_total_datablocks = (file_size/BLOCK_SIZE) + 1;

  // holds the offset of the number of bytes in the last data block used
  uint32_t num_total_offset = file_size%BLOCK_SIZE;

  // holds the position in the inode block. Add one to since first is at position 1
  uint32_t inode_number = 1 + (offset / BLOCK_SIZE);
  uint32_t inode_position = inode_number * FOUR_BYTE;
  // holds which byte we are starting at in the data block
  uint32_t byte_position = offset % BLOCK_SIZE;

  // datablock_num tells us which data block we are on
  uint32_t datablock_num = (*(inode_pointer2 + inode_position)) +(*(inode_pointer2+ inode_position+ONE_MEM_LOCATION) << SHIFT_ONE_BYTE) +(*(inode_pointer2+ inode_position+TWO_MEM_LOCATION) << SHIFT_TWO_BYTE) + (*(inode_pointer2+ inode_position+THREE_MEM_LOCATION) << SHIFT_THREE_BYTE);

  // points to the datablock we are reading from right now. We add one since inodes and data block are 0 indexed
  uint8_t * datablock_ptr = boot_block_ptr + (num_inodes2+1 + datablock_num) * BLOCK_SIZE;

  while(i < length){
    // put the char into the buffer
    buf[i] = datablock_ptr[byte_position];
    i++;
    byte_position++;
    // if we reach the end of the datablock, go to the next one
    if(byte_position >= BLOCK_SIZE){
      inode_position = inode_position + FOUR_BYTE;
      inode_number++;
      datablock_num = (*(inode_pointer2 + inode_position)) +(*(inode_pointer2+ inode_position+ONE_MEM_LOCATION) << SHIFT_ONE_BYTE) +(*(inode_pointer2+ inode_position+TWO_MEM_LOCATION) << SHIFT_TWO_BYTE) + (*(inode_pointer2+ inode_position+THREE_MEM_LOCATION) << SHIFT_THREE_BYTE);
      datablock_ptr = boot_block_ptr + (num_inodes2+1 + datablock_num) * BLOCK_SIZE;
      byte_position = 0;
    }

    // see if we reached the end of the file
    if(inode_number >= num_total_datablocks){
      if(byte_position >= num_total_offset){
        break;
      }
    }
  }

  // return the number of bytes read
  return i;

}

/*
* file_read(int32_t fd, void* buf, int32_t nbytes)
*   DESCRIPTION: reads a file and puts char into buf
*   INPUTS: fd - the index in regards to the directory
*           buf - the buffer that we are storing the name into
*           nbytes - how many bytes we want to read
*   OUTPUTS: none
*   RETURN VALUE: 0 on success, -1 on failure
*   SIDE EFFECTS: puts chars into buf from file
*/
int32_t file_read (int32_t fd, void* buf, int32_t nbytes){
  //use fd to access the pcb block

  // set pcb_ptr to point to beginning of the pcb
  pcb* pcb_ptr = (pcb*)(tss.esp0 & PCPMASK);

  // grab the inode and file_pos
  uint32_t inode = pcb_ptr->file_descriptor_t[fd].inode;
  uint32_t file_pos = pcb_ptr->file_descriptor_t[fd].file_position;

  // set up the pointer to the inode block and get the file size
  uint8_t * inode_pointer2 = boot_block_ptr + (inode+1) * BLOCK_SIZE;
  uint32_t file_size = (*(inode_pointer2)) +(*(inode_pointer2+ONE_MEM_LOCATION) << SHIFT_ONE_BYTE) +(*(inode_pointer2+TWO_MEM_LOCATION) << SHIFT_TWO_BYTE) + (*(inode_pointer2+THREE_MEM_LOCATION) << SHIFT_THREE_BYTE);

  if(file_pos >= file_size){
    return 0;
  }

  uint8_t * buffer = (uint8_t*)buf;

  int32_t read = read_data(inode, file_pos, buffer, nbytes);
  // move the file position
  pcb_ptr->file_descriptor_t[fd].file_position += read;

  return read;

}
