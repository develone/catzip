#!/bin/bash
./arm-zipload -p 8363 -n mypi3-1 -v ../board/jpeg
./arm-wrsdram -p 8363 -n mypi3-1 rgb_pack.bin
./arm-wbregs -p 8363 -n mypi3-1 cpu 0x0f
#sleep 30
#./arm-rdsdram -p 8363 -n mypi3-1 dwt.bin
