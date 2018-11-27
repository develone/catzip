
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
	
	 
	int *m_ptr,*img_ptr;
	
		

	int val,i;
	int w,h;
	w = 256;
	h = 256;
	//malloc is for 3 * w*h 
	printf("malloc should be 0x30000 196608\n");
	printf("size of malloc 0x%x \n",w*h*3);
	img_ptr = (int *)malloc(w*h*3);
	
	//saving the img_ptr
	m_ptr = img_ptr; 
	//*_gpio = GPIO_LEDR_SET;
	//printf("gpio 0x%x\n",_gpio);
	printf("img_ptr = 0x%x\n",img_ptr);
 
	printf("Start of JPEG DWT!\n");
	 
	 
	 
	 
	 
	
	
	//this was done by clr_sdram
	//printf("clearing buf_ptr + 786432 buf_ptr = 0x%x\n",img_ptr);
	//zip_clear_sdram(img_ptr);
	//printf("done clearing buf_ptr + 786432 \n");
	//printf("free img_ptr !\n");	
	 
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
	//lifting(w,wptr,alt,fwd_inv);
	free(img_ptr);
	//*_gpio = 0x010000;
}
