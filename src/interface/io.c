#include "io.h"
#include <uart.h>

#ifndef DEBUG
#include "vgaio.h"
#include "ps.h"
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
	while(1){
		char data = '\0';
		
		//try to read char from UART or PS2
		if((USR0 & USR0_rxcount) > 0){
			data = URDR0;				
		}
		#ifndef DEBUG
		if(input_buffer_count > 0){
			data = get_char();
		}
		#endif
		
		//if something  was readed return it!
		if(data != '\0'){
			return data;
		}
	}
}
	
void io_init(){
	UCR0 |= ( UCR0_txen | UCR0_rxen | (UCR0_N & 0xEF) );
	#ifndef DEBUG
	vgaio_clear();
	vgaio_home();
	#endif	
}
