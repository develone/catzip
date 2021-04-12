`timescale	1ps / 1ps
////////////////////////////////////////////////////////////////////////////////
//
// Filename:	./main.v
//
// Project:	ICO Zip, iCE40 ZipCPU demonstration project
//
// DO NOT EDIT THIS FILE!
// Computer Generated: This file is computer generated by AUTOFPGA. DO NOT EDIT.
// DO NOT EDIT THIS FILE!
//
// CmdLine:	autofpga autofpga -d -o . clockpll40.txt global.txt version.txt buserr.txt pic.txt pwrcount.txt gpio.txt sdramdev.txt bkram.txt hbconsole.txt zipbones.txt mem_flash_bkram.txt mem_bkram_only.txt mem_flash_sdram.txt mem_sdram_only.txt
//
// Creator:	Dan Gisselquist, Ph.D.
//		Gisselquist Technology, LLC
//
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017-2020, Gisselquist Technology, LLC
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
`default_nettype	none
//
//
// Here is a list of defines which may be used, post auto-design
// (not post-build), to turn particular peripherals (and bus masters)
// on and off.  In particular, to turn off support for a particular
// design component, just comment out its respective `define below.
//
// These lines are taken from the respective @ACCESS tags for each of our
// components.  If a component doesn't have an @ACCESS tag, it will not
// be listed here.
//
// First, the independent access fields for any bus masters
`define	WBUBUS_MASTER
// And then for the independent peripherals
`define	BUSTIMER_ACCESS
`define	BUSPIC_ACCESS
`define	BKRAM_ACCESS
`define	GPIO_ACCESS
`define	SDRAM_ACCESS
`define	PWRCOUNT_ACCESS
`define	BUSCONSOLE_ACCESS
`define	WATCHDOG_ACCESS
`define	INCLUDE_ZIPCPU
//
// End of dependency list
//
//
//
// Any include files
//
// These are drawn from anything with a MAIN.INCLUDE definition.
//
//
// Finally, we define our main module itself.  We start with the list of
// I/O ports, or wires, passed into (or out of) the main function.
//
// These fields are copied verbatim from the respective I/O port lists,
// from the fields given by @MAIN.PORTLIST
//
module	main(i_clk, i_reset,
		// GPIO ports
		i_gpio, o_gpio,
		o_ram_cs_n, o_ram_cke, o_ram_ras_n, o_ram_cas_n, o_ram_we_n, 
			o_ram_bs, o_ram_addr,
			o_ram_drive_data, i_ram_data, o_ram_data, o_ram_dqm,
			o_debug,
		// Command and Control port
		i_pp_clk, i_pp_dir, i_pp_data, o_pp_data, o_pp_clkfb, o_pp_dbg);
//
// Any parameter definitions
//
// These are drawn from anything with a MAIN.PARAM definition.
// As they aren't connected to the toplevel at all, it would
// be best to use localparam over parameter, but here we don't
// check
	//
	//
	// Variables/definitions needed by the ZipCPU BUS master
	//
	//
	// A 32-bit address indicating where the ZipCPU should start running
	// from
	localparam	RESET_ADDRESS = 20971520;
	//
	// The number of valid bits on the bus
	localparam	ZIP_ADDRESS_WIDTH = 24; // Zip-CPU address width
	//
	// ZIP_START_HALTED
	//
	// A boolean, indicating whether or not the ZipCPU be halted on startup?
	localparam	ZIP_START_HALTED=1'b1;
//
// The next step is to declare all of the various ports that were just
// listed above.  
//
// The following declarations are taken from the values of the various
// @MAIN.IODECL keys.
//
	input	wire		i_clk;
	// verilator lint_off UNUSED
	input	wire		i_reset;
	// verilator lint_on UNUSED
	localparam	NGPI = 2, NGPO=11;
	// GPIO ports
	input		[(NGPI-1):0]	i_gpio;
	output	wire	[(NGPO-1):0]	o_gpio;
parameter	RDLY = 6;

	// SDRAM control
	output	wire		o_ram_cke;
	output	wire		o_ram_cs_n,
				o_ram_ras_n, o_ram_cas_n, o_ram_we_n;
	output	wire	[1:0]	o_ram_bs;
	output	wire	[12:0]	o_ram_addr;
	 
	input	wire	[15:0]	i_ram_data;
	output	wire	[15:0]	o_ram_data;
	output	wire	[1:0]	o_ram_dqm;
	output	wire	[31:0]	o_debug;
 
	wire	[15:0]	ram_data;
	output	wire		o_ram_drive_data; 
	
	input	wire		i_pp_clk, i_pp_dir;
	input	wire	[7:0]	i_pp_data;
	output	wire	[7:0]	o_pp_data;
	output	wire		o_pp_clkfb;
	output	wire		o_pp_dbg;
	// Make Verilator happy ... defining bus wires for lots of components
	// often ends up with unused wires lying around.  We'll turn off
	// Ver1lator's lint warning here that checks for unused wires.
	// verilator lint_off UNUSED



	//
	// Declaring interrupt lines
	//
	// These declarations come from the various components values
	// given under the @INT.<interrupt name>.WIRE key.
	//
	wire	bustimer_int;	// bustimer.INT.BUSTIMER.WIRE
	wire	w_bus_int;	// buspic.INT.BUS.WIRE
	wire	gpio_int;	// gpio.INT.GPIO.WIRE
	wire	uarttxf_int;	// console.INT.UARTTXF.WIRE
	wire	uartrxf_int;	// console.INT.UARTRXF.WIRE
	wire	uartrx_int;	// console.INT.UARTRX.WIRE
	wire	uarttx_int;	// console.INT.UARTTX.WIRE
	wire	design_reset;	// watchdog.INT.RESET.WIRE
	wire	watchdog_reset;	// watchdog.INT.WATCHDOG.WIRE
	wire	zip_cpu_int;	// zip.INT.ZIP.WIRE


	//
	// Component declarations
	//
	// These declarations come from the @MAIN.DEFNS keys found in the
	// various components comprising the design.
	//
