#ifndef _RTC_H
#define _RTC_H

#include "types.h"

#define REGISTER_A 0xA
#define REGISTER_B 0xB
#define REGISTER_C 0xC
#define REGISTER_D 0xD

#define BIT6      0x40
#define RTC_PORT  0x70
#define READ_PORT 0x71

#define IRQ_LINE 8

#define DISABLE_INTERRUPTS 0x8B

#define TWO_HZ 2
#define FOUR_HZ 4
#define EIGHT_HZ 8
#define SIXTEEN_HZ 16
#define THIRTY_TWO_HZ 32
#define SIXTY_FOUR_HZ 64
#define ONE_HUNDRED_TWENTY_EIGHT_HZ 128
#define TWO_HUNDRED_FIFTY_SIX_HZ 256
#define FIVE_HUNDRED_TWELVE_HZ 512
#define ONE_THOUSAND_TWENTY_FOUR_HZ 1024
/*flag variable to indicate if interrupt is active*/
volatile int32_t rtc_interrupt_flag;

/*function used to initialize the RTC*/
void init_rtc();

/*handler for RTC interrupts*/
void rtc_interrupt_handler(void);

/*function used to initialize RTC frequency to 2 Hz*/
int32_t rtc_open(const uint8_t* filename);

/*function used to restore RTC to starting state*/
int32_t rtc_close(int32_t fd);

/*function used to block interrupt until next one occurs*/
int32_t rtc_read(int32_t fd, void* buf, int32_t nbytes);

/*function used to change the RTC frequency*/
int32_t rtc_write(int32_t fd, const void* buf, int32_t nbytes);

/*helper function used to set the RTC frequency*/
void set_frequency(int32_t frequency_);


#endif
