#!/bin/bash
./arm-wbregs 16777216 0x55
./arm-wbregs 16777220 0xaa
./arm-wbregs 16777216
./arm-wbregs 16777220
