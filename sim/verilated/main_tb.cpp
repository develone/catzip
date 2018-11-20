////////////////////////////////////////////////////////////////////////////////
//
// Filename:	./main_tb.cpp
//
// Project:	ICO Zip, iCE40 ZipCPU demonstration project
//
// DO NOT EDIT THIS FILE!
// Computer Generated: This file is computer generated by AUTOFPGA. DO NOT EDIT.
// DO NOT EDIT THIS FILE!
//
// CmdLine:	autofpga autofpga -o . global.txt bkram.txt buserr.txt clock50.txt pic.txt pwrcount.txt version.txt hbconsole.txt gpio.txt dlyarbiter.txt zipbones.txt sdramdev.txt sdramscope.txt
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
//
// SIM.INCLUDE
//
// Any SIM.INCLUDE tags you define will be pasted here.
// This is useful for guaranteeing any include functions
// your simulation needs are called.
//
// Looking for string: SIM.INCLUDE
#include "verilated.h"
#include "Vmain.h"
#define	BASECLASS	Vmain

#include "design.h"
#include "regdefs.h"
#include "testb.h"
#include "sdramsim.h"
#include "zipelf.h"

#include "byteswap.h"
#include "port.h"
#include "pportsim.h"
//
// SIM.DEFINES
//
// This tag is useful fr pasting in any #define values that
// might then control the simulation following.
//
// Looking for string: SIM.DEFINES
#ifndef	VVAR
#ifdef	NEW_VERILATOR
#define	VVAR(A)	main__DOT_ ## A
#else
#define	VVAR(A)	v__DOT_ ## A
#endif
#endif

#define	CPUVAR(A)	VVAR(_swic__DOT__thecpu__DOT_ ## A)
#define	cpu_break 	VVAR(_swic__DOT__cpu_break)
#define	cpu_cmd_halt	VVAR(_swic__DOT__cmd_halt)
#define	cpu_reset	VVAR(_swic__DOT__cmd_reset)
#define	cpu_ipc		VVAR(_swic__DOT__thecpu__DOT__ipc)
#define	cpu_upc		CPUVAR(_SET_USER_PC__DOT__r_upc)
#define	cpu_gie		CPUVAR(_SET_GIE__DOT__r_gie)
#define	cpu_iflags	CPUVAR(_w_iflags)
#define	cpu_uflags	CPUVAR(_w_uflags)
#define	cpu_regs	CPUVAR(_regset)
#define	cpu_cmd_addr	VVAR(_swic__DOT__cmd_addr)
#define	cpu_bus_err	CPUVAR(_bus_err)
#define	cpu_ibus_err	CPUVAR(_ibus_err_flag)
#define	cpu_ubus_err	CPUVAR(_r_ubus_err_flag)
#define	cpu_mem_rdaddr	CPUVAR(_swic__DOT__thecpu__DOT__domem__DOT__rdaddr)
#define	cpu_mem_wraddr	VVAR(_swic__DOT__thecpu__DOT__domem__DOT__wraddr)
#define	cpu_op_valid	VVAR(_swic__DOT__thecpu__DOT__op_valid)
#define	cpu_alu_ce	CPUVAR(_alu_ce)
#define	cpu_new_pc	CPUVAR(_new_pc)
#define	cpu_op_sim	CPUVAR(_op_sim)
#define	cpu_sim_immv	CPUVAR(_op_sim_immv)

#define	block_ram	VVAR(_bkrami__DOT__mem)
class	MAINTB : public TESTB<Vmain> {
public:
		// SIM.DEFNS
		//
		// If you have any simulation components, create a
		// SIM.DEFNS tag to have those components defined here
		// as part of the main_tb.cpp function.
// Looking for string: SIM.DEFNS
#ifdef	SDRAM_ACCESS

