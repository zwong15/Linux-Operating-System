
/* keyboard.c - Functions to interact with the keyboard */

#include "keyboard.h"
#include "lib.h"
#include "i8259.h"
#include "system_calls.h"
#include "tests.h"
#include "terminal.h"
#include "pit.h"

//initialize variables and buffer
static unsigned int caps = 0;
static unsigned int shift = 0;
static unsigned int ctrl = 0;
static unsigned int alt = 0;
extern uint32_t write_len;
extern int screen_x;
extern int screen_y;
extern uint8_t sched_count;
unsigned int counter = 0;
extern uint32_t counter_del;
unsigned int enter = 0;
extern int process_flag;
extern uint32_t ready[NUM_PROCS];
extern char buff2[SIZE];
int8_t key_buff[BUFFSIZE] = "";
extern uint32_t flag_enter;
uint32_t flag_enter_for_pit = 0;
 /*
 * key_init(void)
 *   DESCRIPTION: Initializes the keyboard.
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: Turns on the keyboard by enabling
 *   the keyboard's irq entry on the pic
 */
void key_init(void){
  //enable the keyboard on the pic
  enable_irq(KEY_PIC);
  ready[PROC_ONE] = 0;
  ready[PROC_TWO] = 0;
}

/*
 * scan_codes(unsigned char scan_code)
 *   DESCRIPTION: Takes the scan codes from the keyboard and
     returns the corresponding ascii character.
 *   INPUTS: scan_code -- the scan_code received from keyboard
 *   OUTPUTS: none
 *   RETURN VALUE: an ascii character corresponding to the
 *   key code.
 *   SIDE EFFECTS: none
 */
unsigned char scan_codes(unsigned char scan_code){
	//checks the input scan code and returns the correct ascii character
	switch(scan_code){
		case(ONE):
			return('1');
			break;
		case(TWO):
			return('2');
			break;
		case(THREE):
			return('3');
			break;
		case(FOUR):
			return('4');
			break;
		case(FIVE):
			return('5');
			break;
		case(SIX):
			return('6');
			break;
		case(SEVEN):
			return('7');
			break;
		case(EIGHT):
			return('8');
			break;
		case(NINE):
			return('9');
			break;
		case(ZERO):
			return('0');
			break;
		case(Q):
			return('q');
			break;
		case(W):
			return('w');
			break;
		case(E):
			return('e');
			break;
		case(R):
			return('r');
			break;
		case(T):
			return('t');
			break;
		case(Y):
			return('y');
			break;
		case(U):
			return('u');
			break;
		case(I):
			return('i');
			break;
		case(O):
			return('o');
			break;
		case(P):
			return('p');
			break;
		case(A):
			return('a');
			break;
		case(S):
			return('s');
			break;
		case(D):
			return('d');
			break;
		case(F):
			return('f');
			break;
		case(G):
			return('g');
			break;
		case(H):
			return('h');
			break;
		case(J):
			return('j');
			break;
		case(K):
			return('k');
			break;
		case(L):
			return('l');
			break;
		case(Z):
			return('z');
			break;
		case(X):
			return('x');
			break;
		case(C):
			return('c');
			break;
		case(V):
			return('v');
			break;
		case(B):
			return('b');
			break;
		case(N):
			return('n');
			break;
		case(M):
			return('m');
			break;
		case(SPACE):
			return(' ');
			break;
		case(BKSPACE):
			return(' ');
			break;
		case(MINUS):
			return('-');
			break;
		case(PLUS):
			return('=');
			break;
		case(ENTER):
			return('\n');
			break;
		case(CTRL):
			return(' ');
			break;
		case(SLASH):
			return('/');
			break;
		case(BKSLASH):
			return('\\');
			break;
		case(PERIOD):
			return('.');
			break;
		case(COMMA):
			return(',');
			break;
		case(QUOTES):
			return('\'');
			break;
		case(COLON):
			return(';');
			break;
		case(LBRACE):
			return('[');
			break;
		case(RBRACE):
			return(']');
			break;
		case(TILDE):
			return('`');
			break;
	}
  return NULL;
}

