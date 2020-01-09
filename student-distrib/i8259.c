/* i8259.c - Functions to interact with the 8259 interrupt controller
 * vim:ts=4 noexpandtab
 */

#include "i8259.h"
#include "lib.h"

/* Interrupt masks to determine which interrupts are enabled and disabled */
uint8_t master_mask; /* IRQs 0-7  */
uint8_t slave_mask;  /* IRQs 8-15 */

/* 
 * i8259_init(void)
 *   DESCRIPTION: Initialize the 8259 PIC
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: the master and slave ports will
 *   be enabled
 */

void i8259_init(void) {
	master_mask = inb(MASTER_DATA_PORT);
	slave_mask = inb(SLAVE_DATA_PORT);
	outb(MASK, MASTER_DATA_PORT);
	outb(MASK, SLAVE_DATA_PORT);
	outb(ICW1, MASTER_8259_PORT);
	outb(ICW1, SLAVE_8259_PORT);
	outb(ICW2_MASTER, MASTER_DATA_PORT);
	outb(ICW2_SLAVE, SLAVE_DATA_PORT);
	outb(ICW3_MASTER, MASTER_DATA_PORT);
	outb(ICW3_SLAVE, SLAVE_DATA_PORT);
	outb(ICW4, MASTER_DATA_PORT);
	outb(ICW4, SLAVE_DATA_PORT);
	outb(master_mask, MASTER_DATA_PORT);
	outb(slave_mask, SLAVE_DATA_PORT);

	enable_irq(SLAVE_PIC);
	disable_irq(TIMER_CHIPS);
}

/* 
 * enable_irq(uint32_t irq_num)
 *   DESCRIPTION: Enable (unmask) the specified IRQ
 *   INPUTS: irq_num -- the IRQ line we want to enable
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: the IRQ lines will be masked according
 *   to the IRQ num we received
 */
 
void enable_irq(uint32_t irq_num) {
	//check for valid IRQ number
	if(irq_num < 0 || irq_num > NUM_PORTS){
		return;
	}
    /*mask the correct bits based on which IRQ we want to enable
	we AND the current mask with the new one to make sure we only change
	one bit to 0*/
	switch(irq_num){
		case(0):
			master_mask = master_mask & IRQ0_ON;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(1):
			master_mask = master_mask & IRQ1_ON;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(2):
			master_mask = master_mask & IRQ2_ON;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(3):
			master_mask = master_mask & IRQ3_ON;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(4):
			master_mask = master_mask & IRQ4_ON;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(5):
			master_mask = master_mask & IRQ5_ON;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(6):
			master_mask = master_mask & IRQ6_ON;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(7):
			master_mask = master_mask & IRQ7_ON;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(8):
			slave_mask = slave_mask & IRQ8_ON;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(9):
			slave_mask = slave_mask & IRQ9_ON;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(10):
			slave_mask = slave_mask & IRQ10_ON;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(11):
			slave_mask = slave_mask & IRQ11_ON;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(12):
			slave_mask = slave_mask & IRQ12_ON;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(13):
			slave_mask = slave_mask & IRQ13_ON;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(14):
			slave_mask = slave_mask & IRQ14_ON;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(15):
			slave_mask = slave_mask & IRQ15_ON;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		}
}

/* 
 * disable_irq(uint32_t irq_num)
 *   DESCRIPTION: Disable (mask) the specified IRQ
 *   INPUTS: irq_num -- the IRQ line we want to disable
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: the IRQ lines will be masked according
 *   to the IRQ num we received
 */
 
void disable_irq(uint32_t irq_num) {
	if(irq_num < 0 || irq_num > NUM_PORTS){
		return;
	}
	 /*mask the correct bits based on which IRQ we want to enable
	we OR the current mask with the new one to make sure we only change
	one bit to 1*/
	switch(irq_num){
		case(0):
			master_mask = master_mask | IRQ0_OFF;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(1):
			master_mask = master_mask | IRQ0_OFF;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(2):
			master_mask = master_mask | IRQ0_OFF;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(3):
			master_mask = master_mask | IRQ0_OFF;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(4):
			master_mask = master_mask | IRQ0_OFF;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(5):
			master_mask = master_mask | IRQ0_OFF;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(6):
			master_mask = master_mask | IRQ0_OFF;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(7):
			master_mask = master_mask | IRQ0_OFF;
			outb(master_mask, MASTER_DATA_PORT);
			break;
		case(8):
			slave_mask = slave_mask | IRQ8_OFF;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(9):
			slave_mask = slave_mask | IRQ9_OFF;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(10):
			slave_mask = slave_mask | IRQ10_OFF;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(11):
			slave_mask = slave_mask | IRQ11_OFF;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(12):
			slave_mask = slave_mask | IRQ12_OFF;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(13):
			slave_mask = slave_mask | IRQ13_OFF;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(14):
			slave_mask = slave_mask | IRQ14_OFF;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		case(15):
			slave_mask = slave_mask | IRQ15_OFF;
			outb(slave_mask, SLAVE_DATA_PORT);
			break;
		}
}

/* Send end-of-interrupt signal for the specified IRQ */
/* 
 * sen_eoi(uint32_t irq_num)
 *   DESCRIPTION: Send end-of-interrupt signal for the specified IRQ
 *   INPUTS: irq_num -- the IRQ line we want to disable
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: the pic will receive the EOI
 *   signal
 */

void send_eoi(uint32_t irq_num) {
	//check for valid IRQ num
	if(irq_num < 0 || irq_num > NUM_PORTS){
		return;
	}
	//if the IRQ num is on the master
	if(irq_num >= 0 && irq_num <= MASTER_PORTS){
		//mask the current IRQ bits with the EOI
		master_mask = EOI | irq_num;
		//send this new mask to the master port
		outb(master_mask, MASTER_8259_PORT);
	}
	//if the IRQ num is on the slave
	if(irq_num >= SLAVE_PORTS && irq_num <= NUM_PORTS){
		//mask the current IRQ bits with the EOI
		slave_mask = EOI | (irq_num-SLAVE_PORTS);
		//send the new mask to both the slave and master ports
		outb(slave_mask, SLAVE_8259_PORT);
		outb(EOI + 2, MASTER_8259_PORT);
	}
}
