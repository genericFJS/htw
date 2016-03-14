#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st1f.h"
static char buf[128];
void putStud(tStud s)
{
  printf("%-28s %u Bel: %d\n",s.name,s.matrNr,s.belNote);
}


tStud getStud2()
{
  tStud s={};
  printf("Eingabe Name: ");
  fgets(buf,128,stdin); 
  buf[strlen(buf)-1]=0;
  s.name=malloc(strlen(buf)+1);
  if (s.name==NULL){puts("malloc hat nicht geklappt"); exit(-1);}
  strcpy(s.name,buf);
  printf("Eingabe MatrNr: ");
  fgets(buf,128,stdin); s.matrNr=atoi(buf);  
  return s;
}


void putStudp(tStud* s)
{
  //printf("%-28s %u\n",(*s).name,(*s).matrNr);
  printf("%-28s %u\n",s->name,s->matrNr);
}