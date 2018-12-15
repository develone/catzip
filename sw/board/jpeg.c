
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "lifting.h"
#define SDRAM 0x800000
#define imgsize 256

void zip_clear_sdram(int *imbuf) {
int val,i;

val = 0;
 
 
 
for(i=0; i<256*256*12; i++) {
	*imbuf++ = val;
}
}
//0xc0024	786468	0x008093b0
struct PTRs {
	int inpbuf[65536];
	int act[131072];
	int flag;
	int w;
	int h;
	int *img;
	int *red;
	//int *fwd_inv;
	int *grn;
	int *blu;
	int *alt;
} ptrs;

void split(int ff, int loop, int *ibuf, int *obuf) {
        
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
		if (i <= 3) printf("x = 0x%x sp = 0x%x z = 0x%x\n",x,sp,z);
		if (i > 65532) printf("x = 0x%x sp = 0x%x z = 0x%x\n",x,sp,z);
		ip++;
		op++;
	}
		
}	
int main(int argc, char **argv) {
	
	ptrs.w = 256;
	ptrs.h = 256;
	int *im_s_ptr; 
	int i,x,y,z,ur,ug,ub;
	int *fwd_inv;
	ptrs.img = (int *)&ptrs.inpbuf;
	printf("w = 0x%x h = 0x%x\n",ptrs.w,ptrs.h); 
	
 	printf("ptrs-->img = 0x%x\n",ptrs.img);
 	
	//split red
	ptrs.red = (int *)&ptrs.act;
	ptrs.alt = (int *)&ptrs.act[65536];
	ptrs.flag = 0;
	i = 65535;
	ptrs.red = ptrs.act;
 	split(ptrs.flag, i, ptrs.img, ptrs.red);
 	printf("back from split start of dwt \n");
	 
 	for(i=0;i<5;i++) printf("0x%x \n",ptrs.red[i]);
 	for(i=0;i<5;i++) printf("0x%x \n",ptrs.alt[i]);
 	*fwd_inv = 1;    
    printf("0x%x 0x%x 0x%x 0x%x  \n", ptrs.w,ptrs.red,ptrs.alt,*fwd_inv);
    

	lifting(ptrs.w,ptrs.red,ptrs.alt,fwd_inv);
	printf("back from dwt\n");
	
	
	
}
