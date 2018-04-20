#include "cmds.h"
#include "return_codes.h"
#include "io.h"

int ping(int argc, char argv[][33]){
	send_string("pong!\n\r");
	return RET_OK;
}

void ping_help(){
	send_string("ping\n\n\r");
	send_string("Use it for testing connection\n\r");
}
