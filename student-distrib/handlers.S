#define ASM     1
#include "x86_desc.h"

# declare global labels
.globl keyboard_handler
.globl rtc_handler
.globl pit_handler


 # keyboard_handler
 #   DESCRIPTION: Calls our keyboard handler
 #   INPUTS: none
 #   OUTPUTS: none
 #   RETURN VALUE: none
 #   SIDE EFFECTS: Allows us to check the status and data
 #   ports of the keyboard by calling the handler
keyboard_handler:
    # save all registers and flags
    PUSH %ebp
    PUSH %eax
    PUSH %ecx
    PUSH %edx
    PUSH %edi
    PUSH %esi
    PUSH %ebx
    PUSHF

    # call the keyboard handler
    call key_handler

    # restore all registers and flags
    POPF
    POP %ebx
    POP %esi
    POP %esi
    POP %edx
    POP %ecx
    POP %eax
    POP %ebp

    #retrun control from the handler
    iret

 # rtc_handler
 #   DESCRIPTION: Calls our rtc handler
 #   INPUTS: none
 #   OUTPUTS: none
 #   RETURN VALUE: none
 #   SIDE EFFECTS: Allows us to generate RTC interrupts
 #   by calling the handler
rtc_handler:
    # save all registers and flags
    PUSH %ebp
    PUSH %eax
    PUSH %ecx
    PUSH %edx
    PUSH %edi
    PUSH %esi
    PUSH %ebx
    PUSHF


    # call the RTC handler
    call rtc_interrupt_handler

    # restore all registers and flags
    POPF
    POP %ebx
    POP %esi
    POP %esi
    POP %edx
    POP %ecx
    POP %eax
    POP %ebp

    # retrun control from the handler
    iret


  # pit_handler
  #   DESCRIPTION: Calls our PIT handler
  #   INPUTS: none
  #   OUTPUTS: none
  #   RETURN VALUE: none
  #   SIDE EFFECTS: Allows us to generate PIT interrupts
  #   by calling the handler
pit_handler:
     # save all registers and flags
     PUSH %ebp
     PUSH %eax
     PUSH %ecx
     PUSH %edx
     PUSH %edi
     PUSH %esi
     PUSH %ebx
     PUSHF

     # call the keyboard handler
     call pit_interrupt_handler

     # restore all registers and flags
     POPF
     POP %ebx
     POP %esi
     POP %esi
     POP %edx
     POP %ecx
     POP %eax
     POP %ebp

     #retrun control from the handler
     iret
