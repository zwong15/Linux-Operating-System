#include "tests.h"
#include "x86_desc.h"
#include "lib.h"
#include "keyboard.h"
#include "i8259.h"
#include "filesystem.h"
#include "rtc.h"
#define PASS 1
#define FAIL 0
#define SIZEBUFF 256
#define HALF     128

// extern char buff2[HALF];
 /* format these macros as you see fit */

// 	printf("[TEST %s] Running %s at %s:%d\n", __FUNCTION__, __FUNCTION__, __FILE__, __LINE__)

// 	printf("[TEST %s] Result = %s\n", name, (result) ? "PASS" : "FAIL");
//
// static inline void assertion_failure(){
 	/* Use exception #15 for assertions, otherwise
 	   reserved by Intel */
// 	asm volatile("int $15");
// }
//
//
// /* Checkpoint 1 tests */
//
// /* IDT Test - Example
//  *
//  * Asserts that first 10 IDT entries are not NULL
//  * Inputs: None
//  * Outputs: PASS/FAIL
//  * Side Effects: None
//  * Coverage: Load IDT, IDT definition
//  * Files: x86_desc.h/S
//  */
// int idt_test(){
// 	TEST_HEADER;
//
// 	int i;
// 	int result = PASS;
// 	for (i = 0; i < 10; ++i){
// 		if ((idt[i].offset_15_00 == NULL) &&
// 			(idt[i].offset_31_16 == NULL)){
// 			assertion_failure();
// 			result = FAIL;
// 		}
// 	}
//
// 	return result;
// }
//
// // add more tests here
//
// /* divide_test()
//  * Divides by zero to check exception handler
//  * Inputs: None
//  * Outputs: divide by zero
//  * Side Effects: divide error exception handler is invoked
//  * Coverage: Load IDT, Divide error definition
//  */
// int divide_test(){
// 	int i = 0;
// 	i = i/i;
// 	return i;
// }
//
//
// /* Checkpoint 2 tests */
// /* print_dir_index(uint32_t index)
//  * prints the name of the file in directory by index
//  * Inputs: index- the index for the directory file
//  * Outputs: none
//  * Side Effects: displays name of the file by index onto terminal
//  */
// void print_dir_index(uint32_t index){
// 	//load varibales and buffer
// 	int32_t fd, cnt;
// 	uint8_t buf[10000];
// 	//clear the screen
// 	clear();
//     //open the directory
// 	fd = directory_open ((uint8_t*)".");
// 	//checks to see that file is recognized
// 	if(fd == -1){
// 		printf("file not recognized\n\n");
// 	}
//     //calls directory_read_by_index to display the name onto terminal
// 	cnt = directory_read_by_index(index,17, buf);
// }
//
// /* print_all_dir()
//  * prints the names of all files in directory
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays name of the files onto terminal
//  */
// void print_all_dir(){
//     //loads variables and buffer
//     int32_t fd, cnt;
//     uint8_t buf[10000];
//     //clear the screen
//     clear();
//     //open the durectory
// 	fd = directory_open ((uint8_t*)".");
// 	//checks to see that the file is recognized
//   if(fd == -1){
//     printf("file not recognized\n\n");
//   }
//     //prints out the names onto terminal
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
//   cnt = directory_read(33, buf);
// }
// /* open_cat()
//  * prints the contents of cat file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of cat into terminal
//  */
// void open_cat(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//   fd = file_open((uint8_t*)"cat");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  ////file_read(50000, buf);
// }
// /* open_counter()
//  * prints the contents of counter file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of counter into terminal
//  */
// void open_counter(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//     fd = file_open((uint8_t*)"counter");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  ////file_read(50000, buf);
// }
// /* open_fish()
//  * prints the contents of fish file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of fish into terminal
//  */
// void open_fish(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//     fd = file_open((uint8_t*)"fish");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	 ////file_read(50000, buf);
// }
// /* open_frame0()
//  * prints the contents of frame0 file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of frame0 into terminal
//  */
// void open_frame0(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//     fd = file_open((uint8_t*)"frame0.txt");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
// /* open_frame1()
//  * prints the contents of frame1 file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of frame1 into terminal
//  */
// void open_frame1(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//     fd = file_open((uint8_t*)"frame1.txt");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
// /* open_grep()
//  * prints the contents of grep file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of grep into terminal
//  */
// void open_grep(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
//   fd = file_open((uint8_t*)"grep");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
// /* open_hello()
//  * prints the contents of hello file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of hello into terminal
//  */
// void open_hello(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//   fd = file_open((uint8_t*)"hello");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
// /* open_ls()
//  * prints the contents of ls file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of ls into terminal
//  */
// void open_ls(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
//   fd = file_open((uint8_t*)"ls");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
// /* open_pingpong()
//  * prints the contents of pingpong file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of pingpong into terminal
//  */
// void open_pingpong(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
//   fd = file_open((uint8_t*)"pingpong");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
// /* open_shell()
//  * prints the contents of shell file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of shell into terminal
//  */
// void open_shell(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
//   fd = file_open((uint8_t*)"shell");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
// /* open_sigtest()
//  * prints the contents of sigtest file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of sigtest into terminal
//  */
// void open_sigtest(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
//   fd = file_open((uint8_t*)"sigtest");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
// /* open_syserr()
//  * prints the contents of syserr file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of syserr into terminal
//  */
// void open_syserr(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
//   fd = file_open((uint8_t*)"syserr");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
// /* open_testprint()
//  * prints the contents of testprint file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of testprint into terminal
//  */
// void open_testprint(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
//   fd = file_open((uint8_t*)"testprint");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
// /* open_verylarge()
//  * prints the contents of verylarge file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of verylarge into terminal
//  */
// void open_verylarge(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
//   fd = file_open((uint8_t*)"verylargetextwithverylongname.tx");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }/* open_mult()
//  * prints the contents of multiple files into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of multiple files into terminal
//  */
// void open_mult(){
//     //loads variables and buffer
// 	int32_t fd, cd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
// 	fd = file_open((uint8_t*)"frame0.txt");
// 	//checks if first file is valid
// 	if(fd == -1){
// 		printf("file not recognized\n");
// 	}
// 	cd = file_open((uint8_t*)"frame1.txt");
// 	//checks if second file is valid
// 	if(cd == -1){
// 		printf("file not recognized\n");
// 	}
//     //prints the contents of the file onto terminal
// 	//file_read(50000, buf);
// }
// /* file_open_rtc()
//  * prints the contents of rtc file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of rtc into terminal
//  */
// void file_open_rtc(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
// 	fd = file_open((uint8_t*)"rtc");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
//
// /* open_invalid_file()
//  * prints the contents of an invalid file into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of an invalid file into terminal
//  */
// void open_invalid_file(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
// 	fd = file_open((uint8_t*)"kevin");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
// /* open_too_big_file()
//  * prints the contents of a file that is too big into terminal
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: displays contents of a file that is too big into terminal
//  */
// void open_too_big_file(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
// 	fd = file_open((uint8_t*)"verylargetextwithverylongname.txt");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
//   //prints the contents of the file onto terminal
// 	  //file_read(50000, buf);
// }
//
// /* close_file_then_open()
//  * open a file and then close it and then try to read from it
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: should not open the file
//  */
// void close_file_then_read(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
// 	fd = file_open((uint8_t*)"frame0.txt");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
// 	//close the file
// 	fd = file_close();
//
//   //try to read the file that we just closed
// 	  //file_read(50000, buf);
// }
//
// /* close_directory_then_open()
//  * open a directory and then close it and then try to read from it
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: should not open the file
//  */
// void close_directory_then_open(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
// 	fd = directory_open((uint8_t*)".");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("directory not recognized\n");
//   }
// 	//close the file
// 	fd = directory_close();
//
//   //try to read the file that we just closed
// 	  directory_read(50000, buf);
// }
//
// /* multiple_calls_to_//file_read()
//  * call file read multiple different times with a small count
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: print segments of the file
//  */
// void multiple_calls_to_//file_read(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
// 	fd = file_open((uint8_t*)"frame0.txt");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
// 	printf("reading 20 bytes:\n");
// 	 	fd = //file_read(20, buf);
// 		printf("file_read returned: %u", fd);
// 	printf("\nreading 20 bytes:\n");
// 	  fd = //file_read(20, buf);
// 		printf("file_read returned: %u", fd);
//
// 	printf("\nreading 20 bytes:\n");
// 	  fd = //file_read(20, buf);
// 		printf("file_read returned: %u", fd);
//
// 	printf("\nreading 20 bytes:\n");
// 		fd = //file_read(20, buf);
// 		printf("file_read returned: %u", fd);
//
// }
//
// /* multiple_calls_to_directory_read()
//  * call directory read multiple different times with a small count
//  * Inputs: none
//  * Outputs: none
//  * Side Effects: print segments of the filename
//  */
// void multiple_calls_to_directory_read(){
//     //loads variables and buffer
// 	int32_t fd;
//   uint8_t buf[50000];
//   //clears the screen
//   clear();
//     //opens the corresponing file
//
// 	fd = directory_open((uint8_t*)".");
//   //checks to see that file is valid
//   if(fd == -1){
//     printf("file not recognized\n");
//   }
// 	printf("reading 4 bytes:\n");
// 	 	fd = directory_read(4, buf);
// 		printf("\ndirectory_read returned: %u\n", fd);
//
// 	printf("reading 4 bytes:\n");
// 	 	fd = directory_read(4, buf);
// 		printf("\ndirectory_read returned: %u\n", fd);
//
// 	printf("reading 4 bytes:\n");
// 		fd = directory_read(4, buf);
// 		printf("\ndirectory_read returned: %u\n", fd);
//
// 	printf("reading 4 bytes:\n");
// 		fd = directory_read(4, buf);
// 		printf("\ndirectory_read returned: %u\n", fd);
//
// 	printf("reading 4 bytes:\n");
// 		fd = directory_read(4, buf);
// 		printf("\ndirectory_read returned: %u\n", fd);
//
// 	printf("reading 4 bytes:\n");
// 		fd = directory_read(4, buf);
// 		printf("\ndirectory_read returned: %u\n", fd);
//
// }
//
//
//
//
// /*rtc_open_test()
//  *DESCRIPTION: Uses rtc_open function to set RTC to
//  *             2 Hz
//  *INPUTS: none
//  *OUTPUTS: none
//  *SIDE EFFECTS: changes RTC interrupt frequency
//  */
// void rtc_open_test(){
// 	/*Initialize variable as arguement for function*/
// 	uint8_t* filename;
//
// 	/*test rtc_open*/
// 	rtc_open(filename);
// }
//
// /*rtc_write_test()
//  *DESCRIPTION: Uses rtc_write function to change the
//  *             RTC interrupt frequency
//  *INPUTS: none
//  *OUTPUTS: none
//  *SIDE EFFECTS: changes RTC interrupt frequency
//  */
// void rtc_write_test(){
//
// 	/*Initialize arguement variables for function*/
// 	int32_t fd;
//
// 	/*Set frequency rate to desired amount*/
// 	int32_t buf = 16;
//
// 	/*test rtc_write function*/
// 	rtc_write(fd, buf, 4);
// }
//
// /*rtc_read_write_test()
//  *DESCRITPTION: tests both rtc_read and rtc_write by printing
//  *              out values to screen. It increases as rate goes
//  *              higher.
//  *INPUTS: none
//  *OUTPUTS: none
//  *SIDE EFFECTS: changes RTC frequency and prints out to screen
//  */
// void rtc_read_write_test(){
//
// 	/*Initialize arguement variables*/
// 	int32_t fd;
// 	void* ptr;
//
// 	/*initialize rtc freuqnecy*/
// 	int32_t buf = 2;
// 	int i = 10;
//
// 	/*Loop through rtc frequency until it reaches max 1024*/
// 	while(buf > 0){
// 		rtc_write(fd, buf, 4);
// 		while(i > 0){
// 			/*Print out character and tests rtc_read*/
// 			puts("a");
// 			rtc_read(fd, ptr, 4);
// 			i--;
// 		}
// 		i = 10;
// 		/*increase frequency rate*/
// 		buf++;
// 	}
// }
//
// /* buff_test();
//  * Writes a buffer of size 256 to terminal
//  * Inputs: None
//  * Outputs: Buffer of size 256
//  * Side Effects: buffer is written to screen
//  */
// void write_test(){
// 	//set buffer
// 	char buff1[SIZEBUFF] = "";
// 	//make first 128 chars 'c'
// 	int i = 0;
// 	for(i = 0; i < HALF; i++)
// 		buff1[i] = 'c';
// 	//last 128 chars 'd'
// 	for(i = HALF; i < SIZEBUFF; i++)
// 		buff1[i] = 'd';
// 	//call write
// 	terminal_write(1, buff1, SIZEBUFF);
// }
//
// /* read_test(char buff1[], int counter);
//  * reads and writes the current line
//  * Inputs: a buffer and counter
//  * Outputs: none
//  * Side Effects: line is read and written to screen
//  */
// extern int read_test(){
// 	buff2[100] = 1;
// 	return 1;
// }
//
//
// /* Checkpoint 3 tests */
// /* Checkpoint 4 tests */
// /* Checkpoint 5 tests */
//
//
// /* Test suite entry point */
void launch_tests(){
	//TEST_OUTPUT("idt_test", idt_test());
	//write_test();
	//read_test();
	// rtc_open_test();
	// rtc_write_test();
	//rtc_read_write_test();
	//open_invalid_file();
	//open_too_big_file();
	//file_open_rtc();
	//print_all_dir();
  //print_dir_index(7);
  //open_cat();
  //open_counter();
  //open_fish();
  //open_frame0();
	//open_frame1();
  //open_grep();
  //open_hello();
  //open_ls();
  //open_pingpong();
  //open_shell();
  //open_sigtest();
  //open_syserr();
  //open_testprint();
  //open_verylarge();
  //open_mult();
	//close_file_then_read();
	//close_directory_then_open();
	//multiple_calls_to_//file_read();
	//multiple_calls_to_directory_read();


}
