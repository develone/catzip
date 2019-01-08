## The catboard was created by Dave Vandenbout [XESS](http://www.xess.com/)
## Dave is working on [ver 0.3](https://hackaday.io/project/7982-cat-board/log/145610-resurrection)
# The ver0.3 will provide an hdmi.  
## This work would not be possible without the work of [ZIPCPU](https://github.com/ZipCPU)
# Dan Gisselquist and his [Blog](https://zipcpu.com/)
# Clifford Wolfe [YOSYS Tools](https://github.com/cliffordwolf/icestorm)
# Chris Felton & Many others 
# git clone https://github.com/develone/catzip.git
# cd catzip
# need to have autofpga, verilator and zipcpu built
# set the PATH to where verilator & zipcpu with the script myenv.sh
# . myenv.sh
# /home/pi/verilator
# /home/pi/verilator/bin:/home/pi/zipcpu/sw/install/cross-tools/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/games:/usr/games
# make Toplevel Makefile now supports all of the build
# Now toplevel make creates several bin files for the catboard
# ./rtl/switch_leds/leddigits.bin
# Counts up using the the Xess 8 led digit display
# [Catled](https://github.com/develone/catzip/blob/master/doc/Catleds.png)
# ./rtl/basic/clktest.bin
# ./rtl/basic/blinky.bin
# ./rtl/basic/pmodtest.bin
# ./rtl/basic/dimmer.bin
# ./rtl/catzip/catzip.bin
# ./rtl/uart/helloworld.bin
# sudo minicom -s
# A -    Serial Device      : /dev/ttyUSB0 
# E -    Bps/Par/Bits       : 115200 8N1
# F - Hardware Flow Control : Yes
# Hello, World! written from FPGA UART PMODUSB to RPi3B minicom
# ./rtl/uart/speechfifo.bin
# ./rtl/leddigits/switch_leds.bin
# ./rtl/pptest/hellopp.bin
# Test the parallel interface writing . Hello, World!
# ./rtl/pptest/speechpp.bin 
# Test the parallel interface writing the Gettysburg address on the RPi3B
# ./rtl/pptest/linepp.bin
# ./sw/host/arm-netpport 
# Program which provides the interface between the C programs and the FPGA
# In addition this program provides remote access to fpga
# ./sw/host/arm-wbregs 
# provides peek & poke 
# ./sw/host/arm-wrsdram 
# provides a method to pass data from RPi3B to SDRAM using the FPGA
# ./sw/host/arm-rdsdram 
# provides a method to pass data from SDRAM to RPi3B using the FPGA
# ./sw/host/arm-sdramscope
# ./sw/host/arm-zipdbg
# Peripherals                   CPU State: 0x00000613 Supervisor mode
# >PIC > 0x00000000<   WDT : 0x00000000    WBUS: 0x00000000    PIC2: 0x00000000
#  TMRA: 0x00000000    TMRB: 0x00000000    TMRC: 0x00000000    JIF : 0x00000000
#  MTSK: 0x00000000    MOST: 0x00000000    MPST: 0x00000000    MICT: 0x00000000
# 
# Supervisor Registers
#  sR0 : 0x00000000    sR1 : 0x00000000    sR2 : 0x00000000    sR3 : 0x00000000 
#  sR4 : 0x00000000    sR5 : 0x00000000    sR6 : 0x00000000    sR7 : 0x00000000 
#  sR8 : 0x00000000    sR9 : 0x00000000    sR10: 0x00000000    sR11: 0x00000000 
#  sR12: 0x00000000    sSP : 0x00000000    sCC :               sPC : 0x00800000 
# User Registers
#  uR0 : 0x00000000    uR1 : 0x00000000    uR2 : 0x00000000    uR3 : 0x00000000
#  uR4 : 0x00000000    uR5 : 0x00000000    uR6 : 0x00000000    uR7 : 0x00000000
#  uR8 : 0x00000000    uR9 : 0x00000000    uR10: 0x00000000    uR11: 0x00000000
#  uR12: 0x00000000    uSP : 0x00000000    uCC :               uPC : 0x00000000
# 
# 
#                                                      >00000000 (Bus Err)
#  0x00800008 0x7b47c009  MOV        $36+PC,uPC         00000004 (Bus Err)
#  0x00800004 0x6a402000  LDILO      $8192,SP           00000008 (Bus Err)
# >0x00800000 0x6a000a00  BREV       $2560,SP           0000000c (Bus Err)
#  0x007ffffc 0x--------  (Bus Error)                   00000010 (Bus Err)
# 
# ./sw/host/arm-zipload
# ./sw/host/arm-zipstate
# ./sim/verilated/arm-main_tb
# ./sw/zlib/libcatzip.a
# ./sw/board/cputest
# ./sw/board/hello
# ./sw/board/jpeg

# should have executeables cputest & hello that will run out sdram
# Since the more bkram was in the icozip design hello.c was running out of bkram.

# The program arm-main_tb provides the functions that FPGA using arm-netpport
# 

# The programs config_cat & reset_cat should be linked in /usr/local/bin
# /usr/local/bin/reset_cat -> /home/pi/catboard_yosys/reset_cat
# /usr/local/bin/config_cat -> /home/pi/catboard_yosys/config_cat
# Load the bin file in the FPGA
# sudo config_cat rtl/catzip/catzip.bin 

 
# Displays the date the bin file was created.
# ./arm-wbregs version
01000010 ( VERSION) : [....] 20181120
# Write SDRAM ./arm-wbregs 0x2001000  0x1000

