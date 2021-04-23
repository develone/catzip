#!/bin/bash
./arm-wbregs 20971520 0x55
./arm-wbregs 20971524 0xaa
./arm-wbregs 20971528 0x01
./arm-wbregs 20971532 0x02
./arm-wbregs 20971536 0x00010000
./arm-wbregs 20971540 0x00020000
./arm-wbregs 20971520 
./arm-wbregs 20971524
./arm-wbregs 20971528 
./arm-wbregs 20971532
./arm-wbregs 20971536 
./arm-wbregs 20971540

echo '01400004 83 20 E2 0D'
./arm-wbregs 0x01400004 0x8320e20d

echo '01040008 75 14 22 0E'
./arm-wbregs 0x01400008 0x7514220e

echo '014002f4 6A 08 C2 0D'
./arm-wbregs 0x014002f4 0x6a08c20d

echo '014006f0 65 F0 F1 0D'
./arm-wbregs 0x014006f0 0x65f0f10d

echo '01400a70 5D 58 41 0B'
./arm-wbregs 0x01400a70 0x5d58410b

echo '00000100   5E 88 D1 0C' 
./arm-wbregs 0x01400100 0x6284010d

echo '00001000   67 00 02 0E' 
./arm-wbregs 0x01401000 0x6700020e

echo '000010F0   58 74 B1 0C' 
./arm-wbregs 0x014011f0 0x5874b10d


echo '000011Fc 61 8C D1 0C'
./arm-wbregs 0x014010fc 0x618cd10c

./arm-wbregs 0x01400004
./arm-wbregs 0x01400008
./arm-wbregs 0x014002f4
./arm-wbregs 0x014006f0
./arm-wbregs 0x01400a70
./arm-wbregs 0x01400100
./arm-wbregs 0x01401000
./arm-wbregs 0x014011f0
./arm-wbregs 0x014010fc
