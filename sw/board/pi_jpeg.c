
#include <stdio.h>
#include <stdlib.h>
 
#include "lifting.h"

int main(int argc, char **argv) {
	
	FILE *inptr,*outptr; 
	int *im_s_ptr;
	int *red_s_ptr, *gr_s_ptr, *bl_s_ptr;
	int *wptr,*wptr1,*wptr2;
	int *alt,*alt1,*alt2;
	
	int *img_ptr;
	int *buf_red, *buf_gr, *buf_bl;
	int ur,ug,ub,x,y,z;
	int *fwd_inv;	

	int val,i;
	int w,h;
	w = 256;
	h = 256;
	
	 
	buf_red = (int *)malloc(sizeof(int)* w*h*2);	red_s_ptr = buf_red;
	
	fwd_inv = (int *)malloc(1);
 
	if(buf_red == NULL) return 2;
	
	if(fwd_inv == NULL) return 5;
	red_s_ptr = buf_red;
    printf("buf_red = 0x%x\n",buf_red);
     
    printf("fwd_inv = 0x%x\n",fwd_inv);
    inptr = fopen("blu.bin","rb");
    if (!inptr)
	{
 	printf("Unle to open file!");
	return 1;
	}
	fread(buf_red,sizeof(int),65536,inptr);
	for(i=0;i<5;i++) {
		printf("buf_red = 0x%x *buf_red = 0x%x\n",buf_red,*buf_red);
		buf_red++;
	} 
	fclose(inptr);
	*fwd_inv = 1;
	buf_red = red_s_ptr;
	wptr = buf_red;
	alt = &buf_red[w*h];
 	printf("w = 0x%x buf_red wptr = 0x%x alt =  0x%x fwd_inverse =  0x%x fwd_inverse =  0x%x \n",w, wptr,alt,fwd_inv,*fwd_inv);
 	
	
	printf("starting red dwt\n");
	
	

	
	
	lifting(w,wptr,alt,fwd_inv);
	printf("finished ted dwt\n");
    outptr = fopen("dwt.bin","wb");
    if (!outptr)
	{
 	printf("Unle to open file!");
	return 1;
	}
	fwrite(buf_red,sizeof(int),65536,outptr);
	fclose(outptr);	
 	free(buf_red);
	free(fwd_inv);
 
	return 0;

}
