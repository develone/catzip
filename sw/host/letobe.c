#include <stdio.h>
#include <inttypes.h>

int main()
{
/*
    uint32_t le = 0x12345678;
    uint32_t be = __builtin_bswap32(le);

    printf("Little-endian: 0x%" PRIx32 "\n", le);
    printf("Big-endian:    0x%" PRIx32 "\n", be);
*/
 
uint32_t le[65536];
uint32_t be[65536];
int i;

FILE *ptr;

ptr = fopen("r.bin","rb");
fread(le,sizeof(le),1,ptr);
fclose(ptr);

for(i=0;i<65536;i++) {

be[i]=__builtin_bswap32(le[i]);
printf("%d 0x%8x	0x%8x\n",i,le[i],be[i]);
}
ptr = fopen("rbe.bin","wb");
fwrite(be,sizeof(be),1,ptr);
fclose(ptr);
    return 0;
}
