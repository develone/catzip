#!/bin/bash
rm -f *.blif *.asc *.bin *.json

yosys -l simple.log -p 'synth_ice40 -abc9 -blif speechpp.blif -json speechpp.json -top speechpp ' speechpp.v  ../pport/pport.v ../pport/ppio.v ../pport/ufifo.v ../pport/wbpport.v

yosys -l simple.log -p 'synth_ice40 -abc9 -blif hellopp.blif -json hellopp.json -top hellopp ' hellopp.v  ../pport/pport.v ../pport/ppio.v

yosys -l simple.log -p 'synth_ice40 -abc9 -blif linepp.blif -json linepp.json -top linepp ' linepp.v  ../pport/pport.v ../pport/ppio.v

nextpnr-ice40 --hx8k --pcf speechpp.pcf --json speechpp.json --asc speechpp.asc

nextpnr-ice40 --hx8k --pcf hellopp.pcf --json hellopp.json --asc hellopp.asc

nextpnr-ice40 --hx8k --pcf linepp.pcf --json linepp.json --asc linepp.asc

icepack speechpp.asc speechpp.bin

icepack hellopp.asc hellopp.bin

icepack linepp.asc linepp.bin

icetime -d hx8k -c 50 speechpp.asc

icetime -d hx8k -c 50 hellopp.asc

icetime -d hx8k -c 50 linepp.asc

rm -f *.blif *.asc  *.json


