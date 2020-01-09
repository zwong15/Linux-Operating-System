#define ASM     1
#include "x86_desc.h"

.text
.globl load_paging

load_paging:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %esi
	pushl %edi
	mov  page_dir, %eax
	movl %eax, %cr3
	movl %cr4, %eax
	orl  $0x00000010, %eax
	movl %eax, %cr4
	movl %cr0, %eax
	orl	 $0x80000001, %eax
	movl %eax, %cr0
	popl %edi
	popl %esi
	popl %ebx
	popl %ebp
	ret
	
