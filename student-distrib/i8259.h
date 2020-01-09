/* i8259.h - Defines used in interactions with the 8259 interrupt
 * controller
 * vim:ts=4 noexpandtab
 */

#ifndef _I8259_H
#define _I8259_H

#include "types.h"

/* Ports that each PIC sits on */
#define MASTER_8259_PORT    0x20
#define MASTER_DATA_PORT    0x21
#define SLAVE_8259_PORT     0xA0
#define SLAVE_DATA_PORT     0xA1

#define NUM_PORTS           15
#define MASTER_PORTS        7
#define SLAVE_PORTS         8
#define MASK                0xFF

#define TIMER_CHIPS         0
#define SLAVE_PIC           2

#define IRQ0_ON    0xFE
#define IRQ1_ON    0xFD
#define IRQ2_ON    0xFB
#define IRQ3_ON    0xF7
#define IRQ4_ON    0xEF
#define IRQ5_ON    0xDF
#define IRQ6_ON    0xBF
#define IRQ7_ON    0x7F
#define IRQ8_ON    0xFE
#define IRQ9_ON    0xFD
#define IRQ10_ON   0xFB
#define IRQ11_ON   0xF7
#define IRQ12_ON   0xEF
#define IRQ13_ON   0xDF
#define IRQ14_ON   0xBF
#define IRQ15_ON   0x7F

#define IRQ0_OFF    0x01
#define IRQ1_OFF    0x02
#define IRQ2_OFF    0x04
#define IRQ3_OFF    0x08
#define IRQ4_OFF    0x10
#define IRQ5_OFF    0x20
#define IRQ6_OFF    0x40
#define IRQ7_OFF    0x80
#define IRQ8_OFF    0x01
#define IRQ9_OFF    0x02
#define IRQ10_OFF   0x04
#define IRQ11_OFF   0x08
#define IRQ12_OFF   0x10
#define IRQ13_OFF   0x20
#define IRQ14_OFF   0x40
#define IRQ15_OFF   0x80

/* Initialization control words to init each PIC.
 * See the Intel manuals for details on the meaning
 * of each word */
#define ICW1                0x11
#define ICW2_MASTER         0x20
#define ICW2_SLAVE          0x28
#define ICW3_MASTER         0x04
#define ICW3_SLAVE          0x02
#define ICW4                0x01

/* End-of-interrupt byte.  This gets OR'd with
 * the interrupt number and sent out to the PIC
 * to declare the interrupt finished */
#define EOI                 0x60

/* Externally-visible functions */

/* Initialize both PICs */
void i8259_init(void);
/* Enable (unmask) the specified IRQ */
void enable_irq(uint32_t irq_num);
/* Disable (mask) the specified IRQ */
void disable_irq(uint32_t irq_num);
/* Send end-of-interrupt signal for the specified IRQ */
void send_eoi(uint32_t irq_num);

#endif /* _I8259_H */
