#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *pf;
unsigned char buf[16];

int main(int argc, char* argv[])
{
  int count=0,i,j,len;
  if(argc!=2){fprintf(stderr,"usage: %s <filename>\n",argv[0]);exit(1);}
  pf=fopen(argv[1],"rb");
  if (pf==NULL) {fprintf(stderr,"file %s not found\n",argv[1]);exit(1);}
  while ((len=fread(buf,1,16,pf))!=0)
  {
    printf("%04X: ",count);
    for(i=0; i<16; i+=4)
    {
      for(j=0;j<4;j++)
      {
	if(i+j<len) printf("%02X ",buf[i+j]);
	else        printf("   ");
      }
      if (i<12) printf("| ");
    }
    for(i=0;i<16;i++)  
      if(i<len) printf("%c",isgraph(buf[i])?buf[i]:'.');
                      
    printf("\n");
    count+=16;
    memset(buf,0,16);
  }
  return 0;
}