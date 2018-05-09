#ifndef DEBUG

#include "vgaio.h"

#include <vga.h>

#define FG_POS 7
#define BG_POS 11

int vgaio_row;
int vgaio_column;

inline void vgaio_move_lines_up();
void set_color(int fg_col, int bg_col);

	
void vgaio_clear(){
    int x, y = 0;
    for(x = ROW_0; x <= ROW_29; x++){
        for(y = COLUMN_0; y <= COLUMN_79; y++){
            VRAM0(x,y) = 0x00 | (vgaio_bg_color << FG_POS) | (vgaio_bg_color << BG_POS);
        }
    }
    vgaio_home();
}

void vgaio_home(){
    vgaio_row = ROW_0;
    vgaio_column = COLUMN_0;
}

void vgaio_putc(char c){
	VRAM0(vgaio_row, vgaio_column) &= ~(CURSOR);
	if (c == '\n'){
		if (vgaio_row < ROW_29) {
			vgaio_row = vgaio_row + 1;
			vgaio_column = COLUMN_0;
		}
		else{
			vgaio_move_lines_up();
			vgaio_row = ROW_29;
			vgaio_column = COLUMN_0;
		}
		VRAM0(vgaio_row, vgaio_column) |= CURSOR;
	}
	else if (c == '\r'){
		vgaio_column = COLUMN_0;
		VRAM0(vgaio_row, vgaio_column) |= CURSOR;
	}
	else if (c == 0x08){ //backspace
		vgaio_column = vgaio_column - 1;
		VRAM0(vgaio_row, vgaio_column) |= CURSOR;
	}
	else{
		VRAM0(vgaio_row, vgaio_column) = c | (vgaio_fg_color << FG_POS) | (vgaio_bg_color << BG_POS);
		vgaio_column = vgaio_column + 1;
		VRAM0(vgaio_row, vgaio_column) = 0x20 | CURSOR | (vgaio_fg_color << FG_POS) | (vgaio_bg_color << BG_POS);
	}	
} 

void vgaio_write_msg(char *c){
    for(int i = 0; c[i] != 0; i++){
        vgaio_putc(c[i]);
    }
}

inline void vgaio_move_lines_up(){
    int x, y = 0;
    for(x = ROW_1; x <= ROW_29; x++){
        for(y = COLUMN_0; y <= COLUMN_79; y++){
            VRAM0(x-1,y) = VRAM0(x, y);
        }
    }
    for(y = COLUMN_0; y <= COLUMN_79; y++){
        VRAM0(ROW_29,y) = 0x00 | (vgaio_bg_color << FG_POS) | (vgaio_bg_color << BG_POS);
    }
}

void vgaio_set_color(int fg_col, int bg_col){
	vgaio_fg_color = fg_col;
	vgaio_bg_color = bg_col;		
}

void vgaio_init(){
	vgaio_fg_color = WHITE;
	vgaio_bg_color = BLACK;
	vgaio_row = ROW_0;
	vgaio_column = COLUMN_0;
}

#endif
