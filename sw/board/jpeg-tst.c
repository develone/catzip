/*
 * 
With a change in bkram & sdram
from
	   bkram(wx) : ORIGIN = 0x00A00000, LENGTH = 0x00002000
	   sdram(wx) : ORIGIN = 0x01000000, LENGTH = 0x01000000
to
	   bkram(wx) : ORIGIN = 0x01400000, LENGTH = 0x00002000
	   sdram(wx) : ORIGIN = 0x02000000, LENGTH = 0x01000000
	   
Files that are dependent on above change are sw/board/jpeg.c, sw/board/boardram.ld,
sw/host/wrsdram.cpp, and sw/host/rdsdram.cpp

Note:
Without a break point in jpeg.c 0x0200f144 <ptrs>: in jpeg-disasm.txt 
With a break point in jpeg.c 0x0200f148 <ptrs>: jpeg-disasm.txt.
This change requires changes in sw/host/wrsdram.cpp, and sw/host/rdsdram.cpp.

./arm-wbregs 0x0200f148					inpbuf
0200f148 (        ) : [."$|] 0e22247c value read from rgb_pack.bin 

./arm-wbregs 0x0201f148
0201f148 (        ) : [...E] 0a00d845	flag


./arm-wbregs 0x0201f14c
0201f14c (        ) : [.@.L] 0a40f04c	w

 ./arm-wbregs 0x0201f150
0201f150 (        ) : [.P.N] 0a50fc4e	h

start of inpbuf	with zip_break
00000000   7C 24 22 0E  83 20 E2 0D  75 14 22 0E  7B 20 32 0E
./arm-wbregs 0x0200f148
0200f148 (        ) : [."$|] 0e22247c
0003FFF0   57 08 61 09  55 20 81 0A  4C 0C 21 0B  51 24 71 0B
./arm-wbregs 0x0204f144
0204f144 (        ) : [.q$Q] 0b712451
*/
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "lifting.h"
#define BLKRAM_FLAG 0x01401000
#define BLKRAM_INVFWD 0x01401004
#define imgsize 256
#define DBUG 1
#define DBUG1 1
#define	zip_break()		asm("BREAK\n")
/* ./arm-zipload -v ../board/jpeg
 * ./arm-wbregs 0x00A01000 0x0
 * ./arm-wbregs 0x00A01004 0x1
 * ./arm-wrsdram rgb_pack.bin
 * ./arm-wbregs cpu 0x0f
 * ./arm-rdsdram dwt.bin
 *  BLKRAM_FLAG is used to tell the program which sub band to use 
 * 0 Red ./arm-wbregs 0x00A01000 0x0
 * 1 Green ./arm-wbregs 0x00A01000 0x1
 * 2 Blue ./arm-wbregs 0x00A01000 0x2
 * BLKRAM_INVFWD is used to tell the program to compute the fwd lifting step only or fwd lifting then inv lifting step
 * 0 fwd lifting then inv lifting step ./arm-wbregs 0x00A01004 0x0
 * 1 fwd lifting step only ./arm-wbregs 0x00A01004 0x1
 */

void clrram(int loop, int *obuf) {
int i,value=0;
for(i=0;i<loop;i++) {
	*obuf = value;
	obuf++;
	
}
}

void out2inpbuf(int loop, int *ibuf,  int *obuf) {
int i;
for(i=0;i<loop;i++) {
	*obuf = *ibuf;
	obuf++;
	ibuf++;
}
}
//0xc0024	786468	0x008093b0
struct PTRs {
	int inpbuf[65536]; //0x0200f144 0e22247c value read from rgb_pack.bin 
	 
	int flag; //0x0201f144 0a00d845 pointing to wh bkram was before upgrade/
	int w; //0x0201f148 0x0a40f04c						"
	int h; //0x0201f14c 0x0a50fc4e						"
	 
	 int *red; //0x0201f150								"
	
