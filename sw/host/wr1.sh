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

