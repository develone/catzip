#!/bin/bash 
#10485760	BLKRAM
#16777216	SDRAM
         COUNTER=2000
	ADDRESS=16777216
         until [  $COUNTER -lt 1 ]; do
             echo COUNTER $COUNTER
             let COUNTER-=1
	     let ADDRESS+=4
	     ./arm-wbregs 0x$ADDRESS 0x$COUNTER
         done
