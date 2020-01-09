#include "x86_desc.h"
#include "lib.h"
#include "paging.h"

extern int process_flag;

/*
 * map_128(int process_flag)
 *   DESCRIPTION: sets up the right page for our process
 *   INPUTS: process_flag - tells us how many processes we have
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: Flushes the TLB
 *
 */
void map_128(int process_flag){
	// 2 comes from either wanting it to point to the 2nd 4MB page or 3rd 4MB page
	page_dir[PROCESS_ENTRY].pointer = (TWOKB) + (process_flag * ONEKB);
	//flush the TLB
	asm(
     "movl %cr3, %eax;"
     "movl %eax, %cr3;"
 );
}



/*
 * page_dir_init(void)
 *   DESCRIPTION: Initializes the page directory.
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: Initializes the page directory
 *   and sets up page entries for the video memory
 *   and kernel
 */
void page_dir_init(void){

  // i and j are used to walk through for loop
  int i = 0;
  int j = 0;

  //set the first 1024 entries in the directory
  for(j = 0; j < ONEKB; j++){
    page_dir[j].pointer = 0;
    page_dir[j].avail1 = 0;
    page_dir[j].avail2 = 0;
    page_dir[j].avail3 = 0;
    page_dir[j].global = 0;
    page_dir[j].size = 1;
    page_dir[j].dirty = 0;
    page_dir[j].PCD = 1;
    page_dir[j].PWT = 0;
    page_dir[j].U_S = 1;
    page_dir[j].R_W = 1;
    page_dir[j].present = 0;
  }

  //set the first 1024 entries in the table
  for(i = 0; i < ONEKB; i++){
    page_table[i].offset = i;
    page_table[i].avail1 = 0;
    page_table[i].avail2 = 0;
    page_table[i].avail3 = 0;
    page_table[i].global = 0;
    page_table[i].PAT = 0;
    page_table[i].dirty = 0;
    page_table[i].PCD = 1;
    page_table[i].PWT = 0;
    page_table[i].U_S = 1;
    page_table[i].R_W = 1;
    page_table[i].present = 0;

    //set the bits to set the video memory entry
    if(i == VIDEO_MEM){
      page_table[i].offset = i;
      page_table[i].avail1 = 0;
      page_table[i].avail2 = 0;
      page_table[i].avail3 = 0;
      page_table[i].global = 0;
      page_table[i].PAT = 0;
      page_table[i].dirty = 0;
      page_table[i].PCD = 0;
      page_table[i].PWT = 0;
      page_table[i].U_S = 1;
      page_table[i].R_W = 1;
      page_table[i].present = 1;
    }
		if(i == VIDEO_MEM_1){
      page_table[i].offset = i;
      page_table[i].avail1 = 0;
      page_table[i].avail2 = 0;
      page_table[i].avail3 = 0;
      page_table[i].global = 0;
      page_table[i].PAT = 0;
      page_table[i].dirty = 0;
      page_table[i].PCD = 1;
      page_table[i].PWT = 0;
      page_table[i].U_S = 1;
      page_table[i].R_W = 1;
      page_table[i].present = 1;
    }
		if(i == VIDEO_MEM_2){
      page_table[i].offset = i;
      page_table[i].avail1 = 0;
      page_table[i].avail2 = 0;
      page_table[i].avail3 = 0;
      page_table[i].global = 0;
      page_table[i].PAT = 0;
      page_table[i].dirty = 0;
      page_table[i].PCD = 1;
      page_table[i].PWT = 0;
      page_table[i].U_S = 1;
      page_table[i].R_W = 1;
      page_table[i].present = 1;
    }
		if(i == VIDEO_MEM_3){
      page_table[i].offset = i;
      page_table[i].avail1 = 0;
      page_table[i].avail2 = 0;
      page_table[i].avail3 = 0;
      page_table[i].global = 0;
      page_table[i].PAT = 0;
      page_table[i].dirty = 0;
      page_table[i].PCD = 1;
      page_table[i].PWT = 0;
      page_table[i].U_S = 1;
      page_table[i].R_W = 1;
      page_table[i].present = 1;
    }
  }

  //set up first page directory entry
  page_dir[0].pointer = (((unsigned long) page_table)>>GET_TWENTY);
  page_dir[0].avail1 = 0;
  page_dir[0].avail2 = 0;
  page_dir[0].avail3 = 0;
  page_dir[0].global = 0;
  page_dir[0].size = 0;
  page_dir[0].dirty = 0;
  page_dir[0].PCD = 0;
  page_dir[0].PWT = 0;
  page_dir[0].U_S = 1;
  page_dir[0].R_W = 1;
  page_dir[0].present = 1;

  // set the correct information for kernal being loaded
  page_dir[1].pointer = ONEKB;
  page_dir[1].avail1 = 0;
  page_dir[1].avail2 = 0;
  page_dir[1].avail3 = 0;
  page_dir[1].global = 1;
  page_dir[1].size = 1;
  page_dir[1].dirty = 0;
  page_dir[1].PCD = 1;
  page_dir[1].PWT = 0;
  page_dir[1].U_S = 0;
  page_dir[1].R_W = 1;
  page_dir[1].present = 1;

 // create the page for the processes to be loaded into
  page_dir[PROCESS_ENTRY].pointer = TWOKB;
  page_dir[PROCESS_ENTRY].avail1 = 0;
  page_dir[PROCESS_ENTRY].avail2 = 0;
  page_dir[PROCESS_ENTRY].avail3 = 0;
  page_dir[PROCESS_ENTRY].global = 0;
  page_dir[PROCESS_ENTRY].size = 1;
  page_dir[PROCESS_ENTRY].dirty = 0;
  page_dir[PROCESS_ENTRY].PCD = 1;
  page_dir[PROCESS_ENTRY].PWT = 0;
  page_dir[PROCESS_ENTRY].U_S = 1;
  page_dir[PROCESS_ENTRY].R_W = 1;
  page_dir[PROCESS_ENTRY].present = 1;

	// set up the page directory entry for video mapping
	page_dir[VID_ENTRY].pointer = (((unsigned long) page_table)>>GET_TWENTY);
  page_dir[VID_ENTRY].avail1 = 0;
  page_dir[VID_ENTRY].avail2 = 0;
  page_dir[VID_ENTRY].avail3 = 0;
  page_dir[VID_ENTRY].global = 0;
  page_dir[VID_ENTRY].size = 0;
  page_dir[VID_ENTRY].dirty = 0;
  page_dir[VID_ENTRY].PCD = 0;
  page_dir[VID_ENTRY].PWT = 0;
  page_dir[VID_ENTRY].U_S = 1;
  page_dir[VID_ENTRY].R_W = 1;
  page_dir[VID_ENTRY].present = 1;

/*
 *   DESCRIPTION: Enables paging
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: Enables paging by setting
 *   the cr0, cr3, cr4 registers
 */
 asm(
    "movl $page_dir, %eax;"
    "movl %eax, %cr3;"
    "movl %cr4, %eax;"
    "orl $0x00000010, %eax;"
    "movl %eax, %cr4;"
    "movl %cr0, %eax;"
    "orl $0x80000000, %eax;"
    "movl %eax, %cr0;"
);

}