unsigned char scan_codes_caps(unsigned char scan_code){
	//checks the input scan code and returns the correct ascii character
	switch(scan_code){
		case(ONE):
			return('!');
			break;
		case(TWO):
			return('@');
			break;
		case(THREE):
			return('#');
			break;
		case(FOUR):
			return('$');
			break;
		case(FIVE):
			return('%');
			break;
		case(SIX):
			return('^');
			break;
		case(SEVEN):
			return('&');
			break;
		case(EIGHT):
			return('*');
			break;
		case(NINE):
			return('(');
			break;
		case(ZERO):
			return(')');
			break;
		case(Q):
			return('Q');
			break;
		case(W):
			return('W');
			break;
		case(E):
			return('E');
			break;
		case(R):
			return('R');
			break;
		case(T):
			return('T');
			break;
		case(Y):
			return('Y');
			break;
		case(U):
			return('U');
			break;
		case(I):
			return('I');
			break;
		case(O):
			return('O');
			break;
		case(P):
			return('P');
			break;
		case(A):
			return('A');
			break;
		case(S):
			return('S');
			break;
		case(D):
			return('D');
			break;
		case(F):
			return('F');
			break;
		case(G):
			return('G');
			break;
		case(H):
			return('H');
			break;
		case(J):
			return('J');
			break;
		case(K):
			return('K');
			break;
		case(L):
			return('L');
			break;
		case(Z):
			return('Z');
			break;
		case(X):
			return('X');
			break;
		case(C):
			return('C');
			break;
		case(V):
			return('V');
			break;
		case(B):
			return('B');
			break;
		case(N):
			return('N');
			break;
		case(M):
			return('M');
			break;
		case(SPACE):
			return(' ');
			break;
		case(BKSPACE):
			return(' ');
			break;
		case(MINUS):
			return('_');
			break;
		case(PLUS):
			return('+');
			break;
		case(ENTER):
			return('\n');
			break;
		case(CTRL):
			return(' ');
			break;
		case(SLASH):
			return('?');
			break;
		case(BKSLASH):
			return('|');
			break;
		case(PERIOD):
			return('>');
			break;
		case(COMMA):
			return('<');
			break;
		case(QUOTES):
			return('"');
			break;
		case(COLON):
			return(':');
			break;
		case(LBRACE):
			return('{');
			break;
		case(RBRACE):
			return('}');
			break;
		case(TILDE):
			return('~');
			break;
	}
  return NULL;
}

/*
 * key_handler(void)
 *   DESCRIPTION: Checks for a keyboard input and
 *   outputs it to the screen if there is one.
 *   INPUTS: None
 *   OUTPUTS: An ascii character to the screen
 *   RETURN VALUE: None
 *   SIDE EFFECTS: puts the keyboard character to the
 *   screen.
 */
