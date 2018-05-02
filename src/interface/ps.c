#include "ps.h"

#ifndef DEBUG

#include <intdrv.h>
#include <ps.h>

char keycode[] = {
	0x16, 0x1E, 0x26, 0x25, 0x2E, 0x36, 0x3D, 0x3E, 0x46, 0x45,
	0x66, 0x5A,
	0x1C, 0x32, 0x21, 0x23, 0x24, 0x2B, 0x34, 
	0x33, 0x43, 0x3B, 0x42, 0x4B, 0x3A, 0x31,
	0x44, 0x4D, 0x15, 0x2D, 0x1B, 0x2C, 0x3C,
	0x2A, 0x1D, 0x22, 0x35, 0x1A,
	0x00
};

char key[] = {
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'\b', '\n',
	'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N',
	'O', 'P', 'Q', 'R', 'S', 'T', 'U',
	'V', 'W', 'X', 'Y', 'Z',
	'\0'
};

char input_buffer[8];
int input_buffer_count = 0;

static char translate_key(char c){
	int i;
	for(i = 0; keycode[i] != c && keycode[i] != '\0'; i++);
	return key[i];
}

static int translate_stream(char c, char * out){
	static int break_code;	
	
	if(break_code == 1){		
		if(translate_key(c) == 0){
			return -1;		//ERROR - unknown key
		}
		else{
			break_code = 0;
			return 0;       //break ignored
		}
	}
	else{   
		if(c == 0xF0){
			break_code = 1;
			return 0;			
		}
		else{
			*out = translate_key(c); //translate key and return it
			return 1;
		}
	}	
}

__interrupt void ps_isr(){
	char data = PSBR0;
	if(translate_stream(data, &data) == 1){
		input_buffer[++input_buffer_count] = data;
	}
}

void ps_init(){	
	//enable interrupt from KB PS2 (PS2_0)
	PS2_0_VECTOR_REG = (unsigned int)(&ps_isr);
	INTMR |= INTMR_PS2_0_en;	
}

//return data from input buffer
char get_char(){
	if(input_buffer_count != 0){
		char data = input_buffer[0];
		for(int i = 1; i <= 7; i++){
			input_buffer[i - 1] = input_buffer[i];
		}	
		input_buffer_count--;
		return data;
	}
	return '\0';
}

#endif
