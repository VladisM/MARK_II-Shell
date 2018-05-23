#include "cmds.h"
#include "../libs/return_codes.h"
#include "../interface/io.h"

#include <lfsr.h>

static int rand_number();
static int atoi(char c);
static char itoa(int i);

int game(int argc, char argv[][INBUF_LEN]){
	int x = 0;
	char x_key = 0;
	int round = 0;
	int number;
	
	number = rand_number();
	
	send_string("I have an integer from <0;7>, try to guess it!\n\r");
	
	while(1){
		
		if(round == 5){
			send_string("You really tried to guess five times?! You are such a loser!!!\n\r");
			goto FAIL;
		}			
			
		send_string("Your guess: ");
		x_key = get_char();	
		send_char(x_key);
		x = atoi(x_key);		
		send_string("\n\r");
		
		if(x < 0){
			send_string("You press key out of interval! Are you drunk?!\n\r");
			goto FAIL;	
		}
		if(x > number){
			send_string("My number is smaller.\n\r");
			round++;
			continue;
		}
		if(x < number){
			send_string("My number is bigger.\n\r");
			round++;
			continue;			
		}
		if(x == number){
			goto WIN;
		}		
	}
WIN:
	x_key = itoa(round + 1);	
	send_string("\n\rYou are winner in round ");
	send_char(x_key);
	send_string("!\n\r"); 
	return RET_OK;
FAIL:	
	send_string("\n\rYou are failed!\n\r");
	return RET_OK;
}

void game_help(){
	send_string("game\n\n\rSimple number guessing game.\n\r");
}

static int rand_number(){
	int rand = LFSR_RN;	
	rand &= 0x07;
	return rand;
}

static int atoi(char c){
	switch(c){
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		default: return -1;
	}
}

static char itoa(int i){
	switch(i){
		case 0: return '0';
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		default: return '\0';
	}
}
