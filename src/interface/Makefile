SRCS = $(shell find -name '*.c' | sed -e 's,^\./,,')
OBJS = $(addprefix ../../build/interface/,$(SRCS:.c=.o))

all: $(OBJS)

../../build/interface/io.o: io.c io.h 
	$(CC) $(CFLAGS) -o=$(@:.o=.asm) $<
	$(AS) -o $@ $(@:.o=.asm)
