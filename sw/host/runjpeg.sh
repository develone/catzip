#!/bin/bash
./arm-wbregs 0x00A01000 0x2
./arm-wbregs 0x00A01004 0x1
./arm-zipload -v ../board/jpeg
./arm-wrsdram rgb_pack.bin
./arm-wbregs cpu 0x0f
sleep 25
rm -f dwt.bin
./arm-rdsdram dwt.bin

