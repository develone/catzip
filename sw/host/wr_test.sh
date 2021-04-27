#!/bin/bash 
#10485760	BLKRAM
#16777216	SDRAM
         COUNTER=8192
	ADDRESS=20971520
         until [  $COUNTER -lt 1 ]; do
             echo COUNTER $COUNTER
             let COUNTER-=1
	     let ADDRESS+=4
	     ./arm-wbregs $ADDRESS 0x$COUNTER
         done
