/* keyboard.h - Defines used in interactions with the keyboard */

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "types.h"

//set ports
#define DATA_PORT    0x60
#define STATUS_PORT  0x64
#define KEY_PIC      1
#define NUM_PROCS    2
#define PROC_ONE     0
#define PROC_TWO     1
#define FOURKB       4096
#define TWELVEKB    12288
//set the scan codes
#define ONE          0x02
#define TWO          0x03
#define THREE        0x04
#define FOUR         0x05
#define FIVE         0x06
#define SIX          0x07
#define SEVEN        0x08
#define EIGHT        0x09
#define NINE         0x0A
#define ZERO         0x0B
#define Q            0x10
#define W            0x11
#define E            0x12
#define R            0x13
#define T            0x14
#define Y            0x15
#define U            0x16
#define I            0x17
#define O            0x18
#define P            0x19
#define A            0x1E
#define S            0x1F
#define D            0x20
#define F            0x21
#define G            0x22
#define H            0x23
#define J            0x24
#define K            0x25
#define L            0x26
#define Z            0x2C
#define X            0x2D
#define C            0x2E
#define V            0x2F
#define B            0x30
#define N            0x31
#define M            0x32
#define LSHIFT       0x2A
#define RSHIFT       0x36
#define ALT          0x38
#define CAPS         0x3A
#define SPACE        0x39
#define BKSPACE      0x0E
#define MINUS        0x0C
#define PLUS         0x0D
#define ENTER        0x1C
#define CTRL         0x1D
#define UP           0x48
#define DOWN         0x50
#define LEFT         0x4B
#define RIGHT        0x4D
#define BKSLASH		   0x2B
#define SLASH	       0x35
#define PERIOD		   0x34
#define COMMA		     0x33
#define TILDE		     0x29
#define QUOTES		   0x28
#define COLON		     0x27
#define LBRACE		   0x1A
#define RBRACE		   0x1B
#define TAB          0x0F
#define RELEASE      0x80
#define MAX          127
#define SIZE         128
#define F1           0x3B
#define F2           0x3C
#define F3           0x3D

//function initialize the keyboard by enabling it's IRQ line
extern void key_init(void);
//function to write a buffer to terminal


//function to convert keyboard scan codes to ASCII characters
extern unsigned char scan_codes(unsigned char scan_code);


/*the handler for the keyboard that writes the correct ASCII to screen when
is pressed*/
extern void key_handler(void);
extern int shifter(unsigned char scan_code);
#endif
