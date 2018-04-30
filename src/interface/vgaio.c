#include "vgaio.h"

#include <vga.h>

int vgaio_row = ROW_0;
int vgaio_column = COLUMN_0;
inline void vgaio_move_lines_up();

void vgaio_clear(){
    int x, y = 0;
    for(x = ROW_0; x <= ROW_29; x++){
        for(y = COLUMN_0; y <= COLUMN_79; y++){
            VRAM0(x,y) = 0x00 | FG_BLACK | BG_BLACK;
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
		VRAM0(vgaio_row, vgaio_column) = c | FG_WHITE | BG_BLACK;
		vgaio_column = vgaio_column + 1;
		VRAM0(vgaio_row, vgaio_column) = 0x20 | CURSOR | FG_WHITE | BG_BLACK;
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
        VRAM0(ROW_29,y) = 0x00 | FG_BLACK | BG_BLACK;
    }
}
