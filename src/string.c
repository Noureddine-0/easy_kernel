#include "../include/types.h"

//Copied from string.c in linux source code

# define CC_SET(c) "\n\t/* output condition code " #c "*/\n"
# define CC_OUT(c) "=@cc" #c

int memcmp(const void *s1, const void *s2, size_t len){
    int diff;
    asm("repe; cmpsb" CC_SET(nz)
        : CC_OUT(nz) (diff), "+D" (s1), "+S" (s2), "+c" (len));
    return diff;
}

// finish copying here. 

int strcmp(char *s1, char *s2){

	int out = 0 ;

	while(*s1 || *s2){
		out = *s1 - *s2;
		if (out)
			return out ;
		s1++;
		s2++;
	}
	return 0 ;
}

int stcncmp(char *s1 , char *s2 , size_t len){
	int out = 0 ;

	while(len && (*s1 || *s2)){
		out = *s1 - *s2 ;
		if (out)
			return out ;

		len--;
		s1++;
		s2++;
	}
	return 0 ;
}

size_t strlen(char *s){
	size_t len = 0;
	while(*s){
		len++;
		s++;
	}
	return len;
}

size_t strnlen(char *s , size_t maxlen){
	size_t len  = maxlen ;
	while(*s && len){
		len--;
		s++;
	}
	return (maxlen - len);
}
