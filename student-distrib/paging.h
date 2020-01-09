#ifndef PAGING_H
#define PAGING_H

// ONEKB is also 1 followed by 10 zeros in hex
#define ONEKB                   1024
#define TWOKB                   2048
#define VIDEO_MEM               (753664/4096) //184
#define VIDEO_MEM_1             185
#define VIDEO_MEM_2             186
#define VIDEO_MEM_3             187
#define GET_TWENTY              12
#define PROGRAM_IMAGE_OFFSET    72
#define EITMB                   0x800000
#define FOMB                    0x400000
#define PROCESS_ENTRY           32
#define VID_ENTRY               33

//function to initialize page directory
extern void page_dir_init(void);
extern void map_128(int process_flag);

#endif
