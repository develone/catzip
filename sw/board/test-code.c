/*
cp test-code.c jpeg.c

make clean; make

zip-objdump -d jpeg > jpeg-disasm.txt

02004ce4 <ptrs>:

./arm-main_tb 
Listening on port 8363
Listening on port 8364
> T
CMD: Only sent 0 bytes of 3!

./arm-zipload -v ../board/jpeg
Halting the CPU
Memory regions:
	Block RAM: 01400000 - 01402000
	SDRAM       : 02000000 - 03000000
Loading: ../board/jpeg
Section 0: 02000000 - 02004d50
Writing to MEM: 02000000-02004d54
Clearing the CPUs registers
Setting PC to 02000000
The CPU should be fully loaded, you may now
start it (from reset/reboot) with:
> wbregs cpu 0x0f

CPU Status is: 0000060f

 ./arm-wbregs cpu 0x0f
04000000 (     CPU)-> 0000000f


*/
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "lifting.h"
#define BLKRAM_FLAG 0x01401000
#define BLKRAM_INVFWD 0x01401004

struct PTRs {
	
	int w; 
	int h;  					
	 
	 int *red; 
	
	 int *grn;  						 
	 int *blu;  
	 int *alt;  
	 int *ptr_blkram_flag;  
	 int *ptr_blkram_invfwd;
	 int *buf_red;
	 int *fwd_inv;
	 int flag;
	 int inpbuf[65536];	  

} ptrs;

int main(int argc, char **argv) {
	ptrs.w = 256;
	ptrs.h = 256;
	ptrs.ptr_blkram_flag = (int *)BLKRAM_FLAG; 
	ptrs.ptr_blkram_invfwd = (int *)BLKRAM_INVFWD;  
	ptrs.buf_red = ( int *)malloc(sizeof( int)* ptrs.w*ptrs.h*2);
	
	ptrs.fwd_inv = (int *)malloc(sizeof( int)*1);
	
	ptrs.flag = ptrs.ptr_blkram_flag[0];
	ptrs.fwd_inv = ptrs.ptr_blkram_invfwd;
	
	ptrs.red = &ptrs.inpbuf[0];
	free(ptrs.buf_red);
	free(ptrs.fwd_inv);
	while(1);
	return 0;
}
