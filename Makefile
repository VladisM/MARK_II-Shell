####
# for emulation use:
#   $ make CFLAGS += -DDEBUG
# or:
#   $ make emul CFLAGS += -DDEBUG
#
#
# if you want put ldm into board you can use directly:
#   $ make
# or
#	$ make load
#
####

PRG = shell

# library paths
SPL = $(HOME)/m2_toolchain/spl
STDLIBC = $(HOME)/m2_toolchain/stdlibc

# flags
override CFLAGS += -I$(SPL) -quiet -c99 
LDFLAGS = -l $(SPL)/lib $(STDLIBC)/__startup.o

# define tools
CC = m2-vbcc
LK = m2-linker
AS = m2-assembler
LD = m2-loader

OBJS = main.o io.o loop.o string.o
OBJS += ping.o help.o beep.o poweroff.o

all: build/$(PRG).ldm

build/$(PRG).ldm: $(addprefix build/, $(OBJS))
	$(LK) -o build/$(PRG).ldm $(LDFLAGS) $(addprefix build/, $(OBJS))

build/main.o: src/main.c src/loop.h
	$(CC) $(CFLAGS) -o=build/main.asm src/main.c
	$(AS) -o build/main.o build/main.asm
	
build/io.o: src/io.c src/io.h
	$(CC) $(CFLAGS) -o=build/io.asm src/io.c
	$(AS) -o build/io.o build/io.asm

build/loop.o: src/loop.c src/loop.h src/io.h src/string.h src/cmds.h src/return_codes.h
	$(CC) $(CFLAGS) -o=build/loop.asm src/loop.c
	$(AS) -o build/loop.o build/loop.asm

build/ping.o: src/ping.c src/cmds.h src/return_codes.h src/io.h
	$(CC) $(CFLAGS) -o=build/ping.asm src/ping.c
	$(AS) -o build/ping.o build/ping.asm

build/help.o: src/help.c src/cmds.h src/return_codes.h src/string.h src/io.h
	$(CC) $(CFLAGS) -o=build/help.asm src/help.c
	$(AS) -o build/help.o build/help.asm

build/string.o: src/string.c src/string.h
	$(CC) $(CFLAGS) -o=build/string.asm src/string.c
	$(AS) -o build/string.o build/string.asm

build/beep.o: src/beep.c src/cmds.h src/return_codes.h src/io.h
	$(CC) $(CFLAGS) -o=build/beep.asm src/beep.c
	$(AS) -o build/beep.o build/beep.asm

build/poweroff.o: src/poweroff.c src/cmds.h src/return_codes.h src/io.h
	$(CC) $(CFLAGS) -o=build/poweroff.asm src/poweroff.c
	$(AS) -o build/poweroff.o build/poweroff.asm

.PHONY: clean emul load set_debug

clean:
	rm -rf build/*
	
emul: build/$(PRG).ldm
	cd sim; sh start.sh

load: build/$(PRG).ldm
	m2-loader -b 0x800000 -p /dev/ttyUSB0 build/$(PRG).ldm

