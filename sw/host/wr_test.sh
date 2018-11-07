#!/bin/bash 
         COUNTER=2000
	ADDRESS=33554428
         until [  $COUNTER -lt 1 ]; do
             echo COUNTER $COUNTER
             let COUNTER-=1
	     let ADDRESS+=4
	     ./arm-wbregs 0x$ADDRESS 0x$COUNTER
         done
