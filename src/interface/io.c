#include "io.h"
#include <uart.h>

#ifndef DEBUG
#include "vgaio.h"
#endif

void send_char(char c){
	while((USR0 & USR0_txcount) != 0);
	UTDR0 = c;	
	#ifndef DEBUG
	vgaio_putc(c);
	#endif
}

void send_string(char *c){
	for(int i = 0; c[i] != 0; i++){
		send_char(c[i]);
	}	
}

char get_char(){
	while((USR0 & USR0_rxcount) == 0);
	return (char)URDR0;		
}
	
void io_init(){
	UCR0 |= ( UCR0_txen | UCR0_rxen | (UCR0_N & 0xEF) );
	#ifndef DEBUG
	vgaio_clear();
	vgaio_home();
	#endif	
}
