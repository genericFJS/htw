#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *pf;
FILE *pfout; 
unsigned char buf[16];

int main(int argc, char* argv[])
{
  int count=0,i,j,len;
  if(argc<2){fprintf(stderr,"usage: %s <filename_in> <textfile_out>\n",argv[0]);exit(1);}
  pf=fopen(argv[1],"rb");
  if (pf==NULL) {fprintf(stderr,"file %s not found\n",argv[1]);exit(1);}
  if(argc==3)
  {
   pfout=fopen(argv[2],"wt");
   if (pfout==NULL) {fprintf(stderr,"could not open file %s \n",argv[2]);exit(1);}
  }
  else pfout=stdout;
  
  while ((len=fread(buf,1,16,pf))!=0)
  {
    fprintf(pfout,"%04X: ",count);
    for(i=0; i<16; i+=4)
    {
      for(j=0;j<4;j++)
      {
	if(i+j<len) fprintf(pfout,"%02X ",buf[i+j]);
	else        fprintf(pfout,"   ");
      }
      if (i<12) fprintf(pfout,"| ");
    }
    for(i=0;i<16;i++)  
      if(i<len) fprintf(pfout,"%c",isgraph(buf[i])?buf[i]:'.');
                      
    fprintf(pfout,"\n");
    count+=16;
    memset(buf,0,16);
  }
  fclose(pf);
  fclose(pfout);
  return 0;
}