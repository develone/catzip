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
# make Toplevel Makefile now supports most of the build
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
# ./sw/host/arm-zipload
# ./sw/host/arm-zipstate
# ./sim/verilated/arm-main_tb
# cd ../zib
# make
# should have libcatzip.a
# cd ../board
# make
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
# pi@mypi3-1:~/testbuilds/catzip/sw/host $ ./arm-wrsdram rgb_pack.bin 
# The size of the buffer is 0x00ffff or 65535 words
# 
# READ-COMPLETE
# Need to load the jpeg program into the SDRAM
# pi@mypi3-1:~/testbuilds/catzip/sw/host $ ./arm-zipload -v ../board/jpeg
# Halting the CPU
# Memory regions:
# 	Block RAM: 00a00000 - 00a02000
# 	SDRAM       : 01000000 - 02000000
# Loading: ../board/jpeg
# Section 0: 01000000 - 0100989c
# Writing to MEM: 01000000-0100989c
# Clearing the CPUs registers
# Setting PC to 01000000
# The CPU should be fully loaded, you may now
# start it (from reset/reboot) with:
# > wbregs cpu 0x0f
# 
# CPU Status is: 0000060f
# Below is the debug when running
# 12/2/18 Currently since the HX8K does not have implement the mul & div instructions
# the lifting step halts and does not complete the lifting step.
# pi@mypi3-1:~/testbuilds/catzip/sw/host $ ./arm-wbregs cpu 0x0f
# 02000000 (        )-> 0000000f
# . img_ptr = 0x10098a8
# . buf_red = 0x10498b0
# . buf_gr = 0x110b638
# . buf_bl = 0x118b640
# . fwd_inv = 0x10c98b8
# . Start of JPEG DWT!
# . w = 0x100 h = 0x100
# . img_ptr = 0x10098a8 *img_ptr = 0xe22247c
# . img_ptr = 0x10098ac *img_ptr = 0xde22083
# . img_ptr = 0x10098b0 *img_ptr = 0xe221475
# . img_ptr = 0x10098b4 *img_ptr = 0xe32207b
# . img_ptr = 0x10098b8 *img_ptr = 0xe12287a
# . 
# . img_ptr = 0x1026d7c *img_ptr = 0xb611851
# . img_ptr = 0x1026d80 *img_ptr = 0xb812051
# . img_ptr = 0x1026d84 *img_ptr = 0xce1845b
# . img_ptr = 0x1026d88 *img_ptr = 0xc312c53
# . img_ptr = 0x1026d8c *img_ptr = 0xc31585a
# . 
# . img_ptr = 0x1049070 *img_ptr = 0x8b11058
# . img_ptr = 0x1049074 *img_ptr = 0x800f054
# . img_ptr = 0x1049078 *img_ptr = 0x7409c44
# . img_ptr = 0x104907c *img_ptr = 0x680783b
# . img_ptr = 0x1049080 *img_ptr = 0x6608c43
# . 
# . im_s_ptr = 0x10098a8
# . buf_red = 0x10498b0 *buf_red = 0xe2
# . buf_red = 0x10498b4 *buf_red = 0xde
# . buf_red = 0x10498b8 *buf_red = 0xe2
# . buf_red = 0x10498bc *buf_red = 0xe3
# . buf_red = 0x10498c0 *buf_red = 0xe1
# . 
# . buf_gr = 0x110b638 *buf_gr = 0x89
# . buf_gr = 0x110b63c *buf_gr = 0x88
# . buf_gr = 0x110b640 *buf_gr = 0x85
# . buf_gr = 0x110b644 *buf_gr = 0x88
# . buf_gr = 0x110b648 *buf_gr = 0x8a
# . 
# . buf_bl = 0x118b640 *buf_bl = 0x7c
# . buf_bl = 0x118b644 *buf_bl = 0x83
# . buf_bl = 0x118b648 *buf_bl = 0x75
# . buf_bl = 0x118b64c *buf_bl = 0x7b
# . buf_bl = 0x118b650 *buf_bl = 0x7a
# . 
# . w = 0x100 buf_red wptr = 0x10498b0 alt =  0x10898b0 fwd_inverse =  0x10c98b8. wd_inverse =  0x1 
# . w = 0x100 buf_gr wptr1 = 0x110b638 alt1 =  0x114b638 fwd_inverse =  0x10c98b. fwd_inverse =  0x1 
# . w = 0x100 buf_bl wptr2 = 0x118b640 alt2 =  0x11cb640 fwd_inverse =  0x10c98b. fwd_inverse =  0x1 
# . all pointers for r g b dwt should be setup correctly
# . starting red dwt
# . in lifting 
# . in singlelift 
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

