SRCS = $(shell find -name '*.c' | sed -e 's,^\./,,')
OBJS = $(addprefix ../../build/libs/,$(SRCS:.c=.o))

all: $(OBJS)

../../build/libs/string.o: string.c string.h
	$(CC) $(CFLAGS) -o=$(@:.o=.asm) $<
	$(AS) -o $@ $(@:.o=.asm)
