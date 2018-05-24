#include "cmds.h"
#include "../libs/return_codes.h"
#include "../interface/io.h"

int ping(int argc, char *argv[]){
	send_string("pong!\n\r");
	return RET_OK;
}

void ping_help(){
	send_string("ping\n\n\r");
	send_string("Use it for testing connection\n\r");
}
