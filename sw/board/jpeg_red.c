
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

int main(int argc, char **argv) {
	
	 
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
	
	 
	buf_red = (int *)malloc( w*h*2);
	red_s_ptr = buf_red;
	
	fwd_inv = (int *)malloc(1);
 
	if(buf_red == NULL) return 2;
	
 
	if(fwd_inv == NULL) return 5;
	red_s_ptr = buf_red;
    printf("buf_red = 0x%x\n",buf_red);
     
    printf("fwd_inv = 0x%x\n",fwd_inv);
    
     
	printf("Start of JPEG DWT!\n");
	 
	 
	 
	 
	 
	
	
	//this was done by clr_sdram
	//printf("clearing buf_ptr + 786432 buf_ptr = 0x%x\n",img_ptr);
	//zip_clear_sdram(img_ptr);
	//printf("done clearing buf_ptr + 786432 \n");
	//printf("free img_ptr !\n");	
	//const int bb = 0x1ff;
    //const int gg = 0x7fc00;		shift right 8
    //const int rr = 0x1ff00000; 	shift right 20
	printf("w = 0x%x h = 0x%x\n",w,h); 
	
 	for(i=0;i<5;i++) {
		printf("buf_red = 0x%x *buf_red = 0x%x\n",buf_red,*buf_red);
		buf_red++;
	}
	printf("\n");
	
	buf_red = red_s_ptr;
	wptr = buf_red;
 	 
	
	alt = &buf_red[w*h];
 	printf("w = 0x%x buf_red wptr = 0x%x alt =  0x%x fwd_inverse =  0x%x fwd_inverse =  0x%x \n",w, wptr,alt,fwd_inv,*fwd_inv);
 	
	
	printf("starting red dwt\n");
	
	

	
	
	lifting(w,wptr,alt,fwd_inv);
	printf("finished ted dwt\n");
 	free(buf_red);
	free(fwd_inv);
 
	return 0;
	//*_gpio = 0x010000;
}
