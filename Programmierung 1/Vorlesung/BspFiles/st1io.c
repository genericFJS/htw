#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st1f.h"

int getAnz(FILE*pf)
{
  char buf[128];
  int n=0;
  while (fgets(buf,128,pf)) n++;
  fseek(pf,0,SEEK_SET);
  return n;
}

tStud readStud(FILE* pf)
{
  tStud s={};
  char buf[128],*p;
  if(fgets(buf,128,pf))
  {
    p=strtok(buf,";\n");
    s.name=malloc(strlen(buf)); // Mit \n, ohne terminierende 0
    if(s.name){
      strcpy(s.name,buf); // Text ohne term. 0 kopieren
      //s.name[strlen(buf)-1]=0; // termineirende 0 einsetzen
      sscanf(buf,"%d;%d;%f\n",&s.matrNr,&s.belNote,&s.klNote);
    }else fprintf(stderr,"malloc failed in readStud\n");
  }
  return s;

}

void writeStud(FILE*pf, tStud* ps)
{
  fprintf(pf,"%s;%d;%d;%f\n",ps->name,ps->matrNr,ps->belNote,ps->klNote);  
}









/*
  char buf[128];
  int n=0;
  while (fgets(buf,128,pf)) n++;
  fseek(pf,0,SEEK_SET);
  return n;
  */
/*
  tStud s={};
  char buf[128],*p;
  if(fgets(buf,128,pf))
  {
    p=strtok(buf,";\n");
    s.name=malloc(strlen(buf)); // Mit \n, ohne terminierende 0
    if(s.name){
      memcpy(s.name,buf,strlen(buf)); // Text ohne term. 0 kopieren
      s.name[strlen(buf)-1]=0; // termineirende 0 einsetzen
      sscanf(buf,"%d;%d;%f\n",&s.matrNr,&s.belNote,&s.klNote);
    }else fprintf(stderr,"malloc failed in readStud\n");
  }
  return s;
*/


/*
  fprintf(pf,"%s;%d;%d;%f\n",ps->name,ps->matrNr,ps->belNote,ps->klNote);  
*/

