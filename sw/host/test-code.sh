#!/bin/bash
#w
./arm-wbregs 0x020022e8
#h
./arm-wbregs 0x020022ec
#*red
./arm-wbregs 0x020022f0
#alt
./arm-wbregs 0x020022fc
#*ptr_blkram_flag; 
./arm-wbregs 0x02002300
#*ptr_blkram_invfwd
./arm-wbregs 0x02002304
#buf_red
./arm-wbregs 0x02002308
#*fwd_inv
./arm-wbregs 0x0200230c
#flag
./arm-wbregs 0x02002310
#inpbuf
./arm-wbregs 0x02002314
