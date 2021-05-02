/*
cp test-code.c jpeg.c

make clean; make

zip-objdump -d jpeg > jpeg-disasm.txt

02002354 <ptrs>:

./arm-main_tb 
Listening on port 8363
Listening on port 8364
> T
CMD: Only sent 0 bytes of 3!

01401000 (        )-> 00000002
01401004 (        )-> 00000001
Halting the CPU
Memory regions:
	Block RAM: 01400000 - 01402000
	SDRAM       : 02000000 - 03000000
Loading: ../board/jpeg
Section 0: 02000000 - 020823cc
Writing to MEM: 02000000-020823cc
Clearing the CPUs registers
Setting PC to 02000000
The CPU should be fully loaded, you may now		65536	262144	40000
start it (from reset/reboot) with:
> wbregs cpu 0x0f

CPU Status is: 0000060f
The size of the buffer is 0x010000 or 65536 words

READ-COMPLETE
04000000 (     CPU)-> 0000000f
inpbuf
02002354 (        ) : [....] 000000e2
altbuf
02042354 (        ) : [....] 00000000
w
02082354 (        ) : [....] 00000100
h
02082358 (        ) : [....] 00000100
*red
0208235c (        ) : [..#.] 020823d8		ptrs.red = ptrs.buf_red;
*grn
02082360 (        ) : [....] 00000000
*blu
02082364 (        ) : [....] 00000000
*alt
02082368 (        ) : [..#.] 020c23e0
*ptr_blkram_flag
0208236c (        ) : [.@..] 01401000
*ptr_blkram_invfwd
02082370 (        ) : [.@..] 01401004
buf_red
02082374 (        ) : [..#.] 020823d8
ptr to fwd_inv
02082378 (        ) : [.@..] 01401004
flag
0208237c (        ) : [....] 00000002
*inbuf
02082390 (        ) : [....] 00000000
01401004 (        ) : [....] 00000001


20000000	prog-start

0200f13c 	<heap>

0200f144 	<ptrs>
02002354	
			16K 
02042354
			16K
02082354

020823cc	prog-end
BOMB : CPU BREAK RECEIVED
ZIPM--DUMP: Supervisor mode

sR0 : 02001024 sR1 : 00000002 sR2 : 01401004 sR3 : 00000002
sR4 : 01400ffc sR5 : 02002294 sR6 : 01400ffe sR7 : 02001e5c
sR8 : 01401004 sR9 : 00000000 sR10: 00000000 sR11: 00000000
sR12: 00000000 sSP : 02ffffd4 sCC : 00000000 sPC : 02001034

uR0 : 00000000 uR1 : 00000000 uR2 : 00000000 uR3 : 00000000
uR4 : 00000000 uR5 : 00000000 uR6 : 00000000 uR7 : 00000000
uR8 : 00000000 uR9 : 00000000 uR10: 00000000 uR11: 00000000
uR12: 00000000 uSP : 00000000 uCC : 00000020 uPC : 02000030

devel@mypi3-16:~/testbuilds/addr23/catzip/sw/host $ ./test-exe.sh 
01401000 (        )-> 00000002
01401004 (        )-> 00000001
Halting the CPU
Memory regions:
	Block RAM: 01400000 - 01402000
	SDRAM       : 02000000 - 03000000
Loading: ../board/jpeg
Section 0: 02000000 - 0208230c
Writing to MEM: 02000000-0208230c
Clearing the CPUs registers
Setting PC to 02000000
The CPU should be fully loaded, you may now
start it (from reset/reboot) with:
> wbregs cpu 0x0f

CPU Status is: 0000060f
The size of the buffer is 0x010000 or 65536 words

READ-COMPLETE
04000000 (     CPU)-> 0000000f
inpbuf
02002368 (        ) : [....] 000000e0
altbuf
02042368 (        ) : [....] 00000000
w
02082368 (        ) : [....] 00000000
h
0208236c (        ) : [....] 00000000
*red
02082370 (        ) : [....] 00000000
*grn
02082374 (        ) : [....] 00000000
*blu
02082378 (        ) : [....] 00000000
*alt
0208237c (        ) : [....] 00000000
*ptr_blkram_flag
02082380 (        ) : [....] 00000000
*ptr_blkram_invfwd
02082364 (        ) : [....] 00000000
*buf_red
02082388 (        ) : [....] 00000000
ptr to fwd_inv
0208238c (        ) : [....] 00000000
flag
02082390 (        ) : [....] 00000000
*inbuf
02082394 (        ) : [....] 00000000
01401004 (        ) : [....] 00000001
	

*/
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "lifting.h"
#define BLKRAM_FLAG 0x01401000
#define BLKRAM_INVFWD 0x01401004
#define	zip_break()		asm("BREAK\n")
struct PTRs {
	
	int inpbuf[65536];
	int altbuf[65536];	
	int w; 
	int h;  					
	 
	 int *red; 
	
	 int grn;  						 
	 int *blu;  
	 int *alt;  
	 int *ptr_blkram_flag;  
	 int *ptr_blkram_invfwd;
	 int *buf_red;
	 int *fwd_inv;
	 int flag;
	 int *inbuf;
	   
	

} ptrs;

int main(int argc, char **argv) {
	ptrs.w = 256;
	ptrs.h = 256;
	ptrs.ptr_blkram_flag = (int *)BLKRAM_FLAG; 
	ptrs.ptr_blkram_invfwd = (int *)BLKRAM_INVFWD; 
	
	/*Allocating memory for 2 images 256x256 */ 
	ptrs.buf_red = ( int *)malloc(sizeof( int)* ptrs.w*ptrs.h);
	
	ptrs.inbuf = &ptrs.inpbuf[0];
	
	ptrs.fwd_inv = (int *)malloc(sizeof( int)*1);
	
	ptrs.flag = ptrs.ptr_blkram_flag[0];
	ptrs.fwd_inv = ptrs.ptr_blkram_invfwd;
	
	ptrs.red = &ptrs.inpbuf[0];
	
	/*Setting ptr.alt to 2nd img size*/ 
	
	ptrs.alt = ( int *)malloc(sizeof( int)* ptrs.w*ptrs.h);
	
	/*calling lifting which performs the dwt on the image*/
	//ptrs.red = ptrs.buf_red;
	
	lifting(ptrs.w,&ptrs.inpbuf[0],ptrs.alt,ptrs.fwd_inv);
	
	free(ptrs.buf_red);
	free(ptrs.fwd_inv);
	free(ptrs.alt);
	while(1);
	return 0;
}
