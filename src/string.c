#include <stdint.h>
#include <errno.h>


//#define ABS(X) (((X) > 0) ? (X) : -(X))

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
 * strncmp - Compare two strings in a fixed range
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



//long strtol(const char *str , char **endptr , int base){
	//TODO 
//}