	SDRAMSIM		*m_sdram;
	
#endif // SDRAM_ACCESS
	int	m_cpu_bombed;
	PPORTSIM	*m_hb;
	MAINTB(void) {
		// SIM.INIT
		//
		// If your simulation components need to be initialized,
		// create a SIM.INIT tag.  That tag's value will be pasted
		// here.
		//
		// From sdram
#ifdef	SDRAM_ACCESS

	m_sdram = new SDRAMSIM;
	
#endif // SDRAM_ACCESS
		// From zip
		m_cpu_bombed = 0;
		// From hb
		m_hb = new PPORTSIM(FPGAPORT, true);
	}

	void	reset(void) {
		// SIM.SETRESET
		// If your simulation component needs logic before the
		// tick with reset set, that logic can be placed into
		// the SIM.SETRESET tag and thus pasted here.
		//
// Looking for string: SIM.SETRESET
		m_core->i_gpio |= 1;
		TESTB<Vmain>::reset();
		// SIM.CLRRESET
		// If your simulation component needs logic following the
		// reset tick, that logic can be placed into the
		// SIM.CLRRESET tag and thus pasted here.
		//
// Looking for string: SIM.CLRRESET
		m_core->i_gpio &= ~1;
	}

	void	trace(const char *vcd_trace_file_name) {
		fprintf(stderr, "Opening TRACE(%s)\n",
				vcd_trace_file_name);
		opentrace(vcd_trace_file_name);
		m_time_ps = 0;
	}

	void	close(void) {
		m_done = true;
	}

	void	tick(void) {
		if (done())
			return;
		TESTB<Vmain>::tick(); // Clock.size = 1
	}


	// Evaluating clock clk

	// sim_clk_tick() will be called from TESTB<Vmain>::tick()
	//   following any falling edge of clock clk
	virtual	void	sim_clk_tick(void) {
		// Default clock tick
		//
		// SIM.TICK tags go here for SIM.CLOCK=clk
		//
		// SIM.TICK from sdram
#ifdef	SDRAM_ACCESS

	m_core->i_ram_data = (*m_sdram)(1,m_core->o_ram_cke,
	m_core->o_ram_cs_n,m_core->o_ram_ras_n,m_core->o_ram_cas_n,
	m_core->o_ram_we_n,m_core->o_ram_bs,m_core->o_ram_addr,
	m_core->ram_drive_data,m_core->o_ram_data,m_core->o_ram_dqm);
	
#endif // SDRAM_ACCESS		
		// SIM.TICK from zip
#ifdef	INCLUDE_ZIPCPU
		// ZipCPU Sim instruction support
		if ((m_core->cpu_op_sim)
			&&(m_core->cpu_op_valid)
			&&(m_core->cpu_alu_ce)
			&&(!m_core->cpu_new_pc)) {
			//
			execsim(m_core->cpu_sim_immv);
		}

		if (m_core->cpu_break) {
			printf("\n\nBOMB : CPU BREAK RECEIVED\n");
			m_cpu_bombed++;
			dump(m_core->cpu_regs);
		} else if (m_cpu_bombed) {
			if (m_cpu_bombed++ > 12)
				m_done = true;
		}
#endif	// INCLUDE_ZIPCPU

		// SIM.TICK from hb
		int	pp_clk = m_core->i_pp_clk,
			pp_dir = m_core->i_pp_dir;
		m_core->i_pp_data = (*m_hb)(
			pp_clk, pp_dir, m_core->o_pp_data,
			m_core->o_pp_clkfb);
		m_core->i_pp_clk = pp_clk;
		m_core->i_pp_dir = pp_dir;
	}
	inline	void	tick_clk(void) {	tick();	}

