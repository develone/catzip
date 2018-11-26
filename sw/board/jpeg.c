
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
	int *buf_ptr = (int *)0x800000;
	//int *img_ptr = (int *)(SDRAM + 45000);
	int *m_ptr,*img_ptr;
	m_ptr = malloc(196608);
	img_ptr = malloc(196608); 
	int val,i;
	//*_gpio = GPIO_LEDR_SET;
	printf("gpio 0x%x\n",_gpio);
	printf("img_ptr = 0x%x\n",img_ptr);
	//int img_mem = imgsize*imgsize*3;
	//printf("img_mem = %ld\n",img_mem);
	printf("Start of JPEG DWT!\n");
	printf("buf_ptr = 0x%x\n",buf_ptr);
	m_ptr = malloc(196608);
	printf("m_ptr = 0x%x\n",m_ptr);
	val = 0;
	printf("Clr m_ptr !\n");
	
	//256*256*12 = 786432
	//this was done by clr_sdram
	printf("clearing buf_ptr + 786432 buf_ptr = 0x%x\n",buf_ptr);
	zip_clear_sdram(buf_ptr);
	printf("done clearing buf_ptr + 786432 \n");
	printf("free m_ptr !\n");	
	free(m_ptr);
	*img_ptr = 0x01020304;
	printf("img_ptr = 0x%x *img_ptr = 0x%x\n",img_ptr,*img_ptr);
	img_ptr ++;
	*img_ptr = 0x05060708;
	printf("img_ptr = 0x%x *img_ptr = 0x%x\n",img_ptr,*img_ptr);
	free(img_ptr);
	//*_gpio = 0x010000;
}
