#include "multiboot.h"
#include "x86_desc.h"
#include "lib.h"
#include "i8259.h"
#include "debug.h"
#include "tests.h"
#include "idt.h"
#include "handlers.h"
#include "rtc.h"
#include "keyboard.h"
#include "syscall_handler.h"
#include "system_calls.h"
#include "pit.h"
extern int exception;

/*
 * DE()
 *   DESCRIPTION: divide by zero exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if divide by zero exception happens
 *   it prints "Divide error"
 */
void DE(){
  cli();
  printf("Divide Error\n");
  exception = 1;
  sti();
}

/*
 * DB()
 *   DESCRIPTION: reserved exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if this excpetion which is reserved
 *   by intel happens print "RESERVED"
 */
void DB(){
  cli();
  printf("RESERVED\n");
  exception = 1;
  sti();
}

/*
 * NMI()
 *   DESCRIPTION: Non maskable interrupt exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if an NMI exception happens
 *   print "NMI Interrupt"
 */
void NMI(){
  cli();
  printf("NMI Interrupt\n");
  exception = 1;
  sti();
}

/*
 * BP()
 *   DESCRIPTION: Breakpoint exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if a breakpoint is set
 *   print "Breakpoint"
 */
void BP(){
  cli();
  printf("Breakpoint\n");
  exception = 1;
  sti();
}

/*
 * OF()
 *   DESCRIPTION: Overflow exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if overflow is detected
 *   print "Overflow"
 */
void OF(){
  cli();
  printf("Overflow\n");
  exception = 1;
  sti();
}

/*
 * BR()
 *   DESCRIPTION: Bound range exceeded exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if the bound range is exceeded
 *   print "Bound Range Exceeded"
 */
void BR(){
  cli();
  printf("Bound Range Exceeded\n");
  exception = 1;
  sti();
}

/*
 * UD()
 *   DESCRIPTION: Invalid opcode exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if an invalid opcode is passed
 *   print "Invalid opcode"
 */
void UD(){
  cli();
  printf("Invalid Opcode\n");
  exception = 1;
  sti();
}

/*
 * UD()
 *   DESCRIPTION: Device not available exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if a device is not available
 *   print "Device not available"
 */
void NM(){
  cli();
  printf("Device Not Available\n");
  exception = 1;
  sti();
}

/*
 * DF()
 *   DESCRIPTION: Double fault exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if a double fault is detected
 *   print "Double fault"
 */
void DF(){
  cli();
  printf("Double Fault\n");
  exception = 1;
  sti();
}

/*
 * CSO()
 *   DESCRIPTION: Coprocessor Segment Overrun exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if a coprocessor segment is overrun
 *   print "Coprocessor Segment Overrun"
 */
void CSO(){
  cli();
  printf("Coprocessor Segment Overrun\n");
  exception = 1;
  sti();
}

/*
 * TS()
 *   DESCRIPTION: Invalid TSS exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if an invalid TSS is detected
 *   print "Invalid TSS"
 */
void TS(){
  cli();
  printf("Invalid TSS\n");
  exception = 1;
  sti();
}

/*
 * NP()
 *   DESCRIPTION: Segment not present exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if a segment is not present
 *   print "Segment Not Present"
 */
void NP(){
  cli();
  printf("Segment Not Present\n");
  exception = 1;
  sti();
}

/*
 * SS()
 *   DESCRIPTION: Stack segment fault exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if a stack segment fault is detected
 *   print "Stack Segment Fault"
 */
void SS(){
  cli();
  printf("Stack Segment Fault\n");
  exception = 1;
  sti();
}

/*
 * GP()
 *   DESCRIPTION: General protection fault exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if a general protection fault is detected
 *   print "General Protection Fault"
 */
void GP(){
  cli();
  printf("General Protection Fault\n");
  exception = 1;
  sti();
}

/*
 * PF()
 *   DESCRIPTION: Page fault exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if a page fault is detected
 *   print "Page Fault"
 */
void PF(){
  cli();
  printf("Page Fault\n");
  exception = 1;
  halt((uint8_t)HALT_NUM);
}

/*
 * MF()
 *   DESCRIPTION: x87 FPU Floating-point error exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if a x87 FPU floating point error is detected
 *   print "x87 FPU Floating-Point Error"
 */
void MF(){
  cli();
  printf("x87 FPU Floating-Point Error\n");
  exception = 1;
  sti();
}

/*
 * AC()
 *   DESCRIPTION: Alignment check fault exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if an alignment check fault is detected
 *   print "Alignment Check Fault"
 */
void AC(){
  cli();
  printf("Alignment Check Fault\n");
  exception = 1;
  sti();
}

/*
 * MC()
 *   DESCRIPTION: Machine check fault exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if a machine check fault is detected
 *   print "Machine Check Fault"
 */
void MC(){
  cli();
  printf("Machine Check Fault\n");
  exception = 1;
  sti();
}

