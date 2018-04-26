#include "cmds.h"
#include "return_codes.h"
#include "io.h"

#include <pwrmng.h>

int beep(int argc, char argv[][INBUF_LEN]){
	#ifndef DEBUG	
	pwrmng_beep_long();	
	#else
	send_string("BEEEEEEEEEEP!\n\r");
	#endif
	return RET_OK;
}

void beep_help(){
	send_string("beep\n\n\rProduce lound beep!\n\r");
}



