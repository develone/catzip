#!/bin/bash
rm -f arm-sdramscope
g++ -g -Wall -I. -I../../rtl -c scopecls.cpp -o obj-arm/scopecls.o
g++ -g -Wall -I. -I../../rtl -c sdramscope.cpp -o obj-arm/sdramscope.o
g++ -g obj-arm/sdramscope.o obj-arm/scopecls.o obj-arm/hexbus.o obj-arm/llcomms.o obj-arm/regdefs.o obj-arm/byteswap.o -o arm-sdramscope
