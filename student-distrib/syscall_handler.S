#define ASM 1
.text

#declare global labels
.globl syscall_handler

#handler for system calls
syscall_handler:
      cli

      #push registers on stack
      pushf
      pushl %ebp
      pushl %edi
      pushl %esi

      #push arguments for system call
      pushl %edx
      pushl %ecx
      pushl %ebx

      #check for validity of system call number
      cmpl $10, %eax
      jg   INVALID
      cmpl $0, %eax
      jle  INVALID
      addl $-1, %eax

      #jump to desired system call
      sti
      call *syscall_table(, %eax, 4)
      cli

      #jump to finish
      jmp  DONE

INVALID:
      #input -1 to indicate error/failure
      xorl %eax, %eax
      addl $-1, %eax

DONE:
      #pop registers
      popl %ebx
      popl %ecx
      popl %edx

      popl %esi
      popl %edi
      popl %ebp

      popf
      sti
      iret

#system call jumptable
syscall_table:
      .long halt, execute, read, write, open, close, getargs, vidmap, set_handler, sigreturn
