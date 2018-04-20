#include "loop.h"
#include <pwrmng.h>

int main(){	
	
	#ifndef DEBUG
	pwrmng_init();
	#endif
	
	shell_init();
	shell_loop();	
	return 0;
}
