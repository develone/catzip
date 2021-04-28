#!/bin/bash
./arm-wbregs 0x01401000 0x2
./arm-wbregs 0x01401004 0x1
./arm-zipload -v ../board/jpeg
./arm-wrsdram rgb_pack.bin
./arm-zipdbg
