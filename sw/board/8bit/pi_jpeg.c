
#include <stdio.h>
#include <stdlib.h>
 
#include "lifting.h"

int main(int argc, char **argv) {
	
	FILE *inptr,*outptr; 
	char *im_s_ptr;
	char *red_s_ptr, *gr_s_ptr, *bl_s_ptr;
	char *wptr,*wptr1,*wptr2;
	char *alt,*alt1,*alt2;
	
	char *img_ptr;
	char *buf_red, *buf_gr, *buf_bl;
	char ur,ug,ub,x,y,z;
	int *fwd_inv;	

	int val,i;
	int w,h;
	w = 256;
	h = 256;
	
	 
	buf_red = (char *)malloc(sizeof(char)* w*h*2);	red_s_ptr = buf_red;
	
	fwd_inv = (int *)malloc(1);
 
	if(buf_red == NULL) return 2;
	
	if(fwd_inv == NULL) return 5;
	red_s_ptr = buf_red;
    printf("buf_red = 0x%x\n",buf_red);
     
    printf("fwd_inv = 0x%x\n",fwd_inv);
    inptr = fopen("red-out.8","rb");
    if (!inptr)
	{
 	printf("Unle to open file!");
	return 1;
	}
	fread(buf_red,sizeof(char),65536,inptr);
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
    outptr = fopen("dwt8.bin","wb");
    if (!outptr)
	{
 	printf("Unle to open file!");
	return 1;
	}
	fwrite(buf_red,sizeof(char),65536,outptr);
	//fwrite(alt,sizeof(char),65536,outptr);
	fclose(outptr);	
 	free(buf_red);
	free(fwd_inv);
 
	return 0;

}
