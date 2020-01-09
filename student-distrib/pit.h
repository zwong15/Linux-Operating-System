#ifndef _PIT_H
#define _PIT_H

#define PIT_INIT_FREQ 1193180
#define COMMAND_REG 0x43
#define CHANNEL_0 0x40
#define SQUARE_MODE_3 0x36
#define IRQ_LINE_PIT 0
#define SHIFT_EIGHT 8
#define MASK_ 0xFF
#define TWELVE 12
#define ZERO_ 0
#define ONE_ 1
#define TWO_ 2
#define THREE_ 3
#define SIX_ 6
#define DIVIDEND 100


void pit_init();
void pit_interrupt_handler(void);

#endif
