#!/bin/bash


echo "The date built"
./pc-wbregs -n mypi3-1  version
#sleep 2
./pc-wbregs -n mypi3-1  0x1000000 0x10000001
#sleep 2 
./pc-wbregs -n mypi3-1  0x1000004 0x10000002
#sleep 2
./pc-wbregs -n mypi3-1  0x1000008 0x10000003
#sleep 2
./pc-wbregs -n mypi3-1  0x100000c 0x10000004
#sleep 2
./pc-wbregs -n mypi3-1  0x1000000 0x10000001
#sleep 2 
./pc-wbregs -n mypi3-1  0x1000004 0x10000002
#sleep 2
./pc-wbregs -n mypi3-1  0x1000008 0x10000003
#sleep 2
./pc-wbregs -n mypi3-1  0x100000c 0x10000004
#sleep 2
./pc-wbregs -n mypi3-1  0x1000000 
#sleep 2
./pc-wbregs -n mypi3-1  0x1000004 
#sleep 2
./pc-wbregs -n mypi3-1  0x1000008 
#sleep 2
./pc-wbregs -n mypi3-1  0x100000c
#sleep 2 
./pc-wbregs -n mypi3-1  0x1000000 
#sleep 2 
./pc-wbregs -n mypi3-1  0x1000004 
#sleep 2
./pc-wbregs -n mypi3-1  0x1000008 
#sleep 2
./pc-wbregs -n mypi3-1  0x100000c
#sleep 2
echo "Turning on the 4th led "
./pc-wbregs -n mypi3-1  gpio 0x00010001
sleep 2 
echo "Turning on the 1st led "
./pc-wbregs -n mypi3-1  gpio 0x00020002
sleep 2 
echo "Turning on the 2nd led "
./pc-wbregs -n mypi3-1  gpio 0x00040004
sleep 5
echo "Turning off the leds "
./pc-wbregs -n mypi3-1  gpio 0x00070000
