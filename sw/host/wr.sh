#!/bin/bash
./arm-wbregs 16777216 0x55
./arm-wbregs 16777220 0xaa
./arm-wbregs 16777224 0x01
./arm-wbregs 16777228 0x02
./arm-wbregs 16777232 0x00010000
./arm-wbregs 16777236 0x00020000
./arm-wbregs 16777216
./arm-wbregs 16777220
./arm-wbregs 16777224
./arm-wbregs 16777228
./arm-wbregs 16777232
./arm-wbregs 16777236
