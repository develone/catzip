## The catboard was created by Dave Vandenbout [XESS](http://www.xess.com/)
## This work would not be possible without the work of [ZIPCPU](https://github.com/ZipCPU]
## Dave is working on [ver 0.3](https://hackaday.io/project/7982-cat-board/log/145610-resurrection)
# Dan Gisselquist and his [Blog](https://zipcpu.com/)
# Clifford Wolfe [YOSYS Tools](https://github.com/cliffordwolf/icestorm)
# Chris Felton & Many others 
# Differece between [Catboard & ICOBoar](https://github.com/develone/catzip/blob/master/doc/zipcpu.pdf) 
# CATZIP status as of 11/20/18
# [Hardware Eight 7-segment LEDs ](http://www.xess.com/shop/product/stickit-leddigits/)
# [Pmod USB](https://www.digikey.com/products/en/development-boards-kits-programmers/evaluation-boards-expansion-boards-daughter-cards/797?k=Pmod%20USB#images)
# [PMOD OLEDrgb 98x64 Display](https://store.digilentinc.com/pmod-oledrgb-96-x-64-rgb-oled-display-with-16-bit-color-resolution/)
# [Catboard branch](https://github.com/develone/otl-icoboard-pmodoledrgb-demo/tree/catboard)
# [catboard OLED](https://photos.google.com/share/AF1QipM7ZcSN7J_qatKbRPyHkwrrLKjgE6Jp9yX76Mo92Ld-JZCW971uc5vPukQT4TGsWw?key=NWd0QjNmOTlOa05HTmUzSE4ycVNLMTVBYUZuSk5R)
# Requirements 
[learning_hdl](https://github.com/develone/learning_hdl)
# After building autofpga create a link in /usr/local/bin
# autofpga -> /home/pi/autofpga/sw/autofpga
# Current testing is being done on ver 0.1 catboard 
# This verison has issues with the spiflash.

# git clone https://github.com/develone/catzip.git
# cd catzip
# need to have verilator & zipcpu built
# set the PATH to where verilator & zipcpu with 
# . myenv.sh
# /home/pi/verilator
/home/pi/verilator/bin:/home/pi/zipcpu/sw/install/cross-tools/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/games:/usr/games
# make datestamp
# make autodata
# cd rtl/catzip
# make
# cd ../../sw/host
# make

# program to test the SDRAM
# gcc -g exe_wbregs.c -o exe_wbregs

# cd ../zib
# make
# cd ../board
# make
# cd ../../../sim/verilated
# make
# cd ../../sw/host

# Load the bin file in the FPGA
# sudo config_cat rtl/catzip/catzip.bin 

# in sw/host ./arm-netpport which provides the interface between the C programs and the FPGA
# Displays the date the bin file was created.
# ./arm-wbregs version
01000010 ( VERSION) : [....] 20181120
# Write SDRAM ./arm-wbregs 0x2001000  0x1000

# Read SDRAM ./arm-wbregs 0x2001000

# ICOZIP

ICO Zip is intended to be a demonstration repository, demonstrating how the
[ZipCPU](https://github.com/ZipCPU/zipcpu) may be placed onto an
[ICO board](http://www.icoboard.org).

Particular goals of this project include:
- Generate the main project files using [AutoFPGA](https://github.com/ZipCPU/autofpga)
- Demonstrate the ZipCPU running [tttt](https://github.com/ZipCPU/tttt), a 4x4x4 tic-tac-toe game

A unique feature of this project is that the
[Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-2-model-b/)
that will host the
[ICO board](http://icoboard.org) will only have a minor role in the project. 
My intention is to use the
[Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-2-model-b/)
only as a TCP/IP stack the provides access to 1) a command
port on the FPGA, 2) a serial port within the FPGA, and perhaps even 3) a means
of downloading new bit files to the FPGA.  If all goes well, then, one should
only need to run the [netpport](sw/host/netpport.cpp) program on the
[Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-2-model-b/),
and after that everything should be accessable through the TCP/IP port numbers
given in [port.h](sw/host/port.h).

This actually has a *very* profound consequence.  By allowing the user to have
access to the internals of the FPGA, peripheral development may be done and
verified prior to placing the CPU into the FPGA.  Hence, by the time the CPU
is placed on board, all the parts and pieces of the design will already be
known to work, leaving the only new variable that of the CPU itself.

## Status

This project is a work in progress.  It has a long way to go from "work in
progress" to a working system.  Still ... a lot has been done, a not all of it
is yet in the repository.  I chose to share this repository, even with the work
unfinished, so that I can share some of the very basic RTL tests I've done
and reference them on [my blog](http://zipcpu.com).

As of 20170526, the [basic](rtl/basic), [uart](rtl/uart), and
[pmodled](rtl/pmodleds) examples are fully functional.
While much work has taken place on the parallel port testing modules
(using sw/netpport)--they just aren't reliable enough (yet) to depend upon.

