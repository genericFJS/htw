#include <stdio.h>
#include <stdlib.h>

char buf[128];
char *result;

char* crtBitStr(unsigned int x){
	unsigned int size = sizeof(x)*8;
	unsigned int bitMask = 1;
	result = malloc(size);
	unsigned int i;
	if (!result) {
		exit (-1);
	} else {
		for (i=0; i<size;i++){
			result[size-1-i]=(x&bitMask)>0;
			bitMask = bitMask<<1;
		}
	}	
	return result;
}

main (int argc, char* argv[]){
	printf("\x1b[32m");
	printf("Eingabe einer int-Zahl: ");
	fgets(buf, 128, stdin);
	puts("***");
	int x = atoi(buf);
	char* bitStr = crtBitStr(x);
	
	printf("dez: %u\nhex: %08X\nbin: ",x, x);
	int i;
	for (i=0; i<sizeof(x)*8; i++){
		if (i%8 ==0 && i!=0)
			printf("|");
		printf("%u",bitStr[i]);
	}
	
	puts("\n+++");
	printf("\x1b[0m");
	free (result);
}