// BUILDTIME doesnt need to include builddate.v a second time
// `include "builddate.v"
`include "builddate.v"
	reg	[31:0]	r_pwrcount_data;
	// Console definitions
	wire		w_console_rx_stb, w_console_tx_stb, w_console_busy;
	wire	[6:0]	w_console_rx_data, w_console_tx_data;
	// Definitions for the WB-UART converter.  We really only need one
	// (more) non-bus wire--one to use to select if we are interacting
	// with the ZipCPU or not.
	wire		pp_rx_stb,  pp_tx_stb,  pp_tx_busy;
	wire	[7:0]	pp_rx_data, pp_tx_data;
	wire	[31:0]	console_dbg;
	reg	cpu_reset;
	reg	[25-1:0]	r_buserr_addr;
	// ZipSystem/ZipCPU connection definitions
	// All we define here is a set of scope wires
	wire	[31:0]	zip_debug;
	wire		zip_trigger;
	wire		zip_halted;


	//
	// Declaring interrupt vector wires
	//
	// These declarations come from the various components having
	// PIC and PIC.MAX keys.
	//
	wire	[14:0]	bus_int_vector;
	wire	[7:0]	cpu_reset_bus;
	//
	//
	// Define bus wires
	//
	//

	// Bus wb
	// Wishbone definitions for bus wb, component hbarb
	// Verilator lint_off UNUSED
	wire		wb_hbarb_cyc, wb_hbarb_stb, wb_hbarb_we;
	wire	[23:0]	wb_hbarb_addr;
	wire	[31:0]	wb_hbarb_data;
	wire	[3:0]	wb_hbarb_sel;
	wire		wb_hbarb_stall, wb_hbarb_ack, wb_hbarb_err;
	wire	[31:0]	wb_hbarb_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb, component zip
	// Verilator lint_off UNUSED
	wire		wb_zip_cyc, wb_zip_stb, wb_zip_we;
	wire	[23:0]	wb_zip_addr;
	wire	[31:0]	wb_zip_data;
	wire	[3:0]	wb_zip_sel;
	wire		wb_zip_stall, wb_zip_ack, wb_zip_err;
	wire	[31:0]	wb_zip_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb(SIO), component buildtime
	// Verilator lint_off UNUSED
	wire		wb_buildtime_cyc, wb_buildtime_stb, wb_buildtime_we;
	wire	[23:0]	wb_buildtime_addr;
	wire	[31:0]	wb_buildtime_data;
	wire	[3:0]	wb_buildtime_sel;
	wire		wb_buildtime_stall, wb_buildtime_ack, wb_buildtime_err;
	wire	[31:0]	wb_buildtime_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb(SIO), component buserr
	// Verilator lint_off UNUSED
	wire		wb_buserr_cyc, wb_buserr_stb, wb_buserr_we;
	wire	[23:0]	wb_buserr_addr;
	wire	[31:0]	wb_buserr_data;
	wire	[3:0]	wb_buserr_sel;
	wire		wb_buserr_stall, wb_buserr_ack, wb_buserr_err;
	wire	[31:0]	wb_buserr_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb(SIO), component buspic
	// Verilator lint_off UNUSED
	wire		wb_buspic_cyc, wb_buspic_stb, wb_buspic_we;
	wire	[23:0]	wb_buspic_addr;
	wire	[31:0]	wb_buspic_data;
	wire	[3:0]	wb_buspic_sel;
	wire		wb_buspic_stall, wb_buspic_ack, wb_buspic_err;
	wire	[31:0]	wb_buspic_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb(SIO), component gpio
	// Verilator lint_off UNUSED
	wire		wb_gpio_cyc, wb_gpio_stb, wb_gpio_we;
	wire	[23:0]	wb_gpio_addr;
	wire	[31:0]	wb_gpio_data;
	wire	[3:0]	wb_gpio_sel;
	wire		wb_gpio_stall, wb_gpio_ack, wb_gpio_err;
	wire	[31:0]	wb_gpio_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb(SIO), component pwrcount
	// Verilator lint_off UNUSED
	wire		wb_pwrcount_cyc, wb_pwrcount_stb, wb_pwrcount_we;
	wire	[23:0]	wb_pwrcount_addr;
	wire	[31:0]	wb_pwrcount_data;
	wire	[3:0]	wb_pwrcount_sel;
	wire		wb_pwrcount_stall, wb_pwrcount_ack, wb_pwrcount_err;
	wire	[31:0]	wb_pwrcount_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb(SIO), component version
	// Verilator lint_off UNUSED
	wire		wb_version_cyc, wb_version_stb, wb_version_we;
	wire	[23:0]	wb_version_addr;
	wire	[31:0]	wb_version_data;
	wire	[3:0]	wb_version_sel;
	wire		wb_version_stall, wb_version_ack, wb_version_err;
	wire	[31:0]	wb_version_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb, component bustimer
	// Verilator lint_off UNUSED
	wire		wb_bustimer_cyc, wb_bustimer_stb, wb_bustimer_we;
	wire	[23:0]	wb_bustimer_addr;
	wire	[31:0]	wb_bustimer_data;
	wire	[3:0]	wb_bustimer_sel;
	wire		wb_bustimer_stall, wb_bustimer_ack, wb_bustimer_err;
	wire	[31:0]	wb_bustimer_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb, component watchdog
	// Verilator lint_off UNUSED
	wire		wb_watchdog_cyc, wb_watchdog_stb, wb_watchdog_we;
	wire	[23:0]	wb_watchdog_addr;
	wire	[31:0]	wb_watchdog_data;
	wire	[3:0]	wb_watchdog_sel;
	wire		wb_watchdog_stall, wb_watchdog_ack, wb_watchdog_err;
	wire	[31:0]	wb_watchdog_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb, component console
	// Verilator lint_off UNUSED
	wire		wb_console_cyc, wb_console_stb, wb_console_we;
	wire	[23:0]	wb_console_addr;
	wire	[31:0]	wb_console_data;
	wire	[3:0]	wb_console_sel;
	wire		wb_console_stall, wb_console_ack, wb_console_err;
	wire	[31:0]	wb_console_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb, component wb_sio
	// Verilator lint_off UNUSED
	wire		wb_sio_cyc, wb_sio_stb, wb_sio_we;
	wire	[23:0]	wb_sio_addr;
	wire	[31:0]	wb_sio_data;
	wire	[3:0]	wb_sio_sel;
	wire		wb_sio_stall, wb_sio_ack, wb_sio_err;
	wire	[31:0]	wb_sio_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb, component bkram
	// Verilator lint_off UNUSED
	wire		wb_bkram_cyc, wb_bkram_stb, wb_bkram_we;
	wire	[23:0]	wb_bkram_addr;
	wire	[31:0]	wb_bkram_data;
	wire	[3:0]	wb_bkram_sel;
	wire		wb_bkram_stall, wb_bkram_ack, wb_bkram_err;
	wire	[31:0]	wb_bkram_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus wb, component sdram
	// Verilator lint_off UNUSED
	wire		wb_sdram_cyc, wb_sdram_stb, wb_sdram_we;
	wire	[23:0]	wb_sdram_addr;
	wire	[31:0]	wb_sdram_data;
	wire	[3:0]	wb_sdram_sel;
	wire		wb_sdram_stall, wb_sdram_ack, wb_sdram_err;
	wire	[31:0]	wb_sdram_idata;
	// Verilator lint_on UNUSED
	// Bus hb
	// Wishbone definitions for bus hb, component hb
	// Verilator lint_off UNUSED
	wire		hb_hb_cyc, hb_hb_stb, hb_hb_we;
	wire	[24:0]	hb_hb_addr;
	wire	[31:0]	hb_hb_data;
	wire	[3:0]	hb_hb_sel;
	wire		hb_hb_stall, hb_hb_ack, hb_hb_err;
	wire	[31:0]	hb_hb_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus hb, component hbarb
	// Verilator lint_off UNUSED
	wire		hb_hbarb_cyc, hb_hbarb_stb, hb_hbarb_we;
	wire	[24:0]	hb_hbarb_addr;
	wire	[31:0]	hb_hbarb_data;
	wire	[3:0]	hb_hbarb_sel;
	wire		hb_hbarb_stall, hb_hbarb_ack, hb_hbarb_err;
	wire	[31:0]	hb_hbarb_idata;
	// Verilator lint_on UNUSED
	// Wishbone definitions for bus hb, component zip
	// Verilator lint_off UNUSED
	wire		hb_zip_cyc, hb_zip_stb, hb_zip_we;
	wire	[24:0]	hb_zip_addr;
	wire	[31:0]	hb_zip_data;
	wire	[3:0]	hb_zip_sel;
	wire		hb_zip_stall, hb_zip_ack, hb_zip_err;
	wire	[31:0]	hb_zip_idata;
	// Verilator lint_on UNUSED

	//
	// Peripheral address decoding
	//
	//
	// BUS-LOGIC for wb
	//
	//
	// wb Bus logic to handle SINGLE slaves
	//
	reg		r_wb_sio_ack;
	reg	[31:0]	r_wb_sio_data;

	assign	wb_sio_stall = 1'b0;

	initial r_wb_sio_ack = 1'b0;
	always	@(posedge i_clk)
		r_wb_sio_ack <= (wb_sio_stb);
	assign	wb_sio_ack = r_wb_sio_ack;

	always	@(posedge i_clk)
	casez( wb_sio_addr[2:0] )
	3'h0: r_wb_sio_data <= wb_buildtime_idata;
	3'h1: r_wb_sio_data <= wb_buserr_idata;
	3'h2: r_wb_sio_data <= wb_buspic_idata;
	3'h3: r_wb_sio_data <= wb_gpio_idata;
	3'h4: r_wb_sio_data <= wb_pwrcount_idata;
	3'h5: r_wb_sio_data <= wb_version_idata;
	default: r_wb_sio_data <= wb_version_idata;
	endcase
	assign	wb_sio_idata = r_wb_sio_data;


	//
	// Now to translate this logic to the various SIO slaves
	//
	// In this case, the SIO bus has the prefix wb_sio
	// and all of the slaves have various wires beginning
	// with their own respective bus prefixes.
	// Our goal here is to make certain that all of
	// the slave bus inputs match the SIO bus wires
	assign	wb_buildtime_cyc = wb_sio_cyc;
	assign	wb_buildtime_stb = wb_sio_stb && (wb_sio_addr[ 2: 0] ==  3'h0);  // 0x000000
	assign	wb_buildtime_we  = wb_sio_we;
	assign	wb_buildtime_data= wb_sio_data;
	assign	wb_buildtime_sel = wb_sio_sel;
	assign	wb_buserr_cyc = wb_sio_cyc;
	assign	wb_buserr_stb = wb_sio_stb && (wb_sio_addr[ 2: 0] ==  3'h1);  // 0x000004
	assign	wb_buserr_we  = wb_sio_we;
	assign	wb_buserr_data= wb_sio_data;
	assign	wb_buserr_sel = wb_sio_sel;
	assign	wb_buspic_cyc = wb_sio_cyc;
	assign	wb_buspic_stb = wb_sio_stb && (wb_sio_addr[ 2: 0] ==  3'h2);  // 0x000008
	assign	wb_buspic_we  = wb_sio_we;
	assign	wb_buspic_data= wb_sio_data;
	assign	wb_buspic_sel = wb_sio_sel;
	assign	wb_gpio_cyc = wb_sio_cyc;
	assign	wb_gpio_stb = wb_sio_stb && (wb_sio_addr[ 2: 0] ==  3'h3);  // 0x00000c
	assign	wb_gpio_we  = wb_sio_we;
	assign	wb_gpio_data= wb_sio_data;
	assign	wb_gpio_sel = wb_sio_sel;
	assign	wb_pwrcount_cyc = wb_sio_cyc;
	assign	wb_pwrcount_stb = wb_sio_stb && (wb_sio_addr[ 2: 0] ==  3'h4);  // 0x000010
	assign	wb_pwrcount_we  = wb_sio_we;
	assign	wb_pwrcount_data= wb_sio_data;
	assign	wb_pwrcount_sel = wb_sio_sel;
	assign	wb_version_cyc = wb_sio_cyc;
	assign	wb_version_stb = wb_sio_stb && (wb_sio_addr[ 2: 0] ==  3'h5);  // 0x000014
	assign	wb_version_we  = wb_sio_we;
	assign	wb_version_data= wb_sio_data;
	assign	wb_version_sel = wb_sio_sel;
	//
	// No class DOUBLE peripherals on the "wb" bus
	//

	assign	wb_bustimer_err= 1'b0;
	assign	wb_watchdog_err= 1'b0;
	assign	wb_console_err= 1'b0;
	assign	wb_sio_err= 1'b0;
	assign	wb_bkram_err= 1'b0;
	assign	wb_sdram_err= 1'b0;
	//
	// Connect the wb bus components together using the wbxbar()
	//
	//
	wbxbar #(
		.NM(2), .NS(6), .AW(24), .DW(32),
		.SLAVE_ADDR({
			// Address width    = 24
			// Address LSBs     = 2
			// Slave name width = 8
			{ 24'h800000 }, //    sdram: 0x2000000
			{ 24'h500000 }, //    bkram: 0x1400000
			{ 24'h400000 }, //   wb_sio: 0x1000000
			{ 24'h300000 }, //  console: 0x0c00000
			{ 24'h200000 }, // watchdog: 0x0800000
			{ 24'h100000 }  // bustimer: 0x0400000
		}),
		.SLAVE_MASK({
			// Address width    = 24
			// Address LSBs     = 2
			// Slave name width = 8
			{ 24'hc00000 }, //    sdram
			{ 24'hf00000 }, //    bkram
			{ 24'hf00000 }, //   wb_sio
			{ 24'hf00000 }, //  console
			{ 24'hf00000 }, // watchdog
			{ 24'hf00000 }  // bustimer
		}),
		.OPT_DBLBUFFER(1'b1))
	wb_xbar(
		.i_clk(i_clk), .i_reset(i_reset),
		.i_mcyc({
			wb_zip_cyc,
			wb_hbarb_cyc
		}),
		.i_mstb({
			wb_zip_stb,
			wb_hbarb_stb
		}),
		.i_mwe({
			wb_zip_we,
			wb_hbarb_we
		}),
		.i_maddr({
			wb_zip_addr,
			wb_hbarb_addr
		}),
		.i_mdata({
			wb_zip_data,
			wb_hbarb_data
		}),
		.i_msel({
			wb_zip_sel,
			wb_hbarb_sel
		}),
		.o_mstall({
			wb_zip_stall,
			wb_hbarb_stall
		}),
		.o_mack({
			wb_zip_ack,
			wb_hbarb_ack
		}),
		.o_mdata({
			wb_zip_idata,
			wb_hbarb_idata
		}),
		.o_merr({
			wb_zip_err,
			wb_hbarb_err
		}),
		// Slave connections
		.o_scyc({
			wb_sdram_cyc,
			wb_bkram_cyc,
			wb_sio_cyc,
			wb_console_cyc,
			wb_watchdog_cyc,
			wb_bustimer_cyc
		}),
		.o_sstb({
			wb_sdram_stb,
			wb_bkram_stb,
			wb_sio_stb,
			wb_console_stb,
			wb_watchdog_stb,
			wb_bustimer_stb
		}),
		.o_swe({
			wb_sdram_we,
			wb_bkram_we,
			wb_sio_we,
			wb_console_we,
			wb_watchdog_we,
			wb_bustimer_we
		}),
		.o_saddr({
			wb_sdram_addr,
			wb_bkram_addr,
			wb_sio_addr,
			wb_console_addr,
			wb_watchdog_addr,
			wb_bustimer_addr
		}),
		.o_sdata({
			wb_sdram_data,
			wb_bkram_data,
			wb_sio_data,
			wb_console_data,
			wb_watchdog_data,
			wb_bustimer_data
		}),
		.o_ssel({
			wb_sdram_sel,
			wb_bkram_sel,
			wb_sio_sel,
			wb_console_sel,
			wb_watchdog_sel,
			wb_bustimer_sel
		}),
		.i_sstall({
			wb_sdram_stall,
			wb_bkram_stall,
			wb_sio_stall,
			wb_console_stall,
			wb_watchdog_stall,
			wb_bustimer_stall
		}),
		.i_sack({
			wb_sdram_ack,
			wb_bkram_ack,
			wb_sio_ack,
			wb_console_ack,
			wb_watchdog_ack,
			wb_bustimer_ack
		}),
		.i_sdata({
			wb_sdram_idata,
			wb_bkram_idata,
			wb_sio_idata,
			wb_console_idata,
			wb_watchdog_idata,
			wb_bustimer_idata
		}),
		.i_serr({
			wb_sdram_err,
			wb_bkram_err,
			wb_sio_err,
			wb_console_err,
			wb_watchdog_err,
			wb_bustimer_err
		})
		);

	//
	// BUS-LOGIC for hb
	//
	//
	// No class SINGLE peripherals on the "hb" bus
	//

	//
	// No class DOUBLE peripherals on the "hb" bus
	//

	// info: @ERROR.WIRE for hbarb matches the buses error name, hb_hbarb_err
	assign	hb_zip_err= 1'b0;
	//
	// Connect the hb bus components together using the wbxbar()
	//
	//
	wbxbar #(
		.NM(1), .NS(2), .AW(25), .DW(32),
		.SLAVE_ADDR({
			// Address width    = 25
			// Address LSBs     = 2
			// Slave name width = 5
			{ 25'h1000000 }, //   zip: 0x4000000
			{ 25'h0000000 }  // hbarb: 0x0000000
		}),
		.SLAVE_MASK({
			// Address width    = 25
			// Address LSBs     = 2
			// Slave name width = 5
			{ 25'h1000000 }, //   zip
			{ 25'h1000000 }  // hbarb
		}),
		.OPT_DBLBUFFER(1'b1))
	hb_xbar(
		.i_clk(i_clk), .i_reset(i_reset),
		.i_mcyc({
			hb_hb_cyc
		}),
		.i_mstb({
			hb_hb_stb
		}),
		.i_mwe({
			hb_hb_we
		}),
		.i_maddr({
			hb_hb_addr
		}),
		.i_mdata({
			hb_hb_data
		}),
		.i_msel({
			hb_hb_sel
		}),
		.o_mstall({
			hb_hb_stall
		}),
		.o_mack({
			hb_hb_ack
		}),
		.o_mdata({
			hb_hb_idata
		}),
		.o_merr({
			hb_hb_err
		}),
		// Slave connections
		.o_scyc({
			hb_zip_cyc,
			hb_hbarb_cyc
		}),
		.o_sstb({
			hb_zip_stb,
			hb_hbarb_stb
		}),
		.o_swe({
			hb_zip_we,
			hb_hbarb_we
		}),
		.o_saddr({
			hb_zip_addr,
			hb_hbarb_addr
		}),
		.o_sdata({
			hb_zip_data,
			hb_hbarb_data
		}),
		.o_ssel({
			hb_zip_sel,
			hb_hbarb_sel
		}),
		.i_sstall({
			hb_zip_stall,
			hb_hbarb_stall
		}),
		.i_sack({
			hb_zip_ack,
			hb_hbarb_ack
		}),
		.i_sdata({
			hb_zip_idata,
			hb_hbarb_idata
		}),
		.i_serr({
			hb_zip_err,
			hb_hbarb_err
		})
		);

	//
	// Declare the interrupt busses
	//
	// Interrupt busses are defined by anything with a @PIC tag.
	// The @PIC.BUS tag defines the name of the wire bus below,
	// while the @PIC.MAX tag determines the size of the bus width.
	//
	// For your peripheral to be assigned to this bus, it must have an
	// @INT.NAME.WIRE= tag to define the wire name of the interrupt line,
	// and an @INT.NAME.PIC= tag matching the @PIC.BUS tag of the bus
	// your interrupt will be assigned to.  If an @INT.NAME.ID tag also
	// exists, then your interrupt will be assigned to the position given
	// by the ID# in that tag.
	//
	assign	bus_int_vector = {
		1'b0,
		1'b0,
		1'b0,
		1'b0,
		1'b0,
		1'b0,
		1'b0,
		1'b0,
		1'b0,
		1'b0,
		1'b0,
		uartrxf_int,
		uarttxf_int,
		gpio_int,
		bustimer_int
	};
	assign	cpu_reset_bus = {
		1'b0,
		1'b0,
		1'b0,
		1'b0,
		1'b0,
		1'b0,
		watchdog_reset,
		design_reset
	};


	//
	//
	// Now we turn to defining all of the parts and pieces of what
	// each of the various peripherals does, and what logic it needs.
	//
	// This information comes from the @MAIN.INSERT and @MAIN.ALT tags.
	// If an @ACCESS tag is available, an ifdef is created to handle
	// having the access and not.  If the @ACCESS tag is `defined above
	// then the @MAIN.INSERT code is executed.  If not, the @MAIN.ALT
	// code is exeucted, together with any other cleanup settings that
	// might need to take place--such as returning zeros to the bus,
	// or making sure all of the various interrupt wires are set to
	// zero if the component is not included.
	//
	assign	wb_buildtime_idata = `BUILDTIME;
	assign	wb_buildtime_ack = wb_buildtime_stb;
	assign	wb_buildtime_stall = 1'b0;
	assign	wb_version_idata = `DATESTAMP;
	assign	wb_version_ack = wb_version_stb;
	assign	wb_version_stall = 1'b0;
	assign	wb_hbarb_cyc  = hb_hbarb_cyc;
	assign	wb_hbarb_stb  = hb_hbarb_stb;
	assign	wb_hbarb_we   = hb_hbarb_we;
	assign	wb_hbarb_addr = hb_hbarb_addr[24-1:0];
	assign	wb_hbarb_data = hb_hbarb_data;
	assign	wb_hbarb_sel  = hb_hbarb_sel;
	assign	hb_hbarb_stall = wb_hbarb_stall;
	assign	hb_hbarb_ack   = wb_hbarb_ack;
	assign	hb_hbarb_idata = wb_hbarb_idata;
	assign	hb_hbarb_err   = wb_hbarb_err;