/*
 * XF()
 *   DESCRIPTION: SIMD Floating-Point exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if a SIMD Floating-Point fault is detected
 *   print "SIMD Floating-Point Exception"
 */
void XF(){
  cli();
  printf("SIMD Floating-Point Exception\n");
  exception = 1;
  sti();
}

/*
 * interrupt()
 *   DESCRIPTION: interrupt exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if an interrupt is detected
 *   it prints "Interrupt"
 */
void interrupt(){
  cli();
  printf("Interrupt\n");
  sti();
}

/*
 * interrupt2()
 *   DESCRIPTION: interrupt exception handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: if an interrupt is detected
 *   it prints "Interrupt2"
 */
void interrupt2(){
  cli();
  printf("Interrupt2\n");
  sti();
}

/*
 * idt_init()
 *   DESCRIPTION: initialize the IDT
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: void
 *   SIDE EFFECTS: set the bits for each entry in
 *   the IDT
 */
void idt_init(){
int i;
/*loop through each entry in the IDT and set the correct
priviledges and gates*/
for(i = 0; i < NUM_VEC; i++){
  idt[i].present = 1;
  idt[i].dpl = HIGH_PRIV;
  idt[i].size = 1;
  idt[i].reserved0 = 0;
  idt[i].reserved1 = 1;
  idt[i].reserved2 = 1;
  idt[i].reserved3 = 1;
  idt[i].seg_selector = KERNEL_CS;

  //set the system call vector priviledge
  if(i == SYS_CALL){
    idt[i].dpl = LOW_PRIV;
    idt[i].reserved3 = 1;
    SET_IDT_ENTRY(idt[i], syscall_handler);
  }

  //set the timer chip gate and offset
  if(i == PIT){
    idt[i].reserved3 = 0;
     SET_IDT_ENTRY(idt[i], pit_handler);
  }

  //set the keyboard gate and offset
  if(i == KEYBOARD){
    idt[i].reserved3 = 0;
    SET_IDT_ENTRY(idt[i], keyboard_handler);
  }

  //set gate and offset for IRQ3
  if(i == IRQ3){
    idt[i].reserved3 = 0;
     // SET_IDT_ENTRY(idt[i], interrupt);
  }

  //set gate and offset for IRQ4
  if(i == IRQ4){
    idt[i].reserved3 = 0;
     // SET_IDT_ENTRY(idt[i], interrupt);
  }

  //set gate and offset for IRQ5
  if(i == IRQ5){
    idt[i].reserved3 = 0;
     // SET_IDT_ENTRY(idt[i], interrupt);
  }

  //set gate and offset for IRQ6
  if(i == IRQ6){
    idt[i].reserved3 = 0;
     // SET_IDT_ENTRY(idt[i], interrupt);
  }

  //set gate and offset for IRQ7
  if(i == IRQ7){
    idt[i].reserved3 = 0;
     // SET_IDT_ENTRY(idt[i], interrupt);
  }

  //set gate and offset for the rtc
  if(i == RTC){
    idt[i].reserved3 = 0;
     SET_IDT_ENTRY(idt[i], rtc_handler);
  }

  //set gates and offsets for the rest of IRQ and NUM_VECS
  if(i > RTC){
    idt[i].reserved3 = 0;
     // SET_IDT_ENTRY(idt[i], interrupt);
  }
}

//set privledges for breakpoint and overflow exceptions
idt[BP_IDT].dpl = LOW_PRIV;
idt[OF_IDT].dpl = LOW_PRIV;

//set the correct offsets for the exceptions
SET_IDT_ENTRY(idt[DE_IDT], DE);
SET_IDT_ENTRY(idt[DB_IDT], DB);
SET_IDT_ENTRY(idt[NMI_IDT], NMI);
SET_IDT_ENTRY(idt[BP_IDT], BP);
SET_IDT_ENTRY(idt[OF_IDT], OF);
SET_IDT_ENTRY(idt[BR_IDT], BR);
SET_IDT_ENTRY(idt[UD_IDT], UD);
SET_IDT_ENTRY(idt[NM_IDT], NM);
SET_IDT_ENTRY(idt[DF_IDT], DF);
SET_IDT_ENTRY(idt[CSO_IDT], CSO);
SET_IDT_ENTRY(idt[TS_IDT], TS);
SET_IDT_ENTRY(idt[NP_IDT], NP);
SET_IDT_ENTRY(idt[SS_IDT], SS);
SET_IDT_ENTRY(idt[GP_IDT], GP);
SET_IDT_ENTRY(idt[PF_IDT], PF);
SET_IDT_ENTRY(idt[MF_IDT], MF);
SET_IDT_ENTRY(idt[AC_IDT], AC);
SET_IDT_ENTRY(idt[MC_IDT], MC);
SET_IDT_ENTRY(idt[XF_IDT], XF);

//load the idt
lidt(idt_desc_ptr);
}
