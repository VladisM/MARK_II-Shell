#include "cmds.h"
#include "../libs/return_codes.h"
#include "../libs/string.h"
#include "../interface/io.h"

#ifndef DEBUG
#include "../interface/vgaio.h"

static int echo_color();
static int convert_to_code(char *name);
static int convert_to_name(int code, char *buffer);
inline void list_color_names();
#endif

int color(int argc, char *argv[]){    
#ifndef DEBUG
    if(argc == 1){
        return echo_color();
    }
    else if(argc == 2){
		if(strcmp(argv[1], "list")){
			list_color_names();
			return RET_OK;
		}
		else{
			int fg_col = convert_to_code(argv[1]);
			if(fg_col > 0){
				vgaio_set_color(fg_col, vgaio_bg_color);
				return RET_OK;
			}
			else{
				return RET_NOT_VALID_ARG;
			}
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
    send_string(" > color <colF> <colB>    set foregroud to colF and backgroud to colB\n\r");
    send_string(" > color list             list all color codes\n\n\r");
}

#ifndef DEBUG
static int echo_color(){
    static char col_name[16];
    
    if(convert_to_name(vgaio_fg_color, col_name) < 0){
        return RET_GENERIC_ERROR;
    }
    
    send_string("You are using ");
    send_string(col_name);
    send_string(" on ");
    
    if(convert_to_name(vgaio_bg_color, col_name) < 0){
        return RET_GENERIC_ERROR;
    }
    
    send_string(col_name);
    send_string(".\n\r");
    return RET_OK;
}


static int convert_to_code(char *name){
    if     (strcmp(name, "black"))     return BLACK;
    else if(strcmp(name, "lgray"))     return LIGHT_GRAY;
    else if(strcmp(name, "red"))       return RED;
    else if(strcmp(name, "lred"))      return LIGHT_RED;
    else if(strcmp(name, "green"))     return GREEN;
    else if(strcmp(name, "lgreen"))    return LIGHT_GREEN;
    else if(strcmp(name, "brown"))     return BROWN;
    else if(strcmp(name, "yellow"))    return YELLOW;
    else if(strcmp(name, "blue"))      return BLUE;
    else if(strcmp(name, "lblue"))     return LIGHT_BLUE;
    else if(strcmp(name, "magenta"))   return MAGENTA;
    else if(strcmp(name, "lmagenta"))  return LIGHT_MAGENTA;
    else if(strcmp(name, "cyan"))      return CYAN;
    else if(strcmp(name, "lcyan"))     return LIGHT_CYAN;
    else if(strcmp(name, "gray"))      return GRAY;
    else if(strcmp(name, "white"))     return WHITE;
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

inline void list_color_names(){
	send_string("Available color names are: \n\r");
	send_string(" 'black'\n\r");   
	send_string(" 'lgray'\n\r");   
	send_string(" 'red'\n\r");     
	send_string(" 'lred'\n\r");    
	send_string(" 'green'\n\r");   
	send_string(" 'lgreen'\n\r");  
	send_string(" 'brown'\n\r");   
	send_string(" 'yellow'\n\r");  
	send_string(" 'blue'\n\r");    
	send_string(" 'lblue'\n\r");   
	send_string(" 'magenta'\n\r"); 
	send_string(" 'lmagenta'\n\r");
	send_string(" 'cyan'\n\r");    
	send_string(" 'lcyan'\n\r");   
	send_string(" 'gray'\n\r");     
	send_string(" 'white'\n\r");    
	send_string("\nNote that l prefix mean light.\n\r");
}

#endif