`ifdef	BUSTIMER_ACCESS
	ziptimer #(.VW(16))
		bustimeri(i_clk, i_reset, 1'b1,
			wb_bustimer_cyc, wb_bustimer_stb, wb_bustimer_we,
			wb_bustimer_data, // 32 bits wide
			wb_bustimer_sel,  // 32/8 bits wide
		wb_bustimer_stall, wb_bustimer_ack, wb_bustimer_idata,
			bustimer_int);
`else	// BUSTIMER_ACCESS

	//
	// In the case that there is no wb_bustimer peripheral
	// responding on the wb bus
	assign	wb_bustimer_ack   = 1'b0;
	assign	wb_bustimer_err   = (wb_bustimer_stb);
	assign	wb_bustimer_stall = 0;
	assign	wb_bustimer_idata = 0;

	assign	bustimer_int = 1'b0;	// bustimer.INT.BUSTIMER.WIRE
`endif	// BUSTIMER_ACCESS

`ifdef	BUSPIC_ACCESS
	//
	// The BUS Interrupt controller
	//
	icontrol #(15)	buspici(i_clk, 1'b0,
			wb_buspic_cyc, wb_buspic_stb, wb_buspic_we,
			wb_buspic_data, // 32 bits wide
			wb_buspic_sel,  // 32/8 bits wide
		wb_buspic_stall, wb_buspic_ack, wb_buspic_idata,
			bus_int_vector, w_bus_int);
