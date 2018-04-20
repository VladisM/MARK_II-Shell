#include "cmds.h"
#include "return_codes.h"
#include "io.h"

#include <pwrmng.h>

#ifndef DEBUG	

int poweroff(int argc, char argv[][33]){	
	send_string("Bye!");
	pwrmng_power_off();
	while(1);
	return RET_OK;
}

void poweroff_help(){
	send_string("poweroff\n\n\rShutdown whole system.\n\r");
}

#endif
