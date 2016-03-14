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
  fStud=fopen(argv[1],"a+t");
  if(fStud==NULL){fprintf(stderr,"Fileerror %s\n",argv[1]); exit(1);}
  localStud=getStud();
  fprintf(fStud,"%s,%u,%u,%f\n",
	  localStud.Name,
	  localStud.MatrNr,
	  localStud.BelNote,
	  localStud.KlNote);

  rewind(fStud);
  char*p;
  while(fgets(vbuf,128,fStud)!=NULL)
  {
    puts(vbuf);
    p=strtok(vbuf,",\n");
    strcpy(localStud.Name,p);
    localStud.MatrNr =atoi(strtok(NULL,",\n"));
    localStud.BelNote=atoi(strtok(NULL,",\n"));
    localStud.KlNote =atof(strtok(NULL,",\n"));
    printStud(&localStud);
  }
  fclose(fStud);
  return 0;
}