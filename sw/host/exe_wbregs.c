#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main(void)
{
    int rc,i,offset,hex_addr;
    char addr[8]="xxxxxxx";
    char data[8];
    char cmd[34];
    char hdr[13]="arm-wbregs ";
    //printf("%s\n",addr);
    
    
    strcpy(addr,"2000000");
    rc = system("arm-wbregs 0x2000000 0x11111111");
    //printf("%s\n",addr);
    hex_addr = atoi(addr);
    //printf("0x%d\n",hex_addr);
    for(i=0;i<65536;i+=4) {
		offset = offset + 4;
		hex_addr = 33554432 + offset;
		
		//inttostring(hex_addr,addr,50331644);
		//printf("0x%x 0x%x\n",offset, hex_addr);
		sprintf(addr, "0x%x", hex_addr);
		sprintf(data, "0x%x", offset);
		sprintf(cmd,"./%s %s %s\n",hdr,addr,data);
		printf("%s\n",cmd);
		
		rc = system(cmd);
		sprintf(cmd,"./%s %s\n",hdr,addr);
		rc = system(cmd);
	}
    exit(0);
}
