#!/bin/bash
rm -rf obj-arm/sdramscope.o obj-arm/zipload.o obj-arm/zipdbg.o obj-arm/zipstate.o obj-arm/zopcodes.o obj-arm/twoc.o obj-arm/zipelf.o obj-arm/rdsdram..o
rm -f arm-zipdbg arm-zipload arm-zipstate arm-rdsdram
g++ -g -Wall -I. -I../../rtl -c scopecls.cpp -o obj-arm/scopecls.o
g++ -g -Wall -I. -I../../rtl -c sdramscope.cpp -o obj-arm/sdramscope.o
g++ -g -Wall -I. -I../../rtl -I../../rtl/catzip -c zipload.cpp -o obj-arm/zipload.o
g++ -g -Wall -I. -I../../rtl -I../../rtl/catzip -c zipdbg.cpp -o obj-arm/zipdbg.o
g++ -g -Wall -I. -I../../rtl -I../../rtl/catzip -c zipstate.cpp -o obj-arm/zipstate.o
g++ -g -Wall -I. -I../../rtl -I../../rtl/catzip -c zopcodes.cpp -o obj-arm/zopcodes.o
g++ -g -Wall -I. -I../../rtl -I../../rtl/catzip -c twoc.cpp -o obj-arm/twoc.o
g++ -g -Wall -I. -I../../rtl -I../../rtl/catzip -c zipelf.cpp -o obj-arm/zipelf.o
g++ -g -Wall -I. -I../../rtl -I../../rtl/catzip -c rdsdram.cpp -o obj-arm/rdsdram.o
g++ -g -Wall -I. -I../../rtl -I../../rtl/catzip -c wrsdram.cpp -o obj-arm/wrsdram.o
g++ -g obj-arm/sdramscope.o obj-arm/scopecls.o obj-arm/hexbus.o obj-arm/llcomms.o obj-arm/regdefs.o obj-arm/byteswap.o -o arm-sdramscope
g++ -g obj-arm/zipdbg.o obj-arm/hexbus.o obj-arm/llcomms.o obj-arm/regdefs.o obj-arm/byteswap.o obj-arm/zopcodes.o obj-arm/twoc.o -lcurses -o arm-zipdbg
g++ -g obj-arm/zipstate.o obj-arm/hexbus.o obj-arm/llcomms.o obj-arm/regdefs.o obj-arm/byteswap.o -o arm-zipstate
g++ -g obj-arm/hexbus.o obj-arm/llcomms.o obj-arm/regdefs.o obj-arm/byteswap.o obj-arm/zipelf.o obj-arm/zipload.o -lelf -o arm-zipload
g++ -g obj-arm/hexbus.o obj-arm/llcomms.o obj-arm/regdefs.o obj-arm/byteswap.o obj-arm/zipelf.o obj-arm/rdsdram.o -lelf -o arm-rdsdram
g++ -g obj-arm/hexbus.o obj-arm/llcomms.o obj-arm/regdefs.o obj-arm/byteswap.o obj-arm/zipelf.o obj-arm/wrsdram.o -lelf -o arm-wrsdram
