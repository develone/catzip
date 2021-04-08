#!/bin/bash
./arm-wbregs 10485760 0x55
./arm-wbregs 10485764 0xaa
./arm-wbregs 10485768 0x01
./arm-wbregs 10485772 0x02
./arm-wbregs 10485776 0x00010000
./arm-wbregs 10485768 0x00020000
./arm-wbregs 10485760
./arm-wbregs 10485764
./arm-wbregs 10485768
./arm-wbregs 10485772
./arm-wbregs 10485776
./arm-wbregs 10485768
