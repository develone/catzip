////////////////////////////////////////////////////////////////////////////////
//
// Filename:	bregs.cpp
//
// Project:	ICO Zip, iCE40 ZipCPU demonsrtation project
//
// Purpose:	
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
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "bregs.h"

const	REGNAME	raw_bregs[] = {
	{ R_VERSION       ,	"VERSION" 	},
	{ R_BUSERR        ,	"BUSERR"  	},
	{ R_PWRCOUNT      ,	"PWRCOUNT"	},
	{ R_INT		  ,	"int"		},
	// { R_HALT	  ,	"halt"		},
	{ R_DEBOUNCED	  ,	"DEBOUNCED"	},
	{ R_TRANSITIONS	  ,	"BOUNCES"	},
	{ R_TRANSITIONS	  ,	"TRANSITIONS"	},
	{ R_MAXCLOCKS	  ,	"DURATION"	},
	{ R_MAXCLOCKS	  ,	"MAXCLOCKS"	},
	{ R_SCOPE         ,	"SCOPE"   	},
	{ R_SCOPD         ,	"SCOPD"   	},
	{ R_RSTCOUNTER    ,	"RESET"     	}
};

#define	RAW_NREGS	(sizeof(raw_bregs)/sizeof(bregs[0]))

const	REGNAME		*bregs = raw_bregs;
const	int	NREGS = RAW_NREGS;

unsigned	addrdecode(const char *v) {
	if (isalpha(v[0])) {
		for(int i=0; i<NREGS; i++)
			if (strcasecmp(v, bregs[i].m_name)==0)
				return bregs[i].m_addr;
		fprintf(stderr, "Unknown register: %s\n", v);
		exit(-2);
	} else
		return strtoul(v, NULL, 0);
}

const	char *addrname(const unsigned v) {
	for(int i=0; i<NREGS; i++)
		if (bregs[i].m_addr == v)
			return bregs[i].m_name;
	return NULL;
}

