################################################################################
##
## Filename:	Makefile
##
## Project:	CAT Zip, iCE40 ZipCPU demonsrtation project
##
## Purpose:	Simply coordinates builds in the various subdirectories of
##		rtl.
##
##
## Creator:	Dan Gisselquist, Ph.D.
##		Gisselquist Technology, LLC
##
################################################################################
##
## Copyright (C) 2016-2018, Gisselquist Technology, LLC
##
## This program is free software (firmware): you can redistribute it and/or
## modify it under the terms of  the GNU General Public License as published
## by the Free Software Foundation, either version 3 of the License, or (at
## your option) any later version.
##
## This program is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
## FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
## for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program.  (It's in the $(ROOT)/doc directory.  Run make with no
## target there if the PDF file isn't present.)  If not, see
## <http://www.gnu.org/licenses/> for a copy.
##
## License:	GPL, v3, as defined and found on www.gnu.org,
##		http://www.gnu.org/licenses/gpl.html
##
##
################################################################################
##
##
.PHONY: all
#all:	basic uart catzip  leddigits switch_leds pptest
all:	basic uart catzip  leddigits switch_leds
# all:	verilated sw bench bit
SUBMAKE := $(MAKE) --no-print-directory -C
#
.PHONY: basic
basic:
	$(SUBMAKE) basic

.PHONY: uart
uart:
	$(SUBMAKE) uart

.PHONY: leddigits
leddigits:
	$(SUBMAKE) leddigits

.PHONY: switch_leds
switch_leds:
	$(SUBMAKE) switch_leds
	
.PHONY: pptest
pptest:
	$(SUBMAKE) pptest

.PHONY: catzip
catzip:
	$(SUBMAKE) catzip


.PHONY: clean
clean:	clean-basic clean-uart clean-pptest clean-pmodleds clean-catzip clean-leddigits clean-switch_leds

.PHONY: clean-basic
clean-basic:
	$(SUBMAKE) basic clean

.PHONY: clean-uart
clean-uart:
	$(SUBMAKE) uart clean

.PHONY: clean-pptest
clean-pptest:
	$(SUBMAKE) pptest clean

.PHONY: clean-leddigits
clean-pmodleds:
	$(SUBMAKE) leddigits clean

.PHONY: clean-catzip
clean-catzip:
	$(SUBMAKE) catzip clean

.PHONY: clean-leddigits
clean-leddigits:
	$(SUBMAKE) leddigits clean
	
.PHONY: clean-switch_leds
clean-switch_leds:
	$(SUBMAKE) switch_leds clean
