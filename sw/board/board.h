////////////////////////////////////////////////////////////////////////////////
//
// Filename:	./board.h
//
// Project:	CAT Zip, iCE40 ZipCPU demonstration project
//
// DO NOT EDIT THIS FILE!
// Computer Generated: This file is computer generated by AUTOFPGA. DO NOT EDIT.
// DO NOT EDIT THIS FILE!
//
// CmdLine:	autofpga autofpga -d -o . global.txt bkram.txt buserr.txt clockpll40.txt pic.txt pwrcount.txt version.txt hbconsole.txt gpio.txt dlyarbiter.txt zipbones.txt sdramdev.txt mem_sdram_bkram.txt sdramscope.txt
//
// Creator:	Dan Gisselquist, Ph.D.
//		Gisselquist Technology, LLC
//
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017, Gisselquist Technology, LLC
//
// This program is free software (firmware): you can redistribute it and/or
// modify it under the terms of  the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  (It's in the $(ROOT)/doc directory.  Run make with no
// target there if the PDF file isn't present.)  If not, see
// <http://www.gnu.org/licenses/> for a copy.
//
// License:	GPL, v3, as defined and found on www.gnu.org,
//		http://www.gnu.org/licenses/gpl.html
//
//
////////////////////////////////////////////////////////////////////////////////
//
//
#ifndef	BOARD_H
#define	BOARD_H

// And, so that we can know what is and isn't defined
// from within our main.v file, let's include:
#include <design.h>

#include <design.h>
#include <cpudefs.h>

#define	_HAVE_ZIPBONES



//
// GPIO input wires
//
#define	GPIO_IN(WIRE)	((WIRE)<<16)
#define	GPIO_BTN_0	0x00001
#define	GPIO_BTN_1	0x00002
//
// GPIO output wires
//
#define	GPIO_IN(WIRE)	((WIRE)<<16)
#define	GPIO_SET(WIRE)	(((WIRE)<<16)|(WIRE))
#define	GPIO_CLR(WIRE)	 ((WIRE)<<16)
//
#define	GPIO_LEDR		0x000000001
#define	GPIO_LEDG0		0x000000002
#define	GPIO_LEDG1		0x000000004
//
#define	GPIO_LEDR_SET	GPIO_SET(GPIO_LEDR)
#define	GPIO_LEDR_CLR	GPIO_CLR(GPIO_LEDR)
#define	GPIO_LEDG0_SET	GPIO_SET(GPIO_LEDG0)
#define	GPIO_LEDG0_CLR	GPIO_CLR(GPIO_LEDG0)
#define	GPIO_LEDG1_SET	GPIO_SET(GPIO_LEDG1)
#define	GPIO_LEDG1_CLR	GPIO_CLR(GPIO_LEDG1)


typedef struct  CONSOLE_S {
	unsigned	u_setup;
	unsigned	u_fifo;
	unsigned	u_rx, u_tx;
} CONSOLE;



#define	CLKFREQHZ	40000000


#define BUSPIC(X) (1<<X)


#ifdef	SDRAM_ACCESS
#define	_BOARD_HAS_SDRAM
extern char	_sdram[0x01000000];
#endif	// SDRAM_ACCESS
#ifdef	GPIO_ACCESS
#define	_BOARD_HAS_GPIO
static volatile unsigned *const _gpio = ((unsigned *)8);
#endif	// GPIO_ACCESS
#ifdef	BUSCONSOLE_ACCESS
#define	_BOARD_HAS_BUSCONSOLE
static volatile CONSOLE *const _uart = ((CONSOLE *)6291456);
#endif	// BUSCONSOLE_ACCESS
#ifdef	BUSTIMER_ACCESS
#define	_BOARD_HAS_BUSTIMER
static volatile unsigned *const _bustimer = ((unsigned *)0x00400000);
#endif	// BUSTIMER_ACCESS
#define	_BOARD_HAS_BUSERR
static volatile unsigned *const _buserr = ((unsigned *)8388608);
#ifdef	BKRAM_ACCESS
#define	_BOARD_HAS_BKRAM
extern char	_bkram[0x00002000];
#endif	// BKRAM_ACCESS
#define	_BOARD_HAS_VERSION
#ifdef	BUSPIC_ACCESS
#define	_BOARD_HAS_BUSPIC
static volatile unsigned *const _buspic = ((unsigned *)8388612);
#endif	// BUSPIC_ACCESS
//
// Interrupt assignments (2 PICs)
//
// PIC: cpu_reset
#define	CPU_RESET_RESET	CPU_RESET(0)
#define	CPU_RESET_WATCHDOG	CPU_RESET(1)
// PIC: buspic
#define	BUSPIC_GPIO	BUSPIC(0)
#define	BUSPIC_UARTTXF	BUSPIC(1)
#define	BUSPIC_UARTRXF	BUSPIC(2)
#define	BUSPIC_BUSTIMER	BUSPIC(3)
#endif	// BOARD_H
