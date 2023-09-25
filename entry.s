.set MAGIC, 0x1BADB002
.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS , ALIGN | MEMINFO
.set checksum , -(FLAGS + MAGIC)

.section .multiboot
	.align	4
	.long	MAGIC
	.long 	FLAGS
	.long	checksum

.section .bss
	.align 16
	bottom_stack:
	.skip 16384
	top_stack:


.section .text
	.global _start
	.type _start , @function
 

_start:

	mov $top_stack, %esp
	call kmain

	cli
	hlt
1:
	jmp 1b

.size _start , . - _start



