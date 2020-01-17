#!/bin/bash
mkdir bin-files
   
cd rtl/basic
rm -rf ../../bin-files/*
rm -f *.asc *.blif *.bin 
yosys -l simple.log -p 'synth_ice40 -blif blinky.blif -json blinky.json -top blinky' blinky.v
nextpnr-ice40 --seed 8 --freq 100 --hx8k --pcf blinky.pcf --json blinky.json --asc blinky.asc
icepack blinky.asc blinky.bin
cp blinky.bin ../../bin-files
echo "checking blinky " > ../build.log
icetime -d hx8k -c 100 blinky.asc >> ../build.log

yosys -l simple.log -p 'synth_ice40 -blif dimmer.blif -json dimmer.json -top dimmer' dimmer.v
nextpnr-ice40 --seed 8 --freq 100 --hx8k --pcf dimmer.pcf --json dimmer.json --asc dimmer.asc
icepack dimmer.asc dimmer.bin
cp dimmer.bin ../../bin-files 
echo "checking dimmer " >> ../build.log
icetime -d hx8k -c 100 dimmer.asc >> ../build.log
 
yosys -l simple.log -p 'synth_ice40 -blif clktest.blif -json clktest.json -top clktest' clktest.v
nextpnr-ice40 --seed 8 --freq 100 --hx8k --pcf clktest.pcf --json clktest.json --asc clktest.asc
icepack clktest.asc clktest.bin
cp clktest.bin ../../bin-files
echo "checking clktest " >> ../build.log
icetime -d hx8k -c 100 clktest.asc >> ../build.log

cd ../leddigits

rm -f *.asc *.blif *.bin
yosys -l simple.log -p 'synth_ice40 -blif leddigits.blif -json leddigits.json -top catboard' leddigits.v
nextpnr-ice40 --seed 8 --freq 100 --hx8k --pcf leddigits.pcf --json leddigits.json --asc leddigits.asc
icepack leddigits.asc leddigits.bin
cp leddigits.bin ../../bin-files
echo "checking leddigits " >> ../build.log
icetime -d hx8k -c 100 leddigits.asc  >> ../build.log

cd ../switch_leds

rm -f *.asc *.blif *.bin
yosys -l simple.log -p 'synth_ice40 -blif switch_leds.blif -json switch_leds.json -top buttons_display' switch_leds.v
nextpnr-ice40 --seed 8 --freq 100 --hx8k --pcf switch_leds.pcf --json switch_leds.json --asc switch_leds.asc
icepack switch_leds.asc switch_leds.bin
cp switch_leds.bin ../../bin-files
echo "checking switch_leds" >> ../build.log
icetime -d hx8k -c 100 switch_leds.asc   >> ../build.log

cd ../
find ../bin-files -name *.bin >> build.log
md5sum ../bin-files/* >> build.log
less build.log
cd ../