	//
	// The load function
	//
	// This function is required by designs that need the flash or memory
	// set prior to run time.  The test harness should be able to call
	// this function to load values into any (memory-type) location
	// on the bus.
	//
	bool	load(uint32_t addr, const char *buf, uint32_t len) {
		uint32_t	start, offset, wlen, base, naddr;

		//
		// Loading the sdram component
		//
		base  = 0x02000000;
		naddr = 0x00800000;

		if ((addr >= base)&&(addr < base + naddr)) {
			// If the start access is in sdram
			start = (addr > base) ? (addr-base) : 0;
			offset = (start + base) - addr;
			wlen = (len-offset > naddr - start)
				? (naddr - start) : len - offset;
#ifdef	SDRAM_ACCESS
			// FROM sdram.SIM.LOAD
#ifdef	SDRAM_ACCESS

	m_sdram->load(start, &buf[offset], wlen);
	
#endif // SDRAM_ACCESS
			// AUTOFPGA::Now clean up anything else
			// Was there more to write than we wrote?
			if (addr + len > base + naddr)
				return load(base + naddr, &buf[offset+wlen], len-wlen);
			return true;
#else	// SDRAM_ACCESS
			return false;
#endif	// SDRAM_ACCESS
		//
		// End of components with a SIM.LOAD tag, and a
		// non-zero number of addresses (NADDR)
		//
		}

		//
		// Loading the bkram component
		//
		base  = 0x01400000;
		naddr = 0x00000040;

		if ((addr >= base)&&(addr < base + naddr)) {
			// If the start access is in bkram
			start = (addr > base) ? (addr-base) : 0;
			offset = (start + base) - addr;
			wlen = (len-offset > naddr - start)
				? (naddr - start) : len - offset;
#ifdef	BKRAM_ACCESS
			// FROM bkram.SIM.LOAD
			start = start & (-4);
			wlen = (wlen+3)&(-4);

			// Need to byte swap data to get it into the memory
			char	*bswapd = new char[len+8];
			memcpy(bswapd, &buf[offset], wlen);
			byteswapbuf(len>>2, (uint32_t *)bswapd);
			memcpy(&m_core->block_ram[start], bswapd, wlen);
			delete	bswapd;
			// AUTOFPGA::Now clean up anything else
			// Was there more to write than we wrote?
			if (addr + len > base + naddr)
				return load(base + naddr, &buf[offset+wlen], len-wlen);
			return true;
#else	// BKRAM_ACCESS
			return false;
#endif	// BKRAM_ACCESS
		//
		// End of components with a SIM.LOAD tag, and a
		// non-zero number of addresses (NADDR)
		//
		}

		return false;
	}

	//
	// KYSIM.METHODS
	//
	// If your simulation code will need to call any of its own function
	// define this tag by those functions (or other sim code), and
	// it will be pasated here.
	//
// Looking for string: SIM.METHODS
#ifdef	INCLUDE_ZIPCPU
	void	loadelf(const char *elfname) {
		ELFSECTION	**secpp, *secp;
		uint32_t	entry;

		elfread(elfname, entry, secpp);

		for(int s=0; secpp[s]->m_len; s++) {
			secp = secpp[s];

			load(secp->m_start, secp->m_data, secp->m_len);
		} free(secpp);
	}


	bool	gie(void) {
		return (m_core->cpu_gie);
	}

