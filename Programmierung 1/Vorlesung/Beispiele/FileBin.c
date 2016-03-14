#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tStudent
{ 
  char  Name[30];
  int   MatrNr;
  int   BelNote;
  float KlNote;
} tStud;

char vbuf[128];

tStud getStud()
{
  tStud St;
  printf("Name     :");
  fgets(vbuf,128,stdin); vbuf[strlen(vbuf)-1]=0; strncpy(St.Name,vbuf,30);
  printf("MatrNr   :");
  fgets(vbuf,128,stdin); St.MatrNr=atoi(vbuf);
  St.KlNote=0.0; St.BelNote=0;
  return St;
}
void printStud(tStud* s)
{
  printf("Student: %s MatrNr: %06d Klausur: %3.1f Beleg: %d\n",
          s->Name, 
          s->MatrNr, 
          s->KlNote, 
          s->BelNote);
}

/*
 * printf(....)
 * fprintf(stdout,....)
*/
FILE * fStud;

int main(int argc, char*argv[])
{
  tStud localStud;
  int i,anz;
  long len;
  if (argc<2){fprintf(stderr,"usage: %s <filename>\n",argv[0]); exit(1);}
  fStud=fopen(argv[1],"a+b");
  if(fStud==NULL){fprintf(stderr,"Fileerror %s\n",argv[1]); exit(1);}
  localStud=getStud();
  fwrite(&localStud,sizeof localStud,1,fStud);
  
  len=ftell(fStud);
  anz=len/sizeof(tStud);
  fseek(fStud,0,SEEK_SET); //rewind(fSrud);
  for (i=0; i<anz; i++)
  {
    fread(&localStud,sizeof localStud,1,fStud);
    printStud(&localStud);
  }
  fseek(fStud,1*sizeof(tStud),SEEK_SET);
  fread(&localStud,sizeof localStud,1,fStud);
  puts("Student[1]:");
  printStud(&localStud);
  fclose(fStud);
  return 0;
}