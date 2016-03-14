#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tstudent // Strukturtyp
{
  char  name[28+1]; //Strukturkomponenten
  int   matrNr;
  float KlNote;
  int   BelegNote;
}tStud;
char vbuf[128];
void putStud(struct tstudent* s)
{
//printf("%-28s %07d %3.1f      %d\n",(*s).name,(*s).matrNr,(*s).KlNote,(*s).BelegNote); 
  printf("%-28s %07d %3.1f      %d\n",s->name,s->matrNr,s->KlNote,s->BelegNote); 
}
struct tstudent getStud()
{
  struct tstudent s;
  printf("Name    :"); fgets(s.name,28,stdin);s.name[strlen(s.name)-1]=0;
  printf("MatrNr  :"); fgets(vbuf,128,stdin); s.matrNr=atoi(vbuf);
  s.KlNote=0.0; s.BelegNote=0;
  return s;
}

int main()
{
  int count=0;
  tStud* pStuds;  
  pStuds=malloc(sizeof (tStud));
  if(pStuds==NULL){printf("kein Speicher\n"); exit(1);}
  while(1)
  {
    int i;
    pStuds[count]=getStud(); count ++;
    for (i=0;i<count;i++) putStud(pStuds+i);
    printf("noch einen Studenten erfassen? (j/n):");
    fgets(vbuf,128,stdin);
    if(vbuf[0]=='n') break;
    pStuds=realloc(pStuds,sizeof(tStud)*(count+1));
    if(pStuds==NULL){printf("kein Speicher\n"); exit(1);}
  }

  free(pStuds);
  
  return 0;
}