	 int *grn; //0x0201f154								"
	 int *blu; //0x0201f158								"
	 int *alt; //0x0201f15c
	 int *ptr_blkram_flag; //0x0201f160 0x0a70fc4c		"
	 int *ptr_blkram_invfwd; //0x0201f164 0x0ac10051	"
	//int *fwd_inv;
} ptrs;

 
void split(int ff, int loop, int *ibuf,  int *obuf) {
        
    int	*ip = ibuf;
     int *op = obuf;
    int i,sp,x,y,z;
	for(i=0;i<loop;i++) {
		x = *ip;
		if (ff == 0) y = 0x1ff00000;
		if (ff == 1) y = 0x7fc00;
		if (ff == 2) y = 0x1ff;
		z = x & y;
		//printf("x = 0x%x z = 0x%x y = 0x%x ",x,z,y);
		if (ff == 0) sp = z>>20;
		if (ff == 1) sp = z>>8;
		if (ff == 2) sp = z;
		*op = sp;
		if(DBUG) {
			if (i <= 3) printf("x = 0x%x sp = 0x%x z = 0x%x\n",x,sp,z);
			if (i > 65532) printf("x = 0x%x sp = 0x%x z = 0x%x\n",x,sp,z);
		}
		ip++;
		op++;
	}
		
}	
int main(int argc, char **argv) {
	
	 
	  
	 int *red_s_ptr, *gr_s_ptr, *bl_s_ptr;
	 int *wptr,*wptr1,*wptr2;
	 int *alt,*alt1,*alt2;
	
	 
	 int *buf_red, *buf_gr, *buf_bl;
	 int ur,ug,ub,x,y,z;
	int *fwd_inv;	

	int i,j;
	 
	ptrs.w = 256;
	ptrs.h = 256;
	ptrs.ptr_blkram_flag = (int *)BLKRAM_FLAG; 
	ptrs.ptr_blkram_invfwd = (int *)BLKRAM_INVFWD;  
	buf_red = ( int *)malloc(sizeof( int)* ptrs.w*ptrs.h*2);	
	red_s_ptr = buf_red;
	
	fwd_inv = (int *)malloc(sizeof( int)*1);
	//zip_break(); //break #2
/*
BOMB : CPU BREAK RECEIVED
ZIPM--DUMP: Supervisor mode

sR0 : 020000b8 sR1 : 020cf1c8 sR2 : 00000000 sR3 : 00000000
sR4 : 00000000 sR5 : 0204f1c0 sR6 : 00000000 sR7 : 0200f148
sR8 : 0204f14c sR9 : 0204f150 sR10: 0204f164 sR11: 0204f168
sR12: 00000000 sSP : 02ffffc8 sCC : 00000000 sPC : 020000b8

uR0 : 00000000 uR1 : 00000000 uR2 : 00000000 uR3 : 00000000
uR4 : 00000000 uR5 : 00000000 uR6 : 00000000 uR7 : 00000000
uR8 : 00000000 uR9 : 00000000 uR10: 00000000 uR11: 00000000
uR12: 00000000 uSP : 00000000 uCC : 00000020 uPC : 02000030
*/
	if(buf_red == NULL) return 2;
	
	if(fwd_inv == NULL) return 5;
	red_s_ptr = buf_red;
	//zip_break();//break #3
/*
BOMB : CPU BREAK RECEIVED
ZIPM--DUMP: Supervisor mode

sR0 : 020000b8 sR1 : 020cf1c8 sR2 : 00000000 sR3 : 00000000
sR4 : 00000000 sR5 : 0204f1c0 sR6 : 020cf1c8 sR7 : 0200f148
sR8 : 0204f14c sR9 : 0204f150 sR10: 0204f164 sR11: 0204f168
sR12: 00000000 sSP : 02ffffc8 sCC : 00000000 sPC : 020000c8

uR0 : 00000000 uR1 : 00000000 uR2 : 00000000 uR3 : 00000000
uR4 : 00000000 uR5 : 00000000 uR6 : 00000000 uR7 : 00000000
uR8 : 00000000 uR9 : 00000000 uR10: 00000000 uR11: 00000000
uR12: 00000000 uSP : 00000000 uCC : 00000020 uPC : 02000030
*/
	if (DBUG) {
		zip_break();//break #4
		printf("ptrs.inpbuf = 0x%x buf_red = 0x%x\n",ptrs.inpbuf,buf_red);
     
		printf("fwd_inv = 0x%x\n",fwd_inv);
	}
    /*The file rgb_pack.bin contains the rgb images
     * packed in bits red 29-20
     * packed in bits grn 19-10
     * packed in bits blu 9-0 
    */ 
 	i = ptrs.w*ptrs.h*2;
 	//zip_break();
 	clrram(i,buf_red);
 	//zip_break(); //break #1 not reached.
	i = 65535;
	 
		ptrs.flag = ptrs.ptr_blkram_flag[0];
		split(ptrs.flag, i, ptrs.inpbuf,buf_red);
	

		*fwd_inv = ptrs.ptr_blkram_invfwd[0];
		
		if (ptrs.flag == 0) { 
			if (DBUG1) {
				printf("spliting red sub band\n");
			}
			
		}
		else if (ptrs.flag == 1) {
			if (DBUG1) {
				printf("spliting green sub band\n");
			}
			
		}	
		else if (ptrs.flag == 2) {
			if (DBUG1) {
				printf("spliting blue sub band\n");
			}
		
		}
		else {
			if (DBUG1) {
				printf("First parameter can only be 0 1 2 \n");
			}
			free(buf_red);
	        free(fwd_inv);
			exit (1);
		}
 
 
 
		if (fwd_inv[0] == 0) { 
			if (DBUG1) {
				printf("fwd lifting then inv lifting step\n");
			}
			
		}
		else if (fwd_inv[0] == 1) {
			if (DBUG1) {
				printf("fwd lifting step only\n");
			}
			
		} else
		{
			if (DBUG1) {
				printf("BLKRAM_INVFWD parameter can only be 0 1  \n");
			}
			free(buf_red);
	        free(fwd_inv);
			exit (2);
		}

		buf_red = red_s_ptr;
		wptr = buf_red;
		alt = &buf_red[ptrs.w*ptrs.h];
		if(DBUG) {
			printf("w = 0x%x wptr = 0x%x alt =  0x%x fwd_inverse =  0x%x fwd_inverse =  0x%x \n",ptrs.w, wptr,alt,fwd_inv,*fwd_inv);
		}
		if(DBUG1) {
			printf("starting red dwt\n");
		}
		
			lifting(ptrs.w,wptr,alt,fwd_inv);
		
		if(DBUG1) {
			printf("finished ted dwt\n");
		}
		out2inpbuf(i,buf_red, ptrs.inpbuf);
		//pack(ptrs.flag, i,buf_red, ptrs.inpbuf);
	while (DBUG1) {
	}
  	free(buf_red);
	free(fwd_inv);
	return 0;
	
	
}
