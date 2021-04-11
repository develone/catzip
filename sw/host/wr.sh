#!/bin/bash
./arm-wbregs 33554432 0x55
./arm-wbregs 33554436 0xaa
./arm-wbregs 33554440 0x01
./arm-wbregs 33554444 0x02
./arm-wbregs 33554448 0x00010000
./arm-wbregs 33554452 0x00020000
./arm-wbregs 33554432
./arm-wbregs 33554436
./arm-wbregs 33554440
./arm-wbregs 33554444
./arm-wbregs 33554448
./arm-wbregs 33554452