`else	// BUSPIC_ACCESS
	assign	w_bus_int = 1'b0;	// buspic.INT.BUS.WIRE
`endif	// BUSPIC_ACCESS

`ifdef	BKRAM_ACCESS
	memdev #(.LGMEMSZ(13), .EXTRACLOCK(1))
		bkrami(i_clk, 1'b0,
		wb_bkram_cyc, wb_bkram_stb, wb_bkram_we,
			wb_bkram_addr[11-1:0],
			wb_bkram_data, // 32 bits wide
			wb_bkram_sel,  // 32/8 bits wide
		wb_bkram_stall, wb_bkram_ack, wb_bkram_idata);
`else	// BKRAM_ACCESS

	//
	// In the case that there is no wb_bkram peripheral
	// responding on the wb bus
	assign	wb_bkram_ack   = 1'b0;
	assign	wb_bkram_err   = (wb_bkram_stb);
	assign	wb_bkram_stall = 0;
	assign	wb_bkram_idata = 0;

`endif	// BKRAM_ACCESS

`ifdef	GPIO_ACCESS
	//
	// GPIO
	//
	// This interface should allow us to control up to 16 GPIO inputs,
	// and another 16 GPIO outputs.  The interrupt trips when any of
	// the inputs changes.  (Sorry, which input isn't (yet) selectable.)
	//
	localparam	INITIAL_GPIO = 11'h0;
	wbgpio	#(NGPI, NGPO, INITIAL_GPIO)
		gpioi(i_clk, 1'b0, wb_gpio_cyc, wb_gpio_stb, wb_gpio_we,
			wb_gpio_data, // 32 bits wide
			wb_gpio_sel,  // 32/8 bits wide
		wb_gpio_stall, wb_gpio_ack, wb_gpio_idata,
			i_gpio, o_gpio, gpio_int);
