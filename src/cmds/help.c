#include "cmds.h"
#include "../libs/return_codes.h"
#include "../libs/string.h"
#include "../interface/io.h"

int help(int argc, char argv[][INBUF_LEN]){
	
	if(argc == 1){
		send_string("MARK-II Shell\n\n\r");
		
		send_string("Built-in cmds:\n\r");
		send_string(" ping      test connection\n\r");
		send_string(" help      show help\n\r");
		send_string(" beep      produce sound\n\r");
		send_string(" game      play simple game\n\r");
		#ifndef DEBUG
		send_string(" poweroff  disable power\n\r"); 
		#endif
		
		send_string("\n\rFor info about cmd use:\n\r");
		send_string(" >help cmd\n\n\r");
	}
	else if(argc == 2){
		if(strcmp(argv[1], "help")){
			help_help();
			return RET_OK;
		}
		else if(strcmp(argv[1], "ping")){
			ping_help();
			return RET_OK;
		}
		else if(strcmp(argv[1], "beep")){
			beep_help();
			return RET_OK;
		}
		else if(strcmp(argv[1], "game")){
			game_help();
			return RET_OK;
		}
		#ifndef DEBUG
		else if(strcmp(argv[1], "poweroff")){
			poweroff_help();
			return RET_OK;
		}
		#endif
		else{
			return RET_NOT_VALID_ARG;
		}
	}
	else{
		return RET_TOO_MUCH_ARGS;
	}
	
	return RET_OK;	
}

void help_help(){
	send_string("Help! I need somebody!\n\r");
	send_string("Help! Not just anybody!\n\r");
	send_string("Help! You know I need someone!\n\r");
	send_string("Help!\n\r");
}