	void dump(const uint32_t *regp) {
		uint32_t	uccv, iccv;
		fflush(stderr);
		fflush(stdout);
		printf("ZIPM--DUMP: ");
		if (gie())
			printf("Interrupts-enabled\n");
		else
			printf("Supervisor mode\n");
		printf("\n");

		iccv = m_core->cpu_iflags;
		uccv = m_core->cpu_uflags;

		printf("sR0 : %08x ", regp[0]);
		printf("sR1 : %08x ", regp[1]);
		printf("sR2 : %08x ", regp[2]);
		printf("sR3 : %08x\n",regp[3]);
		printf("sR4 : %08x ", regp[4]);
		printf("sR5 : %08x ", regp[5]);
		printf("sR6 : %08x ", regp[6]);
		printf("sR7 : %08x\n",regp[7]);
		printf("sR8 : %08x ", regp[8]);
		printf("sR9 : %08x ", regp[9]);
		printf("sR10: %08x ", regp[10]);
		printf("sR11: %08x\n",regp[11]);
		printf("sR12: %08x ", regp[12]);
		printf("sSP : %08x ", regp[13]);
		printf("sCC : %08x ", iccv);
		printf("sPC : %08x\n",regp[15]);

		printf("\n");

		printf("uR0 : %08x ", regp[16]);
		printf("uR1 : %08x ", regp[17]);
		printf("uR2 : %08x ", regp[18]);
		printf("uR3 : %08x\n",regp[19]);
		printf("uR4 : %08x ", regp[20]);
		printf("uR5 : %08x ", regp[21]);
		printf("uR6 : %08x ", regp[22]);
		printf("uR7 : %08x\n",regp[23]);
		printf("uR8 : %08x ", regp[24]);
		printf("uR9 : %08x ", regp[25]);
		printf("uR10: %08x ", regp[26]);
		printf("uR11: %08x\n",regp[27]);
		printf("uR12: %08x ", regp[28]);
		printf("uSP : %08x ", regp[29]);
		printf("uCC : %08x ", uccv);
		printf("uPC : %08x\n",regp[31]);
		printf("\n");
		fflush(stderr);
		fflush(stdout);
	}


	void	execsim(const uint32_t imm) {
		uint32_t	*regp = m_core->cpu_regs;
		int		rbase;
		rbase = (gie())?16:0;

		fflush(stdout);
		if ((imm & 0x03fffff)==0)
			return;
		// fprintf(stderr, "SIM-INSN(0x%08x)\n", imm);
		if ((imm & 0x0fffff)==0x00100) {
			// SIM Exit(0)
			close();
			exit(0);
		} else if ((imm & 0x0ffff0)==0x00310) {
			// SIM Exit(User-Reg)
			int	rcode;
			rcode = regp[(imm&0x0f)+16] & 0x0ff;
			close();
			exit(rcode);
		} else if ((imm & 0x0ffff0)==0x00300) {
			// SIM Exit(Reg)
			int	rcode;
			rcode = regp[(imm&0x0f)+rbase] & 0x0ff;
			close();
			exit(rcode);
		} else if ((imm & 0x0fff00)==0x00100) {
			// SIM Exit(Imm)
			int	rcode;
			rcode = imm & 0x0ff;
			close();
			exit(rcode);
		} else if ((imm & 0x0fffff)==0x002ff) {
			// Full/unconditional dump
			printf("SIM-DUMP\n");
			dump(regp);
		} else if ((imm & 0x0ffff0)==0x00200) {
			// Dump a register
			int rid = (imm&0x0f)+rbase;
			printf("%8lu @%08x R[%2d] = 0x%08x\n", m_time_ps/1000,
			m_core->cpu_ipc, rid, regp[rid]);
		} else if ((imm & 0x0ffff0)==0x00210) {
			// Dump a user register
			int rid = (imm&0x0f);
			printf("%8lu @%08x uR[%2d] = 0x%08x\n", m_time_ps/1000,
				m_core->cpu_ipc,
				rid, regp[rid+16]);
		} else if ((imm & 0x0ffff0)==0x00230) {
			// SOUT[User Reg]
			int rid = (imm&0x0f)+16;
			printf("%c", regp[rid]&0x0ff);
		} else if ((imm & 0x0fffe0)==0x00220) {
			// SOUT[User Reg]
			int rid = (imm&0x0f)+rbase;
			printf("%c", regp[rid]&0x0ff);
		} else if ((imm & 0x0fff00)==0x00400) {
			// SOUT[Imm]
			printf("%c", imm&0x0ff);
		} else { // if ((insn & 0x0f7c00000)==0x77800000)
			uint32_t	immv = imm & 0x03fffff;
			// Simm instruction that we dont recognize
			// if (imm)
			// printf("SIM 0x%08x\n", immv);
			printf("SIM 0x%08x (ipc = %08x, upc = %08x)\n", immv,
				m_core->cpu_ipc,
				m_core->cpu_upc);
		} fflush(stdout);
	}
#endif


};
