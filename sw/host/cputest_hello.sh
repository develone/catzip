#!/bin/bash
./arm-zipload -p 8363 -n mypi3-1 -v ../board/cputest
./arm-wbregs -p 8363 -n mypi3-1 cpu 0x0f
sleep 30
./arm-zipload -p 8363 -n mypi3-1 -v ../board/hello
./arm-wbregs -p 8363 -n mypi3-1 cpu 0x0f

 
