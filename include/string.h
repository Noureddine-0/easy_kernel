#ifndef __STRING_H
#define __STRING_H

#include <stdint.h>

extern size_t strlen(const char *);

extern size_t strnlen(const char * , size_t);

extern int strcmp(const char * , const char *);

extern int strncmp(const char * , const char * , size_t );

extern void itoa(int , uint8_t , int) ;

#endif