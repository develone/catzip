#!/bin/bash
rm -f arm-sdramscope arm-zipload
g++ -g -Wall -I. -I../../rtl -c scopecls.cpp -o obj-arm/scopecls.o
g++ -g -Wall -I. -I../../rtl -c sdramscope.cpp -o obj-arm/sdramscope.o
g++ -g -Wall -I. -I../../rtl -c zipload.cpp -o obj-arm/zipload.o
g++ -g obj-arm/sdramscope.o obj-arm/scopecls.o obj-arm/hexbus.o obj-arm/llcomms.o obj-arm/regdefs.o obj-arm/byteswap.o -o arm-sdramscope