void key_handler(void){
    //clears interrupt flag
    cli();
    //declare variables
    unsigned char filled;
    unsigned char scan_code;
    unsigned char ascii_char;
    //check for keyboard input
    filled = inb(STATUS_PORT);
	if(filled != 0){
        //get scan code from keyboard data port
		scan_code = inb(DATA_PORT);
		//handles the case of shift being pressed
		if(scan_code == LSHIFT|| scan_code == RSHIFT)
			shift = 1;
		//checks if shift has been released
		if(scan_code == LSHIFT+RELEASE || scan_code == (RSHIFT+RELEASE))
			shift = 0;
		//handles the case of ctrl being pressed
		if(scan_code == CTRL)
			ctrl = 1;
		//checks if ctrl has been released
		if(scan_code == CTRL+RELEASE)
			ctrl = 0;
    if(scan_code == ALT)
  		alt = 1;
  		//checks if ctrl has been released
  	if(scan_code == ALT+RELEASE)
  		alt = 0;
		//handles the case of enter being pressed
		if(scan_code == ENTER)
			enter = 1;
    if(scan_code == ENTER+RELEASE)
  			enter = 0;
		//checks if caps is on
		if(scan_code == CAPS){
			if(caps == 0)
				caps = 1;
			else
				caps = 0;
		}
		//only print necessary characters and valid keys
		if((scan_code <= SLASH || scan_code == SPACE) && scan_code >= ONE && scan_code != TAB && scan_code != LSHIFT && scan_code != BKSPACE && scan_code != CTRL){
			//check if caps or shift is on
			if((caps == 0 && shift == 0) || (caps == 1 && shift == 1))
				ascii_char = scan_codes(scan_code);
			else
				ascii_char = scan_codes_caps(scan_code);

			//handles shift for keys that have different values that caps doesnt change
			if(scan_code <= PLUS || scan_code == LBRACE || scan_code == RBRACE || scan_code == SLASH || scan_code == BKSLASH || scan_code == COLON || scan_code == QUOTES || scan_code == COMMA || scan_code == PERIOD || scan_code == TILDE){
				if(shift == 0)
					ascii_char = scan_codes(scan_code);
				else
					ascii_char = scan_codes_caps(scan_code);
			}
			//print the ascii character to the screen and prevent overflow
			if(counter < MAX || scan_code == ENTER){
        if(scan_code == ENTER && flag_enter == 1){
          key_buff[counter] = '\0';
        }
        else{
        key_buff[counter] = ascii_char;
        printf("%c", ascii_char);
        }
			}
			//increment counter based on how many chars are typed
			if(scan_code != ENTER && counter < MAX)
				counter++;
		}
		//clear the screen with ctrl+L and decrement counter
		if(scan_code == L && ctrl == 1){
			clear();
      //ready[process_flag] = 1;
      backspace(counter-1);
      counter--;
		}
    if(scan_code == F1 && alt == 1){
      if(terminal_2.present){
        memcpy((uint8_t*)(VID_MEM_OFFSET + EIGHTKB), (uint8_t*)VID_MEM_OFFSET, FOURKB);
        memcpy(terminal_2.curr_key_buff, key_buff, BUFFSIZE);
        terminal_2.curr_screen_x = screen_x;
        terminal_2.curr_screen_y = screen_y;
        terminal_2.write_len_term = write_len;
        terminal_2.counter_del_term = counter_del;
        terminal_2.present = 0;
      }
      if(terminal_3.present){
        memcpy((uint8_t*)(VID_MEM_OFFSET + TWELVEKB), (uint8_t*)VID_MEM_OFFSET, FOURKB);
        memcpy(terminal_3.curr_key_buff, key_buff, BUFFSIZE);
        terminal_3.curr_screen_x = screen_x;
        terminal_3.curr_screen_y = screen_y;
        terminal_3.write_len_term = write_len;
        terminal_3.counter_del_term = counter_del;
        terminal_3.present = 0;
      }
      if(!terminal_1.present){
        uint8_t* screen_start;
        vidmap(&screen_start);
        memcpy((uint8_t*)VID_MEM_OFFSET, (uint8_t*)(VID_MEM_OFFSET + FOURKB), FOURKB);
        memcpy(key_buff, terminal_1.curr_key_buff, BUFFSIZE);
        screen_x = terminal_1.curr_screen_x;
        screen_y = terminal_1.curr_screen_y;
        counter_del = terminal_3.counter_del_term;
        write_len = terminal_3.write_len_term;
        terminal_1.present = 1;
      }
    }
    if(scan_code == F2 && alt == 1){
      if(terminal_1.present){
        memcpy((uint8_t*)(VID_MEM_OFFSET + FOURKB), (uint8_t*)VID_MEM_OFFSET, FOURKB);
        memcpy(terminal_1.curr_key_buff, key_buff, BUFFSIZE);
        terminal_1.curr_screen_x = screen_x;
        terminal_1.curr_screen_y = screen_y;
        terminal_1.write_len_term = write_len;
        terminal_1.counter_del_term = counter_del;
        terminal_1.present = 0;
      }
      if(terminal_3.present){
        memcpy((uint8_t*)(VID_MEM_OFFSET + TWELVEKB), (uint8_t*)VID_MEM_OFFSET, FOURKB);
        memcpy(terminal_3.curr_key_buff, key_buff, BUFFSIZE);
        terminal_3.curr_screen_x = screen_x;
        terminal_3.curr_screen_y = screen_y;
        terminal_3.write_len_term = write_len;
        terminal_3.counter_del_term = counter_del;
        terminal_3.present = 0;
      }
      if(!terminal_2.present){
        uint8_t* screen_start;
        vidmap(&screen_start);
        memcpy(key_buff, terminal_2.curr_key_buff, BUFFSIZE);
        screen_x = terminal_2.curr_screen_x;
        screen_y = terminal_2.curr_screen_y;

        memcpy((uint8_t*)VID_MEM_OFFSET, (uint8_t*)(VID_MEM_OFFSET + EIGHTKB), FOURKB);
        counter_del = terminal_3.counter_del_term;
        write_len = terminal_3.write_len_term;
        terminal_2.present = 1;
      }
    }
    if(scan_code == F3 && alt == 1){
      if(terminal_1.present){
        memcpy((uint8_t*)(VID_MEM_OFFSET + FOURKB), (uint8_t*)VID_MEM_OFFSET, FOURKB);
        memcpy(terminal_1.curr_key_buff, key_buff, BUFFSIZE);
        terminal_1.curr_screen_x = screen_x;
        terminal_1.curr_screen_y = screen_y;
        terminal_1.write_len_term = write_len;
        terminal_1.counter_del_term = counter_del;
        terminal_1.present = 0;
      }
      if(terminal_2.present){
        memcpy((uint8_t*)(VID_MEM_OFFSET + EIGHTKB), (uint8_t*)VID_MEM_OFFSET, FOURKB);
        memcpy(terminal_2.curr_key_buff, key_buff, BUFFSIZE);
        terminal_2.curr_screen_x = screen_x;
        terminal_2.curr_screen_y = screen_y;
        terminal_2.write_len_term = write_len;
        terminal_2.counter_del_term = counter_del;
        terminal_2.present = 0;
      }
      if(!terminal_3.present){
        terminal_3.present = 1;
        memcpy( (uint8_t*)VID_MEM_OFFSET, (uint8_t*)(VID_MEM_OFFSET + TWELVEKB), FOURKB);
        memcpy(key_buff, terminal_3.curr_key_buff, BUFFSIZE);
        screen_x = terminal_3.curr_screen_x;
        screen_y = terminal_3.curr_screen_y;
        counter_del = terminal_3.counter_del_term;
        write_len = terminal_3.write_len_term;
      }
    }
		//make backspace delete the previous char and update counter
		if(scan_code == BKSPACE){
			counter = backspace(counter);
		}
		//read the previous line and put it on buffer
		if(scan_code == ENTER){
      if(flag_enter == 1){
      }
      else{
        //allow us to delete stuff while fish is running
          //flag_enter_for_pit = 1;
          //if(sched_count == 1){
            ready[process_flag] = 1;
            write_len = 0;
            counter_del = 0;
            //set counter to 0
    			  counter = 0;
          //}
      }
		}
		//update cursor
		move();
	}
    //send end of interrupt
    send_eoi(KEY_PIC);
    //set the interrupt flag
    sti();
}
