SRCS = $(shell find -name '*.c' | sed -e 's,^\./,,')
OBJS = $(addprefix ../../build/shell/,$(SRCS:.c=.o))

all: $(OBJS)

../../build/shell/loop.o: loop.c loop.h ../interface/io.h ../libs/string.h ../cmds/cmds.h ../libs/return_codes.h
	$(CC) $(CFLAGS) -o=$(@:.o=.asm) $<
	$(AS) -o $@ $(@:.o=.asm)
