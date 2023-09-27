#include <stdint.h>

/* Here you find some string manipulation functions like strlen , we'll add more
*whenever we need them
*/

size_t strlen(const char *data){
	size_t len = 0 ;

	while(*data){
		len++ ;
		data ++ ;
	}
	return len ;
}

size_t strnlen(const char *data , size_t maxlen){
	size_t len = maxlen ;

	while (*data && len){
		data ++ ;
		len --;
	}

	return (maxlen - len);
}


