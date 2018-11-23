#include <stdio.h>
#include "lifting.h"
int main(int argc, char **argv) {
	int *buf_ptr = (int *)0x800000;
	printf("Start of JPEG DWT!\n");
	printf("buf_ptr = 0x%x\n",buf_ptr);
}
