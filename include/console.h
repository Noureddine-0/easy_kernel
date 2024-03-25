#include <stdint.h>


/* 
* This header file a declaration of functions designed to facilitate writing to console . 
*/ 

#ifndef __CONSOLE_H
#define __CONSOLE_H

/*
 * This struct is responsibe for managing the stdout buffer :
 * videomem_arrary : is the buffer containg the characters to be printed . Each element represent a line (Not optimized for now)
 * virtual_cursor_position : represent where the cursor is , it is used to append data to the buffer . Note that exceeding the size buffer will result in the 
 * direct flush of the buffer . This will also represent the end where to stop writing .
 * start : From where position from the buffer will start printing .
 * write : While appending to the buffer , 
 */

struct vga_terminal{
	uint8_t *buffer ;
	size_t virtual_cursor_position;
	size_t start;
};


extern void __InitializeTerminal(void);
extern void terminal_putchar(char );
extern void terminal_writestring(const char *);
extern void __TerminalClear(void);

#endif