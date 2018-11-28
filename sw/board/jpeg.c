
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
	
	 
	int *m_ptr;
	int *img_ptr;
	int *buf_red, *buf_gr, *buf_bl;
	int u,x,y,z;
		

	int val,i;
	int w,h;
	w = 256;
	h = 256;

	img_ptr = (int *)malloc(w*h);
	buf_red = (int *)malloc(w*h*2);
	buf_gr = (int *)malloc(w*h*2);
	buf_bl = (int *)malloc(w*h*2);
	
	//saving the img_ptr
	m_ptr = img_ptr;
	//*_gpio = GPIO_LEDR_SET;
	//printf("gpio 0x%x\n",_gpio);
	printf("img_ptr = 0x%x\n",img_ptr);
    printf("buf_red = 0x%x\n",buf_red);
    printf("buf_gr = 0x%x\n",buf_gr);
    printf("buf_bl = 0x%x\n",buf_bl);
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
	
	for(i=0;i<10;i++) {
		printf("img_ptr = 0x%x *img_ptr = 0x%x\n",img_ptr,*img_ptr);
		img_ptr ++;
	}
	img_ptr = img_ptr + 30000;
	for(i=0;i<10;i++) {
		printf("img_ptr = 0x%x *img_ptr = 0x%x\n",img_ptr,*img_ptr);
		img_ptr ++;
	}
	img_ptr = img_ptr + 35000;
	for(i=0;i<10;i++) {
		printf("img_ptr = 0x%x *img_ptr = 0x%x\n",img_ptr,*img_ptr);
		img_ptr ++;
	}
	printf("m_ptr = 0x%x\n",m_ptr);
	img_ptr = m_ptr;	
	for(i=0;i<5;i++) {
		x = *img_ptr;
		y = 0x1ff00000;
		z = x & y;
		u = z>>20;
		img_ptr++;
		printf("%d 0x%x\n",i,u);
	}
	img_ptr = m_ptr;
	for(i=0;i<5;i++) {
		x = *img_ptr;
		y = 0x7fc00;
		z = x & y;
		u = z>>8;
		img_ptr++;
		printf("%d 0x%x\n",i,u);
	}
	img_ptr = m_ptr;	
	for(i=0;i<5;i++) {
		
		x = *img_ptr;
		y = 0x1ff;
		z = x & y;
		
		printf("%d 0x%x\n",i,u);
	}	
	//lifting(w,wptr,alt,fwd_inv);
	free(img_ptr);
	free(buf_red);
	free(buf_gr);
	free(buf_bl);
	//*_gpio = 0x010000;
}
