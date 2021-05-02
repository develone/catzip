#!/bin/bash

echo "inpbuf"
./arm-wbregs 0x02002368
echo "altbuf"
./arm-wbregs 0x02042368
echo "w"
./arm-wbregs 0x02082368
echo "h"
./arm-wbregs 0x0208236c
echo "*red"
./arm-wbregs 0x02082370
echo "*grn"
./arm-wbregs 0x02082374
echo "*blu"
./arm-wbregs 0x02082378
echo "*alt"
./arm-wbregs 0x0208237c
echo "*ptr_blkram_flag"
./arm-wbregs 0x02082380

echo "*ptr_blkram_invfwd"
./arm-wbregs 0x02082364

echo "*buf_red"
./arm-wbregs 0x02082388
echo "ptr to fwd_inv"
./arm-wbregs 0x0208238c
echo "flag"
./arm-wbregs 0x02082390
 
echo "*inbuf"
./arm-wbregs 0x02082394

#./arm-wbregs 0x020823d0
