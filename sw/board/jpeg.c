
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
	 
	int flag;
	int w;
	int h;
	 
	char *red;
	
	char *grn;
	char *blu;
	char *alt;
	//int *fwd_inv;
} ptrs;

void pack(int ff, int loop, char *ibuf, int *obuf) {
	int	*op = obuf;
    char *ip = ibuf;

	int i,sp,x,y,z;
	for(i=0;i<loop;i++) {
		z = *ip;
		x = *op;
		
		if (ff == 0) sp = z<<20;
		if (ff == 1) sp = z<<8;
		if (ff == 2) sp = z;
		/*
		if (ff == 0) y = x & 0x1ff00000;
		if (ff == 1) y = x & 0x1ff001ff;
		if (ff == 2) y = x & 0x1ff7fc00;
		y = y | sp;
		*/
		if (i <= 3) printf("x = 0x%x sp = 0x%x y = 0x%x\n",x,sp,y);
		if (i > 65532) printf("x = 0x%x sp = 0x%x y = 0x%x\n",x,sp,y);
		*op = sp;
		ip++;
		op++;
	}
	
	}
void split(int ff, int loop, int *ibuf, char *obuf) {
        
    int	*ip = ibuf;
    char *op = obuf;
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
	
	 
	  
	 
	char *red_s_ptr, *gr_s_ptr, *bl_s_ptr;
	char *wptr,*wptr1,*wptr2;
	char *alt,*alt1,*alt2;
	
	 
	char *buf_red, *buf_gr, *buf_bl;
	char ur,ug,ub,x,y,z;
	int *fwd_inv;	

	int i,j;
	 
	ptrs.w = 256;
	ptrs.h = 256;
	  
	buf_red = (char *)malloc(sizeof(char)* ptrs.w*ptrs.h*2);	
	red_s_ptr = buf_red;
	
	fwd_inv = (int *)malloc(1);
 
	if(buf_red == NULL) return 2;
	
	if(fwd_inv == NULL) return 5;
	red_s_ptr = buf_red;
    printf("buf_red = 0x%x\n",buf_red);
     
    printf("fwd_inv = 0x%x\n",fwd_inv);
    /*The file rgb_pack.bin contains the rgb images
     * packed in bits red 29-20
     * packed in bits grn 19-10
     * packed in bits blu 9-0 
    */ 
 	
	i = 65535;
	 
		ptrs.flag = 2;
		split(ptrs.flag, i, ptrs.inpbuf,buf_red);
	

		*fwd_inv = 1;
		buf_red = red_s_ptr;
		wptr = buf_red;
		alt = &buf_red[ptrs.w*ptrs.h];
		printf("w = 0x%x buf_red wptr = 0x%x alt =  0x%x fwd_inverse =  0x%x fwd_inverse =  0x%x \n",ptrs.w, wptr,alt,fwd_inv,*fwd_inv);
		printf("starting red dwt\n");
		lifting(ptrs.w,wptr,alt,fwd_inv);
		printf("finished ted dwt\n");
		pack(ptrs.flag, i,buf_red, ptrs.inpbuf);
	
  	free(buf_red);
	free(fwd_inv);
	return 0;
	
	
}
