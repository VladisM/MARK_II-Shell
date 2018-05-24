#ifndef DEBUG	

#include "cmds.h"
#include "../libs/return_codes.h"
#include "../interface/io.h"

#include <pwrmng.h>

int poweroff(int argc, char *argv[]){	
	send_string("Bye!");
	pwrmng_power_off();
	while(1);
	return RET_OK;
}

void poweroff_help(){
	send_string("poweroff\n\n\rShutdown whole system.\n\r");
}

#endif
