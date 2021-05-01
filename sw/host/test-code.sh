#!/bin/bash
#w
./arm-wbregs 0x02004d74
#h
./arm-wbregs 0x02004d78
#*red
./arm-wbregs 0x02004d7c

#*ptr_blkram_flag; 
./arm-wbregs 0x02004d8c
#*ptr_blkram_invfwd
./arm-wbregs 0x02004d90
#buf_red
./arm-wbregs 0x02004d94
#*fwd_inv
./arm-wbregs 0x02004d98
#flag
./arm-wbregs 0x02004d9c
#inpbuf
./arm-wbregs 0x02004da0
