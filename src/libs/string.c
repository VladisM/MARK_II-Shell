#include "string.h"

int strcmp(char* s1, char* s2){
	while(*s1 == *s2){
		if(*s1 == 0) return 1;
		s1++;
		s2++;
	}
	return 0;
}

void strcpy(char* s1, char* s2){
	int i = 0;
	do{
		s1[i] = s2[i];
		i++;		
	}while(s2[i] != '\0');
}
