#!/bin/bash


echo "The date built"
./arm-wbregs version
#sleep 2
./arm-wbregs 0x0400000 0x10000001
#sleep 2 
./arm-wbregs 0x0400004 0x10000002
#sleep 2
./arm-wbregs 0x0400008 0x10000003
#sleep 2
./arm-wbregs 0x040000c 0x10000004
#sleep 2
./arm-wbregs 0x0400000 0x10000001
#sleep 2 
./arm-wbregs 0x0400004 0x10000002
#sleep 2
./arm-wbregs 0x0400008 0x10000003
#sleep 2
./arm-wbregs 0x040000c 0x10000004
#sleep 2
./arm-wbregs 0x0400000 
#sleep 2
./arm-wbregs 0x0400004 
#sleep 2
./arm-wbregs 0x0400008 
#sleep 2
./arm-wbregs 0x040000c
#sleep 2 
./arm-wbregs 0x0400000 
#sleep 2 
./arm-wbregs 0x0400004 
#sleep 2
./arm-wbregs 0x0400008 
#sleep 2
./arm-wbregs 0x040000c
#sleep 2
./arm-wbregs 0x0800000 0x10000001
#sleep 2 
./arm-wbregs 0x0800004 0x10000002
#sleep 2
./arm-wbregs 0x0800008 0x10000003
#sleep 2
./arm-wbregs 0x080000c 0x10000004
#sleep 2
./arm-wbregs 0x0800000 0x10000001
#sleep 2 
./arm-wbregs 0x0800004 0x10000002
#sleep 2
./arm-wbregs 0x0800008 0x10000003
#sleep 2
./arm-wbregs 0x080000c 0x10000004
#sleep 2
./arm-wbregs 0x0800000 
#sleep 2
./arm-wbregs 0x0800004 
#sleep 2
./arm-wbregs 0x0800008 
#sleep 2
./arm-wbregs 0x080000c
#sleep 2 
./arm-wbregs 0x0800000 
#sleep 2 
./arm-wbregs 0x0800004 
#sleep 2
./arm-wbregs 0x0800008 
#sleep 2
./arm-wbregs 0x080000c
#sleep 2
echo "Turning on the 4th led "
./arm-wbregs gpio 0x00010001
sleep 2 
echo "Turning on the 1st led "
./arm-wbregs gpio 0x00020002
sleep 2 
echo "Turning on the 2nd led "
./arm-wbregs gpio 0x00040004
sleep 5
echo "Turning off the leds "
./arm-wbregs gpio 0x00070000
