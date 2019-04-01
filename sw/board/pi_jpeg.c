
#include <stdio.h>
#include <stdlib.h>
 
#include "lifting.h"

struct PTRs {
	int inpbuf[65536];
	 
	int flag;
	int w;
	int h;
	 
	 int *red;
	
	 int *grn;
	 int *blu;
	 int *alt;
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
		if (i <= 3) printf("x = 0x%x sp = 0x%x z = 0x%x\n",x,sp,z);
		if (i > 65532) printf("x = 0x%x sp = 0x%x z = 0x%x\n",x,sp,z);
		ip++;
		op++;
	}
		
}	

int main(int argc, char **argv) {
	
	FILE *inptr,*outptr;
	  
	 
	 int *red_s_ptr, *gr_s_ptr, *bl_s_ptr;
	 int *wptr,*wptr1,*wptr2;
	 int *alt,*alt1,*alt2;
	
	 
	 int *buf_red, *buf_gr, *buf_bl;
	 int ur,ug,ub,x,y,z;
	int *fwd_inv;	

	int i,j;
	 
	ptrs.w = 256;
	ptrs.h = 256;
	  
	buf_red = ( int *)malloc(sizeof( int)* ptrs.w*ptrs.h*2);	
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
    inptr = fopen("rgb_pack.bin","rb");
    if (!inptr)
	{
		printf("Unle to open file!");
		return 1;
	}
	fread(ptrs.inpbuf,sizeof(int),65536,inptr);
	for(i=0;i<5;i++) {
		printf("ptrs.inpbuf = 0x%x *ptrs.inpbuf = 0x%x\n",ptrs.inpbuf,*ptrs.inpbuf);
		buf_red++;

	} 
	fclose(inptr);
	
	i = 65535;
	 
		ptrs.flag = 0;
		split(ptrs.flag, i, ptrs.inpbuf,buf_red);
	

		*fwd_inv = 0;
		buf_red = red_s_ptr;
		wptr = buf_red;
		alt = &buf_red[ptrs.w*ptrs.h];
		printf("w = 0x%x buf_red wptr = 0x%x alt =  0x%x fwd_inverse =  0x%x fwd_inverse =  0x%x \n",ptrs.w, wptr,alt,fwd_inv,*fwd_inv);
		printf("starting red dwt\n");
		lifting(ptrs.w,wptr,alt,fwd_inv);
		printf("finished ted dwt\n");
		//pack(ptrs.flag, i,buf_red, ptrs.inpbuf);
	
    outptr = fopen("dwt.bin","wb");
    if (!outptr)
	{
 	printf("Unle to open file!");
	return 1;
	}
	fwrite(buf_red,sizeof( int),65536,outptr);
	//fwrite(alt,sizeof( int),65536,outptr);
	fclose(outptr);
 		
 	free(buf_red);
	free(fwd_inv);
 
	return 0;

}
