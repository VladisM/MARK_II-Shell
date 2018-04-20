# MARK-II Shell

Super simple shell for MARK-II system. To install it connect MARK-II Board with debug uart and call:

```
$ make load
```
then you can connect for example with picocom using:

```
$ picocom -b 4800 /dev/ttyUSB0
```

Try help command to see what commands are there.

If you want to run emulation, you will need tmux and cocat. But, you have to build another binary because emulator doesn't have all features like real board. Run this command:

```
$ make emul CFLAGS += -DDEBUG
```
