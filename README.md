## The catboard was created by Dave Vandenbout [XESS](http://www.xess.com/)
## Dave is working on [ver 0.3](https://hackaday.io/project/7982-cat-board/log/145610-resurrection)
## This work would not be possible without the work of [ZIPCPU](https://github.com/ZipCPU)
# Dan Gisselquist and his [Blog](https://zipcpu.com/)
# Clifford Wolfe [YOSYS Tools](https://github.com/cliffordwolf/icestorm)
# Chris Felton & Many others 
# Both the icozip on ICOBoard & catzip on CatBoard based HX8K ice40 FPGA 
# provide a complete development system on the Raspberry Pi  
# Both icozip & catzip provide a verilated simulation which allows one to 
# test some of the features of the project.

# The Goal currently is to get two C programs running on the CatBoard running with the ZipCPU.
# This requires compiling several catzip/sw/host programs
# arm-zipload, arm-zipstate, and arm-zipdbg that will load the binary code into the Sdram and execute.  
# This also requires the compiling & linking the of cputest.c & hello.c
# [cputest.c](https://github.com/develone/catzip/blob/master/sw/board/cputest.c)
# [hello.c](https://github.com/develone/catzip/blob/master/sw/board/hello.c)
# [boardram.ld](https://github.com/develone/catzip/blob/master/sw/board/boardram.ld)
# The cputest.c & hello.c also require creating libicozip.a or libcatzip.a
# The libraries libicozip.a or libcatzip.a are made up of serveral C files.
# crt0.c, syscalls.c, umod.c, and udiv.c
# For the icozip need to modify sw/host/port.h 
# -// #define     FPGAHOST        "localhost"
# -#define        FPGAHOST        "rpi"
# +#define        FPGAHOST        "localhost"
# +//#define      FPGAHOST        "rpi"

# pi@mypi3-1:~/testbuilds/icozip/sim/verilated $ ./arm-main_tb start the simulator 
# Only if running on icoboard pi@mypi3-1:~/testbuilds/icozip/sw/host $ ./arm-netpport listen for C commands
# pi@mypi3-1:~/testbuilds/icozip/sw/host $ ./arm-zipload ../board/hello
# Or pi@mypi3-1:~/testbuilds/icozip/sw/host $ ./arm-zipload ../board/cputest
# Halting the CPU
# Loading: ../board/cputest
# CPU Status is: 0000060f
# pi@mypi3-1:~/testbuilds/icozip/sw/host $ ./arm-wbregs cpu 0x0f
# Running CPU self-test
# -----------------------------------
# SIM Instructions                Is this a simulator?
# CIS Instructions                Supported
# Break test #1                   Pass
# Break test #2                   Pass
# Break test #3                   Pass
# Early Branch test               Pass
# Trap test/AND                   Pass
# Trap test/CLR                   Pass
# Overflow test                   Pass
# Carry test                      Pass
# Loop test                       Pass
# Shift test                      Pass
# Pipeline test                   Pass
# Mem-Pipeline test               Pass
# Conditional Execution test      Pass
# No-waiting pipeline test        Pass
# Conditional Branching test      Pass
# Ill Instruction test, NULL PC   Pass
# Ill Instruction test, two       Pass
# Comparison test, ==             Pass
# Comparison test, !=             Pass
# CC Register test                Pass
# Multi-Arg test                  Pass
# Multiply test                   No Multiply Implemented
# Divide test                     No divide unit installed
# 
# -----------------------------------
# All tests passed.  Halting CPU.
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
# make  This create the catzip.bin that will be used to program the HX8K ice40 FPGA
# cd ../../sw/host
# make

# program to test the SDRAM
# gcc -g exe_wbregs.c -o exe_wbregs

# cd ../zib
# make
# should have libcatzip.a
# cd ../board
# make
# should have executeables cputest & hello that will run out sdram
# Since the more bkram was in the icozip design hello.c was running out of bkram.
# cd ../../../sim/verilated
# make which creates the program arm-main_tb
# The program arm-main_tb provides the functions that FPGA using arm-netpport
# 
# cd ../../sw/host
# make arm-netpport & arm-wbregs
# The programs config_cat & reset_cat should be linked in /usr/local/bin
# /usr/local/bin/reset_cat -> /home/pi/catboard_yosys/reset_cat
# /usr/local/bin/config_cat -> /home/pi/catboard_yosys/config_cat
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

