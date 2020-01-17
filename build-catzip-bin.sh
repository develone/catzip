#/bin/bash

cd rtl/catzip

rm -f catzip.asc catzip.blif catzip.bin

yosys -l simple.log -p 'synth_ice40 -blif catzip.blif -json catzip.json -top toplevel' toplevel.v cpu/*.v wbubus/*.v ../pport/*.v wbsdram.v memdev.v ../hexbus/*.v wbscope.v main.v wbgpio.v
  
nextpnr-ice40 --seed 8 --freq 40 --hx8k --pcf catzip.pcf --json catzip.json --asc catzip.asc

icepack catzip.asc catzip.bin

cp catzip.bin ../../bin-files

echo "ckecking catzip " >  ../../build-catzip.log
icetime -d hx8k -c 40 catzip.asc
cd ../../
cat build-catzip.log

 
