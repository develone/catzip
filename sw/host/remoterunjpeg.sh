#!/bin/bash

./pc-wbregs -p 8363 -n mypi3-1 0x00A01000 0x2
./pc-wbregs -p 8363 -n mypi3-1 0x00A01004 0x1
./pc-zipload -p 8363 -n mypi3-1 -v ../board/jpeg
./pc-wrsdram -p 8363 -n mypi3-1 rgb_pack.bin
./pc-wbregs -p 8363 -n mypi3-1 cpu 0x0f
sleep 25
rm -f dwt.bin
./pc-rdsdram -p 8363 -n mypi3-1 dwt.bin

