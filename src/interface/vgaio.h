#ifndef DEBUG
#ifndef VGAIO_H_included
#define VGAIO_H_included

#define BLACK 			0x0
#define LIGHT_GRAY 		0x1
#define RED 			0x2
#define LIGHT_RED 		0x3
#define GREEN 			0x4
#define LIGHT_GREEN 	0x5
#define BROWN 			0x6
#define YELLOW 			0x7
#define BLUE 			0x8
#define LIGHT_BLUE 		0x9
#define MAGENTA 		0xA
#define LIGHT_MAGENTA 	0xB
#define CYAN 			0xC
#define LIGHT_CYAN 		0xD
#define GRAY 			0xE
#define WHITE 			0xF

extern int vgaio_fg_color;
extern int vgaio_bg_color;

void vgaio_clear();
void vgaio_home();
void vgaio_write_msg(char *c);
void vgaio_putc(char c);
void vgaio_set_color(int fg_col, int bg_col);
void vgaio_init();

#endif
#endif