`else	// GPIO_ACCESS
	assign	gpio_int = 1'b0;	// gpio.INT.GPIO.WIRE
`endif	// GPIO_ACCESS

`ifdef	SDRAM_ACCESS
	sdramdev 
	
		sdrami(i_clk,
			wb_sdram_cyc,
			/* verilator lint_off WIDTH */ 
			((wb_sdram_stb)&&(wb_sdram_sel)),
			/* verilator lint_off WIDTH */
			wb_sdram_we,
			wb_sdram_addr[(24-2):0],
			wb_sdram_data, // 32 bits wide
			wb_sdram_sel,  // 32/8 bits wide
			wb_sdram_ack, wb_sdram_stall, wb_sdram_idata,


		o_ram_cs_n, o_ram_cke, o_ram_ras_n, o_ram_cas_n, o_ram_we_n,
		o_ram_bs, o_ram_addr,
		o_ram_drive_data, i_ram_data, o_ram_data, o_ram_dqm,
		o_debug);	

`else	// SDRAM_ACCESS

	//
	// In the case that there is no wb_sdram peripheral
	// responding on the wb bus
	assign	wb_sdram_ack   = 1'b0;
	assign	wb_sdram_err   = (wb_sdram_stb);
	assign	wb_sdram_stall = 0;
	assign	wb_sdram_idata = 0;

