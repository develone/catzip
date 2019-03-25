
#include <stdio.h>
#include <stdlib.h>
 


struct PTRs {
	int inpbuf[65536];
	 
	int flag;
	int w;
	int h;
	 
	char *red;
	
	char *grn;
	char *blu;
	char *alt;
	//int *fwd_inv;
} ptrs;

void pack(int ff, int loop, char *ibuf, int *obuf) {
	int	*op = obuf;
    char *ip = ibuf;

	int i,sp,x,y,z;
	for(i=0;i<loop;i++) {
		z = *ip;
		x = *op;
		
		if (ff == 0) sp = z<<20;
		if (ff == 1) sp = z<<8;
		if (ff == 2) sp = z;
		if (ff == 0) y = x & 0x1ff00000;
		if (ff == 1) y = x & 0x1ff001ff;
		if (ff == 2) y = x & 0x1ff7fc00;
		y = y | sp;
		if (i <= 3) printf("x = 0x%x sp = 0x%x y = 0x%x\n",x,sp,y);
		if (i > 65532) printf("x = 0x%x sp = 0x%x y = 0x%x\n",x,sp,y);
		ip++;
		op++;
	}
	
	}
void split(int ff, int loop, int *ibuf, char *obuf) {
        
    int	*ip = ibuf;
    char *op = obuf;
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
	  
	 
	char *red_s_ptr, *gr_s_ptr, *bl_s_ptr;
	char *wptr,*wptr1,*wptr2;
	char *alt,*alt1,*alt2;
	
	 
	char *buf_red, *buf_gr, *buf_bl;
	char ur,ug,ub,x,y,z;
	int *fwd_inv;	

	int val,i;
	 
	ptrs.w = 256;
	ptrs.h = 256;
	  
	buf_red = (char *)malloc(sizeof(char)* ptrs.w*ptrs.h*2);	
	red_s_ptr = buf_red;
	
	if(buf_red == NULL) return 2;
	
 
	 
    printf("buf_red = 0x%x\n",buf_red);
     
    printf("fwd_inv = 0x%x\n",fwd_inv);
    /*The file rgb_pack.bin contains the rgb images
     * packed in bits red 29-20
     * packed in bits grn 19-10
     * packed in bits blu 9-0 
    */ 
    inptr = fopen("dwt_pack.bin","rb");
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
	buf_red = red_s_ptr;
	i = 65535;
	ptrs.flag = 2;
	split(ptrs.flag, i, ptrs.inpbuf,buf_red);
	

 
    outptr = fopen("dwt8.bin","wb");
    if (!outptr)
	{
 	printf("Unle to open file!");
	return 1;
	}
	fwrite(buf_red,sizeof(char),65536,outptr);
	 
	fclose(outptr);

 	free(buf_red);
	 
 
	return 0;

}
