#ifndef PS_H_included
#define PS_H_included

//init ps2 interface
void ps_init();

//get char from input buffer
char ps_get_char();

//char cunt in input buffer
extern volatile int input_buffer_count;

#endif
