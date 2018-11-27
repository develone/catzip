
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
	 
	img_ptr = (int *)malloc(196608); 
	int val,i;
	//*_gpio = GPIO_LEDR_SET;
	printf("gpio 0x%x\n",_gpio);
	printf("img_ptr = 0x%x\n",img_ptr);
 
	printf("Start of JPEG DWT!\n");
	 
	 
	 
	 
	 
	
	
	//this was done by clr_sdram
	//printf("clearing buf_ptr + 786432 buf_ptr = 0x%x\n",img_ptr);
	//zip_clear_sdram(img_ptr);
	//printf("done clearing buf_ptr + 786432 \n");
	printf("free img_ptr !\n");	
	 
	for(i=0;i<100;i++) {
		printf("img_ptr = 0x%x *img_ptr = 0x%x\n",img_ptr,*img_ptr);
		img_ptr ++;
	}
	free(img_ptr);
	//*_gpio = 0x010000;
}