`endif	// SDRAM_ACCESS

`ifdef	PWRCOUNT_ACCESS
	initial	r_pwrcount_data = 32'h0;
	always @(posedge i_clk)
	if (r_pwrcount_data[31])
		r_pwrcount_data[30:0] <= r_pwrcount_data[30:0] + 1'b1;
	else
		r_pwrcount_data[31:0] <= r_pwrcount_data[31:0] + 1'b1;

	assign	wb_pwrcount_stall = 1'b0;
	assign	wb_pwrcount_ack   = wb_pwrcount_stb;
	assign	wb_pwrcount_idata = r_pwrcount_data;
`else	// PWRCOUNT_ACCESS
`endif	// PWRCOUNT_ACCESS

`ifdef	BUSCONSOLE_ACCESS
	console consolei(i_clk, 1'b0,
			wb_console_cyc, wb_console_stb, wb_console_we,
			wb_console_addr[2-1:0],
			wb_console_data, // 32 bits wide
			wb_console_sel,  // 32/8 bits wide
		wb_console_stall, wb_console_ack, wb_console_idata,
			w_console_tx_stb, w_console_tx_data, w_console_busy,
			w_console_rx_stb, w_console_rx_data,
			uartrx_int, uarttx_int, uartrxf_int, uarttxf_int,
			console_dbg);
`else	// BUSCONSOLE_ACCESS
	assign	w_console_tx_stb  = 1'b0;
	assign	w_console_tx_data = 7'h7f;

	//
	// In the case that there is no wb_console peripheral
	// responding on the wb bus
	assign	wb_console_ack   = 1'b0;
	assign	wb_console_err   = (wb_console_stb);
	assign	wb_console_stall = 0;
	assign	wb_console_idata = 0;

	assign	uarttxf_int = 1'b0;	// console.INT.UARTTXF.WIRE
	assign	uartrxf_int = 1'b0;	// console.INT.UARTRXF.WIRE
	assign	uartrx_int = 1'b0;	// console.INT.UARTRX.WIRE
	assign	uarttx_int = 1'b0;	// console.INT.UARTTX.WIRE
