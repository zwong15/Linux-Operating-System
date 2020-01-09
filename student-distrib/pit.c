#include "pit.h"
#include "lib.h"
#include "idt.h"
#include "system_calls.h"
#include "context_switch.h"
#include "terminal.h"
#include "paging.h"
#include "keyboard.h"

uint8_t shells_on_start = 0;
uint8_t sched_count = 0;
uint32_t sched_entry_point;
uint32_t t1_esp;
uint32_t t1_ebp;
uint32_t t2_esp;
uint32_t t2_ebp;
uint32_t t3_esp;
uint32_t t3_ebp;
int printer = 0;
uint8_t process_num;
extern uint32_t inode_nums[SIX_];
extern uint8_t p3_flag;
extern int8_t update_ebp;
extern uint8_t global_flag[SIX_];
extern int dont_run;
extern uint32_t ready[NUM_PROCESS];
extern uint32_t flag_enter_for_pit;
extern int process_flag;
extern int firt;

/*
 * pit_init(){
 *   DESCRIPTION: initializes the pit
 *   INPUTS: nONE_
 *   OUTPUTS: nONE_
 *   RETURN VALUE: void
 *   SIDE EFFECTS: sets pit to about 12 ms
 *
 */
void pit_init(){
  /*Calculate divisor value for PIT interrupts*/
  int divisor = PIT_INIT_FREQ / DIVIDEND;
  /*Obtain command value from PIT*/
  outb(SQUARE_MODE_3, COMMAND_REG);
  /*Calculate low byte of desired time*/
  int low_byte = divisor & MASK_;
  /*Output to channel of PIT*/
  outb(low_byte, CHANNEL_0);
  /*Calculate high byte of PIT*/
  int high_byte = divisor >> SHIFT_EIGHT;
  /*Output to channel of PIT*/
  outb(high_byte, CHANNEL_0);

  /*Send EOI*/
  enable_irq(IRQ_LINE_PIT);

  return;
}

/*
 * pit_interrupt_handler(void)
 *   DESCRIPTION: sets up scheduling
 *   INPUTS: nONE_
 *   OUTPUTS: nONE_
 *   RETURN VALUE: void
 *   SIDE EFFECTS: switches what process we are doing
 *
 */
void pit_interrupt_handler(void){
  // send end of interrupt
  send_eoi(IRQ_LINE_PIT);

  cli();
  // used to hold esp and ebp
  uint32_t esp;
  uint32_t ebp;

  uint8_t i;

  if(shells_on_start == ONE_){
    sched_count = ONE_;
    // save shell 1's ebp and esp
    asm volatile(
       "movl %%esp, %0;"
      :"=g"(esp)
    );
    t1_esp = esp;
    asm volatile(
       "movl %%ebp, %0;"
      :"=g"(ebp)
    );
    t1_ebp = ebp;
    // create the second shell
    execute((uint8_t*)"shell");
  }

else if(shells_on_start == TWO_){
  sched_count = TWO_;
  // save shell 2's ebp and esp
  asm volatile(
     "movl %%esp, %0;"
    :"=g"(esp)
  );
  t2_esp = esp;
  asm volatile(
     "movl %%ebp, %0;"
    :"=g"(ebp)
  );
  t2_ebp = ebp;

  // create the third shell
  execute((uint8_t*)"shell");
}

else if(shells_on_start == THREE_){
  // save shell 3's ebp and esp
  sched_count = ZERO_;
  asm volatile(
     "movl %%esp, %0;"
    :"=g"(esp)
  );
  t3_esp = esp;
  asm volatile(
     "movl %%ebp, %0;"
    :"=g"(ebp)
  );
  t3_ebp = ebp;
  shells_on_start++;
}
else if(sched_count == ZERO_){
   // save terminal 3 esp and ebp
   asm volatile(
      "movl %%esp, %0;"
     :"=g"(esp)
   );
   t3_esp = esp;
   asm volatile(
      "movl %%ebp, %0;"
     :"=g"(ebp)
   );
   t3_ebp = ebp;
 }

 else if(sched_count == ONE_){
   // save terminal 1 esp and ebp
   asm volatile(
      "movl %%esp, %0;"
     :"=g"(esp)
   );
   t1_esp = esp;
   asm volatile(
      "movl %%ebp, %0;"
     :"=g"(ebp)
   );
   t1_ebp = ebp;
 }

 else if(sched_count == TWO_){
   // save terminal 2 esp and ebp
   asm volatile(
      "movl %%esp, %0;"
     :"=g"(esp)
   );
   t2_esp = esp;
   asm volatile(
      "movl %%ebp, %0;"
     :"=g"(ebp)
   );
   t2_ebp = ebp;
 }

 // run this part after we have created the THREE_ shells
 if(shells_on_start > TWO_){
   sched_count++;
   sched_count = sched_count % THREE_;

   // grab the last process on terminal 1
   if(sched_count == ONE_){
     ebp = t1_ebp;
     for(i = THREE_; i >= ONE_; i--){
       if(terminal_1.PID_array[i-ONE_] != ZERO_){
         process_num = terminal_1.PID_array[i-ONE_];
         break;
       }
       else{
         process_num = ZERO_;
       }
     }
   }

   // grab the last process on terminal 2
   else if(sched_count == TWO_){
     ebp = t2_ebp;
     for(i = THREE_; i >= ONE_; i--){
       if(terminal_2.PID_array[i-ONE_] != ZERO_){
         process_num = terminal_2.PID_array[i-ONE_];
         break;
       }
       else{
         process_num = ONE_;
       }
     }
   }

   // grab the last process on terminal 3
   else{
     ebp = t3_ebp;
     for(i = THREE_; i >= ONE_; i--){
       if(terminal_3.PID_array[i-ONE_] != ZERO_){
         process_num = terminal_3.PID_array[i-ONE_];
         break;
       }
       else{
         process_num = TWO_;
       }
     }
   }

   //remap
   page_dir[PROCESS_ENTRY].pointer = ((EIGHTMB + (process_num * FOMB))>>TWELVE);
   //flush tlb
   asm(
       "movl %cr3, %eax;"
       "movl %eax, %cr3;"
   );

   // set the tss values to the next process
   tss.esp0 = EIGHTMB-(EIGHTKB*process_num)-FOURBYT;

   // put the ebp value into the ebp register
   asm volatile(
      "movl %0, %%ebp;"
     :
     : "r"(ebp)
     : "%ebp"
   );

 }
 sti();

 asm volatile(
   "leave;"
   "ret;"
 );
  return;
}
