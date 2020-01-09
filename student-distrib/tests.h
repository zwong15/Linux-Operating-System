#ifndef TESTS_H
#define TESTS_H

#include "types.h"


// test launcher
void launch_tests();

//function to test buffer for keyboard
void write_test();
//function to test read for keyboard
extern int read_test();
//test to check if divide error handler works correctly
int divide_test();
//fucntion that prints all files in directory
void print_all_dir();
//function that prints contents of cat file
void open_cat();
//function that prints contents of counter file
void open_counter();
//function that prints contents of fish file
void open_fish();
//function that prints contents of frame0 file
void open_frame0();
//function that prints contents of frame1 file
void open_frame1();
//function that prints contents of grep file
void open_grep();
//function that prints contents of hello file
void open_hello();
//function that prints contents of ls file
void open_ls();
//function that prints contents of pingpong file
void open_pingpong();
//function that prints contents of shell file
void open_shell();
//function that prints contents of sigtest file
void open_sigtest();
//function that prints contents of syserr file
void open_syserr();
//function that prints contents of testprint file
void open_testprint();
//function that prints contents of verylarge file
void open_verylarge();
//function that prints contents of multiple opened files
void open_mult();
//function that prints file in directory by index
void print_dir_index(uint32_t index);
//function that prints contents of invalid file
void open_invalid_file();
//function that prints contents of file thats too big
void open_too_big_file();
//function that prints contents of rtc file
void file_open_rtc();
//function that tests rtc open
void rtc_open_test();
//function that test rtc write
void rtc_write_test();
//function that test rtc write and read
void rtc_read_write_test();
//function to test closing a file and then trying to read it
void close_file_then_read();
//function to test closing a directory and then trying to read it
void close_directory_then_open();
// function to call file read multiple different times with a small count
void multiple_calls_to_file_read();
// function to call directory read multiple different times with a small count
void multiple_calls_to_directory_read();
#endif /* TESTS_H */