`endif	// BUSCONSOLE_ACCESS

`ifdef	WBUBUS_MASTER
	// Parallel port logic
	pport	hbi_pp(i_clk,
			pp_rx_stb, pp_rx_data,
			pp_tx_stb, pp_tx_data, pp_tx_busy,
			i_pp_dir, i_pp_clk, i_pp_data, o_pp_data,
				o_pp_clkfb, o_pp_dbg);
`ifndef	BUSPIC_ACCESS
	wire	w_bus_int;
	assign	w_bus_int = 1'b0;
`endif
	wire	[29:0]	hb_tmp_addr;
	hbconsole genbus(i_clk, pp_rx_stb, pp_rx_data,
			hb_hb_cyc, hb_hb_stb, hb_hb_we, hb_tmp_addr, hb_hb_data, hb_hb_sel,
			hb_hb_stall, hb_hb_ack, hb_hb_err, hb_hb_idata,
			w_bus_int,
			pp_tx_stb, pp_tx_data, pp_tx_busy,
			//
			w_console_tx_stb, w_console_tx_data, w_console_busy,
			w_console_rx_stb, w_console_rx_data);
	assign	hb_hb_addr= hb_tmp_addr[(25-1):0];
`else	// WBUBUS_MASTER
`endif	// WBUBUS_MASTER

	always @(posedge i_clk)
		cpu_reset <= (|cpu_reset_bus);
	always @(posedge i_clk)
	if (wb_zip_err)
	begin
		r_buserr_addr <= 0;
		r_buserr_addr[24-1:0] <= wb_zip_addr[24-1:0];
	end else if (hb_hb_err)
	begin
		r_buserr_addr <= 0;
		r_buserr_addr[25-1:0] <= hb_hb_addr[25-1:0];
	end
	assign	wb_buserr_stall= 1'b0;
	assign	wb_buserr_ack  = wb_buserr_stb;
	assign	wb_buserr_idata = { {(30-25){1'b0}},
			r_buserr_addr, 2'b00 };
`ifdef	WATCHDOG_ACCESS
	ziptimer #(.VW(16), .RELOADABLE(0))
		watchdogi(i_clk, i_reset, 1'b1,
			wb_watchdog_cyc, wb_watchdog_stb, wb_watchdog_we,
			wb_watchdog_data, // 32 bits wide
			wb_watchdog_sel,  // 32/8 bits wide
		wb_watchdog_stall, wb_watchdog_ack, wb_watchdog_idata,
			watchdog_reset);

	assign	design_reset = i_reset;
`else	// WATCHDOG_ACCESS

	//
	// In the case that there is no wb_watchdog peripheral
	// responding on the wb bus
	assign	wb_watchdog_ack   = 1'b0;
	assign	wb_watchdog_err   = (wb_watchdog_stb);
	assign	wb_watchdog_stall = 0;
	assign	wb_watchdog_idata = 0;

	assign	design_reset = 1'b0;	// watchdog.INT.RESET.WIRE
	assign	watchdog_reset = 1'b0;	// watchdog.INT.WATCHDOG.WIRE
`endif	// WATCHDOG_ACCESS

`ifdef	INCLUDE_ZIPCPU
	//
	//
	// The ZipCPU/ZipSystem BUS master
	//
	//
	zipbones #(.RESET_ADDRESS(RESET_ADDRESS),.ADDRESS_WIDTH(ZIP_ADDRESS_WIDTH),
			.START_HALTED(ZIP_START_HALTED))
		swic(i_clk, (cpu_reset),
			// Zippys wishbone interface
			wb_zip_cyc, wb_zip_stb, wb_zip_we,
			wb_zip_addr[24-1:0],
			wb_zip_data, // 32 bits wide
			wb_zip_sel,  // 32/8 bits wide
		wb_zip_stall, wb_zip_ack, wb_zip_idata,wb_zip_err,
			// zip_cyc, zip_stb, zip_we, zip_addr, zip_data, zip_sel,
			//		zip_ack, zip_stall, zip_idata, zip_err,
			w_bus_int, zip_cpu_int,
			// Debug wishbone interface
			hb_zip_cyc, hb_zip_stb, hb_zip_we,
			hb_zip_addr[1-1:0],
			hb_zip_data, // 32 bits wide
			hb_zip_sel,  // 32/8 bits wide
		hb_zip_stall, hb_zip_ack, hb_zip_idata,
			zip_debug);
	assign	zip_trigger = zip_debug[31];
`else	// INCLUDE_ZIPCPU

	//
	// In the case that there is no hb_zip peripheral
	// responding on the hb bus
	assign	hb_zip_ack   = 1'b0;
	assign	hb_zip_err   = (hb_zip_stb);
	assign	hb_zip_stall = 0;
	assign	hb_zip_idata = 0;

	assign	zip_cpu_int = 1'b0;	// zip.INT.ZIP.WIRE
`endif	// INCLUDE_ZIPCPU



endmodule // main.v
