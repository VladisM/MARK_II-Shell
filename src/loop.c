#include "loop.h"
#include "io.h"
#include "string.h"
#include "cmds.h"
#include "return_codes.h"

static int get_cmd();
static int tokenize_cmd();
int eval_cmd(int argc);

char input_string[33];
char input_tokens[10][33];

void shell_init(){
	io_init();
}

void shell_loop(){
	int argc, ret = 0;
	
	while(1){
		
		//get cmd from io
		if(get_cmd() < 0){
			send_string("Input ERR: Input buffer overflow!\n\r");
			continue;
		}
		
		//tokenize it
		argc = tokenize_cmd();
		if(argc < 0){
			switch(argc){
				case -1:
					send_string("Parse ERR: Too many args!\n\r");
					break;
				case -2:
					send_string("Parse ERR: Empty command!\n\r");
					break;
				default:
					break;
			}
			continue;
		}
		
		//execute it
		ret = eval_cmd(argc);
		if(ret < 0){
			switch(ret){
				case RET_NOT_SUCH_CMD:
					send_string("ERR: Not such cmd!\n\r");
					break;
				case RET_TOO_MUCH_ARGS:
					send_string("ERR: Too much arguments!\n\r!");
					break;
				case RET_NOT_VALID_ARG:
					send_string("ERR: Arguments are not valid!\n\r");
					break;
				default:
					send_string("ERR: Unknown error!\n\r");
					break;
			}
			continue;
		}
	}
}

static int get_cmd(){
	char key = 0;
	int pos = 0;
	
	send_char('>');
	
	do{
		//wait for key
		key = get_char();
		
		//if key is backspace or delete
		if (key == 0x0B || key == 0x7F){			
			if(pos > 0){
				pos--;
				send_string("\b \b");
			}
			continue;
		}
		
		//store key
		if (key != 0x0D) input_string[pos++] = key;
		
		//not let input_string[] overflow!
		if(pos > 31){
			send_string("\n\r");
			input_string[pos] = 0x00;
			return -1;
		}

		//send key back		
		send_char(key);
		
	}while(key != 0x0D);

	//send CR and LF
	send_string("\n\r");
	
	//end string in input buffer
	input_string[pos] = 0;

	return 0; 
}

static int tokenize_cmd(){
	int str_pos = 0;
	int arg_count = 0;
	int pos_in_arg = 0;	
	char c = 0;
	
	do{
		//take one char from string
		c = input_string[str_pos++];
		
		
		if(c == 0x20){
			//if char is space replace it with 0 and continue with another argument
			if(input_string[str_pos] != 0){ //this will avoid emply arguments if input is like "cmd argA argB "
				input_tokens[arg_count++][pos_in_arg] = 0;
				pos_in_arg = 0;			
			}
		}			
		else{
			//else add char in current argument
			input_tokens[arg_count][pos_in_arg++] = c;			
		}
		
		//check if arg count doesn't exceed
		if(arg_count > 9){
			return -1;
		}
		
	}while(c != 0);
	
	//check if arg isn't empty
	if(input_tokens[0][0] == 0) return -2;
	
	//return count of arguments (should be >= 1)
	return (arg_count + 1);
}

int eval_cmd(int arg_count){
	
	if(strcmp(input_tokens[0], "ping")){
		return ping(arg_count, input_tokens);
	}
	else if(strcmp(input_tokens[0], "help")){
		return help(arg_count, input_tokens);
	}
	else if(strcmp(input_tokens[0], "beep")){
		return beep(arg_count, input_tokens);
	}
	#ifndef DEBUG
	else if(strcmp(input_tokens[0], "poweroff")){
		return poweroff(arg_count, input_tokens);
	}
	#endif
	else{
		return RET_NOT_SUCH_CMD;
	}
}
