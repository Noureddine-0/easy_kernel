/*Declare constants for the multiboot header*/
.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BAD002
.set checksum, -(MAGIC+FLAGS)

.section .multiboot
	.align 4
	.long MAGIC
	.long FLAGS
	.long checksum


/*Creating a small stack for the kernel . The stack on x86 must be 16-byte aligned according 
to System V ABI standard and de-facto extensions
*/

.section .stack nobits

	stack_bottom:
	.skip 16384
	stack_top:


.section .text

.global _start
.type _start , @function
_start:
	
	mov $stack_top , %esp

/* Enter the high level kernel . The ABI requires the stack is 16-byte aligned at the time
of the call instruction
*/
	call kmain
	cli
	hlt
1:
	jmp 1b

.size _start, . - _start
