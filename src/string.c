#include "../include/types.h"

#define TOLOWER(x) ((x) | 0x20)

int strcmp(char *s1, char *s2){

	int out = 0 ;

	while(*s1 || *s2){
		out = *s1 - *s2
		if (out)
			return out ;
		s1++;
		s2++;
	}
	return 0 ;
}

int stcncmp(char *s1 , char *s2 , size_t len){
	int out = 0 ;

	while(len && *s1 && *s2){
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

size_t memcpy(void *m1 , void *m2 , size_t maxlen){
	size_t len = maxlen;
	while(len){
		*(char *)m1 = *(char *m2);
		len --;
	}
	return maxlen - len ;
}

size_t memset(void *m1 , char c , size_t ,maxlen){
	size_t len  = maxlen ;
	while(len){
		*(char *)m1 = c;
		len --;		
	}
	return maxlen -len ;
}


