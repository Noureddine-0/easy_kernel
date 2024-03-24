#include <multiboot.h>

/*Compliace with multiboot specification , multiboot specification allows each compliant bootloader implementation to boot any compliant
operating system kernel

Required multiboot fields in the multiboot header
	Magic: and it should be 0x1BADB002
	Flags : Specify feautues that the OS image request from the bootloader
		ALIGN : all boot modules loaded along with the operating system must be aligned on page (4K) boundaries.
		MEMINFO: The bootloader must provide information about available memory through the 'mem_' fileds of the multiboot information structure


The multiboot header must be contained in completely within the first 8192 bytes of the OS image , abd must be  4 bytes aligned .
Additional info : https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Specification
*/

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
//	push %eax
//	push %ebx
	call kmain
	cli
	hlt
1:
	jmp 1b




