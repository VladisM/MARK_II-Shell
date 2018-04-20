#!/bin/bash

tmux new -s emul -d
tmux split-window -h -t emul
tmux split-window -v -t emul:0.1

tmux send-keys -t emul:0.2 'socat -d -d PTY,link=dev/pts0,raw,echo=0 PTY,link=dev/pts1,raw,echo=0' C-m
sleep 1
echo "starting socat..."

tmux send-keys -t emul:0.1 'm2-emulator -p dev/pts0 -r loader.mif' C-m
sleep 1
echo "starting emulator..."

echo "bring you into tmux... now!"
tmux send-keys -t emul:0.0 'm2-loader -e -b 0x100000 -p dev/pts1 ../build/shell.ldm;picocom -b 4800 dev/pts1;tmux kill-session -t emul' C-m

tmux a -t emul:0.0
