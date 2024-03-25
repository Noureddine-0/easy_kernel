#include <console.h>
#include <stdint.h>
#include <string.h>



/**
 * Write a simple string to the output without formatting
 */

void putchark(char c){
	terminal_putchar(c);
}

int putk(const char *buffer){
	size_t size  =  strlen(buffer);
	terminal_writestring(buffer);
	return size;
}

/**
 * printk : formatting output
 * format : The format of the output
 */


