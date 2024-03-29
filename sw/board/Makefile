################################################################################
##
## Filename:	sw/board/Makefile
##
## Project:	ZBasic, a generic toplevel impl using the full ZipCPU
##
## Purpose:	
##
## Creator:	Dan Gisselquist, Ph.D.
##		Gisselquist Technology, LLC
##
################################################################################
##
## Copyright (C) 2015-2016, Gisselquist Technology, LLC
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
PROGRAMS := cputest hello jpeg 
all:	$(PROGRAMS)
#
#
CC	:=zip-gcc
AS	:=zip-as
LD	:=zip-ld
NM	:=zip-nm
OBJDIR	:= obj-zip
RDELF	:= zip-readelf
OBJDUMP := zip-objdump
SOURCES := cputest.c hello.c jpeg.c lifting.c rd_bytes.c
HEADERS := $(foreach hdr,$(subst .c,.o,$(SOURCES)),$(wildcard $(hdr))) board.h
LDSCRIPT:= -Tboard.ld
LFLAGS  := $(LDSCRIPT) -L../zlib
INCS    := -I../zlib -I../../rtl/catzip -I.
CFLAGS  := -O3 $(INCS)
LIBS    := -lc -lcatzip
INSTALLD:=/home/pi/zipcpu/sw/install
NLIBD	:=$(INSTALLD)/cross-tools/zip/lib
ZLIBD	:=../zlib
LIB	:= $(NLIBD)/libg.a $(NLIBD)/libc.a
#
# For source analysis, the following macros are defined:

%.o: $(OBJDIR)/%.o
$(OBJDIR)/%.o: %.c
	$(mk-objdir)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJDIR)/%.s: %.c
	$(mk-objdir)
	$(CC) $(CFLAGS) $(DUMPRTL) -S $< -o $@
$(OBJDIR)/%.txt: $(OBJDIR)/%.o
	$(mk-objdir)
	bash -c "$(RDELF) -a $^ ; $(OBJDUMP) -S -D $^ " | tee $@
%.txt: %
	$(OBJDUMP) -S -D $^ > $@


#
# The CPUTest program here is special--it doesn't use the C library.  Hence,
# it must have the -fno-builtin flag in order to build, and the -Tartyram.ld
# linker script to build something that doesn't go into flash but directly into
# RAM instead.
#
$(OBJDIR)/cputest.o: cputest.c
	$(CC) $(CFLAGS) -c -Wa,-nocis -fno-builtin $< -o $@
$(OBJDIR)/cputestcis.o: cputest.c
	$(CC) $(CFLAGS) -c -Wa,-cis -fno-builtin $< -o $@
$(OBJDIR)/cputest.s: cputest.c
	$(CC) $(CFLAGS) -S -Wa,-cis -fno-builtin $< -o $@

cputest: $(OBJDIR)/cputest.o boardram.ld
	$(CC) $(CFLAGS) -T boardram.ld -fno-builtin -Wl,-Map=$(OBJDIR)/cputest.map $(OBJDIR)/cputest.o -o $@
cputestcis: $(OBJDIR)/cputestcis.o boardram.ld
	$(CC) $(CFLAGS) -T boardram.ld -fno-builtin -Wl,-Map=$(OBJDIR)/cputestcis.map $(OBJDIR)/cputestcis.o -o $@
$(OBJDIR)/lifting.o: lifting.c
	$(CC) -O3 -c  $< -o $@
	
$(OBJDIR)/hello.o: hello.c
	$(CC) -O3 -c  $< -o $@
$(OBJDIR)/jpeg.o: jpeg.c
	$(CC) $(CFLAGS) -c  $< -o $@

$(OBJDIR)/gettysburg.o: gettysburg.c
	$(CC) -O3 -c $< -o $@

hello: $(OBJDIR)/hello.o boardram.ld
	$(CC) $(CFLAGS) $(LFLAGS) -Wl,-Map=$(OBJDIR)/hello.map $< $(LIBS) -o $@

jpeg: $(OBJDIR)/jpeg.o $(OBJDIR)/lifting.o  boardram.ld
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJDIR)/lifting.o  -Wl,-Map=$(OBJDIR)/jpeg.map $< $(LIBS) -o $@ -lgcc


define	mk-objdir
	@bash -c "if [ ! -e $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi"
endef

define	build-depends
	@echo "Building dependency file(s)"
	$(mk-objdir)
	@$(CC) $(CFLAGS) -MM $(SOURCES) > $(OBJDIR)/xdepends.txt
	@sed -e 's/^.*.o: /$(OBJDIR)\/&/' < $(OBJDIR)/xdepends.txt > $(OBJDIR)/depends.txt
	@rm $(OBJDIR)/xdepends.txt
endef

tags: $(SOURCES) $(HEADERS)
	@echo "Generating tags"
	@ctags $(SOURCES) $(HEADERS)

.PHONY: depends
depends: tags
	$(build-depends)

$(OBJDIR)/depends.txt: $(SOURCES) $(HEADERS)
	$(build-depends)

.PHONY: clean
clean:
	rm -f $(PROGRAMS)
	rm -rf $(addsuffix .map,$(PROGRAMS))
	rm -rf $(addsuffix .txt,$(PROGRAMS))
	rm -rf $(OBJDIR)/

-include $(OBJDIR)/depends.txt
