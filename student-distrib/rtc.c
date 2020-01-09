#include "rtc.h"
#include "i8259.h"
#include "lib.h"
#include "tests.h"

/*Flag variable to indicate if interrupt is on*/
volatile int32_t rtc_interrupt_flag;



/*
 * init_rtc()
 *   DESCRIPTION: initialize the RTC
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: the IRQ line for RTC will be initialized
 */
void init_rtc(){
    //clear interrupts flag
    cli();

   //declare variables
   unsigned char curr_val;

   //disable NMI to keep RTC safe and set index to register B
   outb(DISABLE_INTERRUPTS, RTC_PORT);

   //get the original value of reg B
   curr_val = inb(READ_PORT);

   //set the index to reg B again because index D was set after reading
   outb(DISABLE_INTERRUPTS, RTC_PORT);

   //turn on bit 6 in reg B
   outb(curr_val | BIT6, READ_PORT);

   //enable the RTC IRQ line
   enable_irq(IRQ_LINE);

   //set the interrupts flag
   sti();
}

void rtc_interrupt_handler(void){

    //clear interrupts flag
    cli();

   //use to test RTC handler
   //test_interrupts();

   //choose reg C and read to make sure the interrupt happens again
   outb(REGISTER_C, RTC_PORT);
   inb(READ_PORT);

   /*Set interrupt flag low if raised*/
   if(rtc_interrupt_flag){
      rtc_interrupt_flag = 0;
   }

   //send the EOI to the RTC IRQ line
   send_eoi(IRQ_LINE);

   //reset interrupts flag
   sti();
}

/*
 * rtc_open()
 *   DESCRIPTION: initializes the RTC frequency to 2 Hz
 *   INPUTS: filename - pointer to specified filename
 *   OUTPUTS: none
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: sets RTC frequency
 */
int32_t rtc_open(const uint8_t* filename){

    /*Set frequency to 2 Hz*/
    set_frequency(2);

	return 0;
}

/*
 * rtc_close()
 *   DESCRIPTION: initializes the back to original open state
 *   INPUTS: fd - file descriptor number
 *   OUTPUTS: none
 *   RETURN VALUE: 0
 *   SIDE EFFECTS: sets RTC frequency
 */
int32_t rtc_close(int32_t fd){

    /*Return RTC to starting state of 2 Hz*/
	set_frequency(2);

	return 0;
}

/*
 * rtc_read()
 *   DESCRIPTION: blocks until the next interrupt occurs.
 *                DOES NOT READ RTC FREQUENCY!
 *   INPUTS: fd - file descriptor number
 *           buf - buffer
 *           nbytes - number of bytes
 *   OUTPUTS: none
 *   RETURN VALUE: 0
 */
int32_t rtc_read(int32_t fd, void* buf, int32_t nbytes){

    /*Set flag high*/
    rtc_interrupt_flag = 1;
    
	//Block interupt
	while(rtc_interrupt_flag);

	return 0;

}

/*
 * rtc_write()
 *   DESCRIPTION: Accepts a 4 byte integer value which indicates
 *                the interrupt rate in Hertz. Sets the RTC to that rate.
 *   INPUTS: buf - the indicated hertz frequency the RTC needs to be set to
 *           nbytes -- the number of bytes to set
 *   OUTPUTS: number of bytes written
 *   RETURN VALUE: nbytes on success, -1 on failure
 *   SIDE EFFECTS: changes RTC frequency
 */
int32_t rtc_write(int32_t fd, const void* buf, int32_t nbytes){

    /*Extract desired frequency from buffer*/
    int32_t* buffer = (int32_t*)buf;
    
	/*initialization of holder variable*/
	int32_t temp_freq;

    /*Boundary check to ensure we get proper 4 byte frequency value*/
	if(0x4 != nbytes || *buffer == NULL){
		return -1;
	}

	/*Obtain desired frequency rate*/
	else{
		temp_freq = *buffer;
	}

    /*Unwanted frequencies return failure/error*/
    if(temp_freq == 2048 || temp_freq == 4096 || temp_freq == 8192){
		return -1;
	}

	/*Set the RTC to the specific rate*/
	set_frequency(temp_freq);

    return nbytes;

}

/*
 * set_frequency()
 *   DESCRIPTION: Helper function used to set the interrupt frequency of
 *                the RTC.
 *   INPUTS: frequency_ - frequency rate the RTC needs to be set to
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: changes RTC frequency
 */
void set_frequency(int32_t frequency_){

  /*Initialization of variables*/
	char set_rate; //holds frequency rate to be sent to RTC
	unsigned char temp_val; //holds intial value from RTC register

    /*Store value from register A*/
    outb(REGISTER_A, RTC_PORT);

    temp_val = inb(READ_PORT);
    
	/*Maps the desired interrupt rate to corresponding RTC values from
	  pg. 19 in the documentation*/
	switch(frequency_){

	case TWO_HZ:
		set_rate = 0xF;
		break;

	case FOUR_HZ:
		set_rate = 0xE;
		break;

	case EIGHT_HZ:
		set_rate = 0xD;
		break;

	case SIXTEEN_HZ:
		set_rate = 0xC;
		break;

	case THIRTY_TWO_HZ:
		set_rate = 0xB;
		break;

	case SIXTY_FOUR_HZ:
		set_rate = 0xA;
		break;

    case ONE_HUNDRED_TWENTY_EIGHT_HZ:
    	set_rate = 0x9;
  		break;

    case TWO_HUNDRED_FIFTY_SIX_HZ:
    	set_rate = 0x8;
    	break;

	case FIVE_HUNDRED_TWELVE_HZ:
    	set_rate = 0x7;
	  	break;

	case ONE_THOUSAND_TWENTY_FOUR_HZ:
        set_rate = 0x6;
        break;

  	default:
  		return;
	}

	/*Set interrupt rate on RTC using A[3:0]*/
	outb(REGISTER_A, RTC_PORT);

	outb((0xF0 & temp_val) | set_rate, READ_PORT);

}
