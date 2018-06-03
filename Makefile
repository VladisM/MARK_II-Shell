####
# for emulation please use:
#   $ make emul CFLAGS += -DDEBUG -e
#
# if you want put ldm into board you can use directly:
#   $ make load
####

PRG = shell

# library paths
SPL = $(HOME)/m2_toolchain/spl
BSP = $(HOME)/m2_toolchain/bsp
STDLIBC = $(HOME)/m2_toolchain/stdlibc

# flags
override CFLAGS += -I$(SPL) -I$(BSP) -quiet -c99 
LDFLAGS = -l $(BSP)/lib $(STDLIBC)/__startup.o

# define tools
CC = m2-vbcc
LK = m2-linker
AS = m2-assembler
LD = m2-loader

# export variables
export CC AS CFLAGS

all: build/$(PRG).ldm

build/$(PRG).ldm: dirs cmds interface libs shell build/main.o 
	$(LK) -o build/$(PRG).ldm $(LDFLAGS) $(shell find build -name '*.o')

build/main.o: src/main.c src/shell/loop.h
	$(CC) $(CFLAGS) -o=$(@:.o=.asm) $<
	$(AS) -o $@ $(@:.o=.asm)

# create directories
dirs:
	mkdir -p build
	mkdir -p build/cmds
	mkdir -p build/interface
	mkdir -p build/libs
	mkdir -p build/shell
	
# compile all parts
cmds:
	$(MAKE) -C src/cmds

interface:
	$(MAKE) -C src/interface

libs:
	$(MAKE) -C src/libs

shell:
	$(MAKE) -C src/shell
	

.PHONY: clean emul load

clean:
	rm -rf build fast_load*
	
emul: build/$(PRG).ldm
	cd sim; sh start.sh

load: build/$(PRG).ldm
	m2-loader -b 0x800000 -p /dev/ttyUSB0 build/$(PRG).ldm
	
fastload: build/$(PRG).ldm
	m2-loader -b 0x800000 -p /dev/null --fileout build/$(PRG).ldm
	gcc -o fast_load fast_load.c
	./fast_load
