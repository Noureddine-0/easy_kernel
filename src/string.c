#include <stdint.h>
#include <errno.h>


#define ABS(X) (((X) > 0) ? (X) : -(X))

/**
 * strlen - Calculates the length of a string until we reach \x00
 * @data : The string which we want to calculate the length
 */
size_t strlen(const char *data){
	size_t len = 0 ;

	while(*data){
		len++ ;
		data ++ ;
	}
	return len ;
}

/**
 * strnlen - Calculates the length of a string in a fixed range
 * @data : The string which we want to calculate the length
 * @maxlen : Max len we can reach
 */
size_t strnlen(const char *data , size_t maxlen){
	size_t len = maxlen ;

	while (*data && len){
		data ++ ;
		len --;
	}

	return (maxlen - len);
}

/**
 * strcmp - Compare two strings until we reach \x00 for one of them
 * @s1 : First string
 * @s2 : Second string
 */
int strcmp(const char *s1, const char *s2){
    while (*s2 || *s1){
        if(*s2 != *s1){
            return *s1 - *s2;
        }
	    s1++;
        s2++;
    }
    return 0 ;
}

/**
 * strncmp - Compare two arrays of char in a fixed range
 * @s1 : First string
 * @s2 : Second string
 * @maxlen : Max number of bytes to compare
 */ 
int strncmp(const char *s1 , const char *s2 , size_t maxlen){
	size_t len = maxlen ;
	while (len && (*s2 || *s1)){
		len -- ;
		if (*s2 != *s1){
			return *s1 - *s2;
		}
		s1++;
		s2++;
	}
	return 0 ;
}



/**
 * strrev - reverse an array of char
 * @buffer : The array to be reversed
 */


void strrev(char *buffer){
	size_t size  =  strlen(buffer);
	size_t index= 0 ;
	char temp;
	while(index < size/2 ){
		temp =  buffer[index];
		buffer[index] = buffer[size - index -1];
		buffer[size-index -1] =  temp;
		index++;
	}
}

/**
 * itoa : Integer to array
 * @num : The integer to convert
 * @buffer : The buffer where to write the converted integer
 * @base : The base of the integer
 */

void itoa(int num , char *buffer , int base){
	uint32_t cp_num ;
	int remainder ;
	size_t index = 0 ;
	int is_negative = 0;

	if (base==16){
		cp_num =  (uint32_t)num ;
	}else{
		if (num < 0 )
			is_negative++;
		cp_num = ABS(num);
	}
	
	while (cp_num){
		remainder =  cp_num % base ;
		if (remainder  >= 0xa){
			buffer[index] = 'A' + (char)(remainder -0xA);
		}else{
			buffer[index] = '0'+(char)remainder;
		}
		index++;
		cp_num /=base;
	}
	if (is_negative){
		buffer[index] ='-';
		index++;
	}
	if (base == 16){
		buffer[index++] = 'x';
		buffer[index++]  = '0';
		buffer[index] = '\0';
	}
	strrev(buffer);
}

//long strtol(const char *str , char **endptr , int base){
	//TODO 
//}



