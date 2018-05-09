#include "cmds.h"
#include "../libs/return_codes.h"
#include "../libs/string.h"
#include "../interface/io.h"

#ifndef DEBUG
#include "../interface/vgaio.h"

static int echo_color();
static int convert_to_code(char name[INBUF_LEN]);
static int convert_to_name(int code, char *buffer);
#endif

int color(int argc, char argv[][INBUF_LEN]){	
#ifndef DEBUG
	if(argc == 1){
		return echo_color();
	}
	else if(argc == 2){
		int fg_col = convert_to_code(argv[1]);
		if(fg_col > 0){
			vgaio_set_color(fg_col, vgaio_bg_color);
			return RET_OK;
		}
		else{
			return RET_NOT_VALID_ARG;
		}
	}
	else if(argc == 3){
		int fg_col = convert_to_code(argv[1]);
		int bg_col = convert_to_code(argv[2]);
		if(fg_col > 0 || bg_col > 0){
			vgaio_set_color(fg_col, bg_col);
			return RET_OK;
		}
		else{
			return RET_NOT_VALID_ARG;
		}
	}	
	else{
		return RET_TOO_MUCH_ARGS;
	}	
#else
	send_string("You are using MARK-II Shell in emulator, there aren't any colors!\n\rAre you drunk?!\n\r");
	return RET_OK;
#endif
}

void color_help(){
	send_string("color <fg_col> <bg_col>\n\n\r");
	send_string("Use this command to change display color. Example ussage:\n\n\r");
	send_string(" > color                  get current colors\n\r");
	send_string(" > color <colF>           set foregroud collor to colF\n\r");
	send_string(" > color <colF> <colB>    set foregroud to colF and backgroud to colB\n\n\r");
}

#ifndef DEBUG
static int echo_color(){
	char bg[32];
	char fg[32];
	int x;
	
	if(convert_to_name(vgaio_fg_color, fg) < 0){
		return RET_GENERIC_ERROR;
	}
	if(convert_to_name(vgaio_bg_color, bg) < 0){
		return RET_GENERIC_ERROR;
	}
	
	send_string("You are using ");
	send_string(fg);
	send_string(" on ");
	send_string(bg);
	send_string(".\n\r");
	return RET_OK;
}


static int convert_to_code(char name[INBUF_LEN]){
	if     (strcmp(name, "black"))		return BLACK;
	else if(strcmp(name, "red"))		return RED;
	else if(strcmp(name, "green"))		return GREEN;
	else if(strcmp(name, "brown"))		return BROWN;
	else if(strcmp(name, "yellow"))		return YELLOW;
	else if(strcmp(name, "blue"))		return BLUE;
	else if(strcmp(name, "magenta"))	return MAGENTA;
	else if(strcmp(name, "cyan"))		return CYAN;
	else if(strcmp(name, "gray"))		return GRAY;
	else if(strcmp(name, "white"))		return WHITE;
	else return -1;
}

static int convert_to_name(int code, char *buffer){
	switch(code){
		case BLACK: 
			strcpy(buffer, "black");
			break;
		case LIGHT_GRAY:		
			strcpy(buffer, "light gray");
			break;
		case RED:
			strcpy(buffer, "red");
			break;
		case LIGHT_RED:
			strcpy(buffer, "light red");
			break;
		case GREEN:
			strcpy(buffer, "green");
			break;
		case LIGHT_GREEN:
			strcpy(buffer, "light green");
			break;
		case BROWN:
			strcpy(buffer, "brown");
			break;
		case YELLOW:
			strcpy(buffer, "yellow");
			break;
		case BLUE:
			strcpy(buffer, "blue");
			break;
		case LIGHT_BLUE:
			strcpy(buffer, "light blue");
			break;
		case MAGENTA:
			strcpy(buffer, "magenta");
			break;
		case LIGHT_MAGENTA:
			strcpy(buffer, "light magenta");
			break;
		case CYAN:
			strcpy(buffer, "cyan");
			break;
		case LIGHT_CYAN:
			strcpy(buffer, "light cyan");
			break;
		case GRAY:
			strcpy(buffer, "gray");
			break;
		case WHITE:
			strcpy(buffer, "white");
			break;
		default:
			return -1;		
	}	
	return 0;
}

#endif
