/*
* Here we specify the entrypoint for the kernel , if we did not do that ,we will start executing the multiboot header
*/
ENTRY(_start)


/* Linker script 
*/
SECTIONS{
	. = 1M;

	.text BLOCK(4K):ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	.rodata BLOCK(4K):ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K):ALIGN(4K)
	{
		*(.data)
	}

	.bss BLOCK(4K):ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}