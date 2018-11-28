
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "lifting.h"
#define SDRAM 0x2000000
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

	img_ptr = (int *)malloc(w*h);
	buf_red = (int *)malloc(w*h*2);
	buf_gr = (int *)malloc(w*h*2);
	buf_bl = (int *)malloc(w*h*2);
	fwd_inv = (int *)malloc(w*h);
	
	red_s_ptr = buf_red;
	gr_s_ptr = buf_gr;
	bl_s_ptr = buf_bl;
	//saving the img_ptr
	im_s_ptr = img_ptr;
	//*_gpio = GPIO_LEDR_SET;
	//printf("gpio 0x%x\n",_gpio);
	printf("img_ptr = 0x%x\n",img_ptr);
    printf("buf_red = 0x%x\n",buf_red);
    printf("buf_gr = 0x%x\n",buf_gr);
    printf("buf_bl = 0x%x\n",buf_bl);
    printf("fwd_inv = 0x%x\n",fwd_inv);
    
    //printf("top_of_data = 0x%x\n",top_of_data);
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
		printf("img_ptr = 0x%x *img_ptr = 0x%x\n",img_ptr,*img_ptr);
		img_ptr ++;
	}
	printf("\n");
	
	img_ptr = img_ptr + 30000;
	for(i=0;i<5;i++) {
		printf("img_ptr = 0x%x *img_ptr = 0x%x\n",img_ptr,*img_ptr);
		img_ptr ++;
	}
	printf("\n");
	
	img_ptr = img_ptr + 35000;
	for(i=0;i<5;i++) {
		printf("img_ptr = 0x%x *img_ptr = 0x%x\n",img_ptr,*img_ptr);
		img_ptr ++;
	}
	printf("\n");
	
	printf("im_s_ptr = 0x%x\n",im_s_ptr);
	//split red
	img_ptr = im_s_ptr;	
	for(i=0;i<65535;i++) {
		x = *img_ptr;
		y = 0x1ff00000;
		z = x & y;
		ur = z>>20;
		img_ptr++;
		*buf_red = ur;
		buf_red++;
		//printf("%d 0x%x\n",i,ur);
	}
	//restore img_ptr & buf_red
	img_ptr = im_s_ptr;
	buf_red = red_s_ptr;
	
	//split gr
	for(i=0;i<65535;i++) {
		x = *img_ptr;
		y = 0x7fc00;
		z = x & y;
		ug = z>>10;
		img_ptr++;
		*buf_gr = ug;
		buf_gr++;
		//printf("%d 0x%x\n",i,ug);
	}
	
	//restore img_ptr & buf_gr
	img_ptr = im_s_ptr;
	buf_gr = gr_s_ptr;
	
	//split bl	
	for(i=0;i<65535;i++) {		
		x = *img_ptr;
		y = 0x3ff;
		z = x & y;
		ub = z;
		img_ptr++;
		*buf_bl = ub;
		buf_bl++;
		//printf("%d 0x%x\n",i,ub);
	}
	
	//restore img_ptr & buf_bl
	img_ptr = im_s_ptr;
	buf_bl = bl_s_ptr;

	//debug for r g b
	for(i=0;i<5;i++) {
		printf("buf_red = 0x%x *buf_red = 0x%x\n",buf_red,*buf_red);
		buf_red++;
	}
	printf("\n");
	
	buf_red = red_s_ptr;
	
	for(i=0;i<5;i++) {
		printf("buf_gr = 0x%x *buf_gr = 0x%x\n",buf_gr,*buf_gr);
		buf_gr++;
	}
	printf("\n");
	
	buf_gr = gr_s_ptr;
	
	for(i=0;i<5;i++) {
		printf("buf_bl = 0x%x *buf_bl = 0x%x\n",buf_bl,*buf_bl);
		buf_bl++;
	}
	printf("\n");

	buf_bl = bl_s_ptr;
	
	printf("starting red dwt\n");
	
	wptr = buf_red;
	wptr1 = buf_gr;
	wptr2 = buf_bl;	

	alt = &buf_red[256*256];
	lifting(w,wptr,alt,fwd_inv);
	printf("finished ted dwt\n");
	/*	
	alt1 = &buf_gr[256*256];
	lifting(w,wptr1,alt1,fwd_inv);
	
	alt2 = &buf_bl[256*256];
	lifting(w,wptr2,alt2,fwd_inv);
	*/
	
	
	free(img_ptr);
	free(buf_red);
	free(buf_gr);
	free(buf_bl);
	//*_gpio = 0x010000;
}
