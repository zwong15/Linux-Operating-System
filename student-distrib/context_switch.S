# context_switch

#define ASM 1

#include "x86_desc.h"



.globl process_flag
.globl entry_point
.globl esp_holder
.globl privilege_switch_asm

privilege_switch_asm:
	#movl %esp, esp_holder # save old value of esp
	cli
	pushl $0x2B						#SS
	movw $0x2B, %dx				# move the SS into ds reg
	movw %dx, %ds					# cont.

	pushl $0x83FFFFC      #ESP

	pushf           			#push eflags
	popl %eax		 					#push eflags onto EAX
	orl  $0x200, %eax  	#set eflags bits
	push %eax           	#puts new eflags to stack

	pushl $0x23    				#push CS onto stack

	pushl entry_point			#push 24-27 onto stack | EIP

	iret
