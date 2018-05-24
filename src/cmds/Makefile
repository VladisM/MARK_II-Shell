SRCS = $(shell find -name '*.c' | sed -e 's,^\./,,')
OBJS = $(addprefix ../../build/cmds/,$(SRCS:.c=.o))

all: $(OBJS)

../../build/cmds/beep.o: beep.c cmds.h ../libs/return_codes.h ../interface/io.h
	$(CC) $(CFLAGS) -o=$(@:.o=.asm) $<
	$(AS) -o $@ $(@:.o=.asm)

../../build/cmds/poweroff.o: poweroff.c cmds.h ../libs/return_codes.h ../interface/io.h
	$(CC) $(CFLAGS) -o=$(@:.o=.asm) $<
	$(AS) -o $@ $(@:.o=.asm)
	
../../build/cmds/ping.o: ping.c cmds.h ../libs/return_codes.h ../interface/io.h
	$(CC) $(CFLAGS) -o=$(@:.o=.asm) $<
	$(AS) -o $@ $(@:.o=.asm)

../../build/cmds/game.o: game.c cmds.h ../libs/return_codes.h ../interface/io.h
	$(CC) $(CFLAGS) -o=$(@:.o=.asm) $<
	$(AS) -o $@ $(@:.o=.asm)

../../build/cmds/help.o: help.c cmds.h ../libs/return_codes.h ../libs/string.h ../interface/io.h
	$(CC) $(CFLAGS) -o=$(@:.o=.asm) $<
	$(AS) -o $@ $(@:.o=.asm)

../../build/cmds/color.o: color.c cmds.h ../libs/return_codes.h ../libs/string.h ../interface/io.h ../interface/vgaio.h
	$(CC) $(CFLAGS) -o=$(@:.o=.asm) $<
	$(AS) -o $@ $(@:.o=.asm)