# Read SDRAM ./arm-wbregs 0x2001000

# [ZipCPU](https://github.com/develone/catzip/blob/master/doc/zipcpu.png)
# Both the icozip on ICOBoard & catzip on CatBoard based HX8K ice40 FPGA 
# provide a complete development system on the Raspberry Pi  
# Both icozip & catzip (the catzip simulation when testing items using sdram fails the lower 16 bit fail
# see the results when sim_hw_test.sh is executed) provide a verilated simulation which allows one to 
# test some of the features of the project.
# [sdramtrace.png](https://github.com/develone/catzip/blob/master/sdramtrace.png)
# Both the icozip & catzip are autofpga projects also designed by ZipCPU
# autofpga takes serveral txt files which have tags to create the toplevel.v & main.v needed to support the items
# like sram in icozip or sdram in catzip
# Below is the list of txt used in the catzip project
# This is one of the steps make autofpga in the catzip folder. 
# global.txt bkram.txt buserr.txt clock50.txt pic.txt pwrcount.txt version.txt hbconsole.txt gpio.txt dlyarbiter.txt zipbones.txt sdramdev.txt sdramscope.txt
# [toplevel.v](https://github.com/develone/catzip/blob/master/rtl/catzip/toplevel.v)
# [main.v](https://github.com/develone/catzip/blob/master/rtl/catzip/main.v)
# cpudef.h & design.h bkram & clock
# 
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
#
# The new Goal currently is to get jpeg.c C program running on the CatBoard running with the ZipCPU.
# This program was running on xulalx25soc 
# [main program jpeg.c]()
# [lifting.c](https://github.com/develone/catzip/blob/master/sw/board/lifting.c)
# Once the file has been compile with zip-gcc
# The command to compile "zip-gcc -O3 -c  lifting.c -o obj-zip/lifting.o"
# The disassembly can be done with 
# The command "zip-objdump -d obj-zip/lifting.o > lifting.txt"
# Disassembly of [lifting.txt](https://github.com/develone/catzip/blob/master/sw/board/lifting.txt)
# Steps to test running jpeg 
# Need to read packed image into the SDRAM
# Below is the debug when running
# 01/07/18 Currently since the HX8K does not have implement the mul & div instructions
# the lifting step halts and does not complete the lifting step.

# This was fixed with the update to zipcpu 
commit 097c79344952c2caef83f057348d1d18ab2dd445
Author: ZipCPU <dgisselq@ieee.org>
Date:   Tue Dec 18 13:50:02 2018 -0500

    Default to use OPT_DCACHE in ZipSystem

#  pi@mypi3-1:~/testbuilds/testcatzipmypi3-4/catzip/sw/host $ ./arm-zipload -v ../board/jpeg
#  Halting the CPU
#  Memory regions:
#  	Block RAM: 00400000 - 00402000
#  	SDRAM       : 00800000 - 01000000
#  Loading: ../board/jpeg
#  Section 0: 00800000 - 008cef1c
#  Writing to MEM: 00800000-008cef1c
#  Clearing the CPUs registers
#  Setting PC to 00800000
#  The CPU should be fully loaded, you may now
#  start it (from reset/reboot) with:
#  > wbregs cpu 0x0f
#  
#  CPU Status is: 0000060f
#
#  pi@mypi3-1:~/testbuilds/testcatzipmypi3-4/catzip/sw/host $ ./arm-wrsdram rgb_pack.bin
#  The size of the buffer is 0x00ffff or 65535 words
#  
#  READ-COMPLETE

#  pi@mypi3-1:~/testbuilds/testcatzipmypi3-4/catzip/sw/host $ ./arm-wbregs cpu 0x0f
#  01000000 (        )-> 0000000f
#  . w = 0x100 h = 0x100
#  . ptrs-->img = 0x80eeb0
#  . x = 0xe22247c sp = 0xe2 z = 0xe200000
#  . x = 0xde22083 sp = 0xde z = 0xde00000
#  . x = 0xe221475 sp = 0xe2 z = 0xe200000
#  . x = 0xe32207b sp = 0xe3 z = 0xe300000
#  . x = 0xa812055 sp = 0xa8 z = 0xa800000
#  . x = 0xb210c4c sp = 0xb2 z = 0xb200000
#  . back from split start of dwt 
#  . 0xe2 
#  . 0xde 
#  . 0xe2 
#  . 0xe3 
#  . 0xe1 
#  . 0x0 
#  . 0x0 
#  . 0x0 
#  . 0x0 
#  . 0x0 
#  . 0x100 0x84eeb0 0x88eeb0 0x1  
#  . in lifting 
#  . in singlelift 
#  . in singlelift 
#  . back from singlelift
#  . in lifting 
#  . in singlelift 
#  . in singlelift 
#  . back from singlelift
#  . in lifting 
#  . in singlelift 
#  . in singlelift 
#  . back from singlelift
#  . testing test_fwd  
#  
# [rd_bytes.c](https://github.com/develone/catzip/blob/master/sw/board/rd_bytes.c)

# Disassemble of [rd_bytes.txt](https://github.com/develone/catzip/blob/master/sw/board/rd_bytes.txt)
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
# CATZIP status as of 12/08/18
# The 2 C programs cputest.c & hello.c compile and link with libcatzip.a
# Now both of the C prorgrams work in the FPGA but not in simulation.
# Getting the 2 working required reducing the clk to 40 mhz and increasing 
# size of bkram to 0x2000. 
# arm-zipdbg, arm-zipload, arm-zipstate are built using buildsdramscope.sh
# since the Makefile has not been updated
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

