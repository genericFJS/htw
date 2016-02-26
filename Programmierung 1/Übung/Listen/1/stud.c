#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "stud.h"

tStud* getStud()
{
  tStud*ptmp;
  puts("Eingabe Student:");
  printf("Name:");
  fgets(vbuf,128,stdin);
  vbuf[strlen(vbuf)-1]=0;
  ptmp=malloc(sizeof(tStud));
  if (ptmp)
  {
    ptmp->pName=malloc(strlen(vbuf));
    if (ptmp->pName==0) {free(ptmp); ptmp=NULL;}
    strcpy(ptmp->pName,vbuf);
  }
  return ptmp;
}

void putStud(tStud* pStud)
{
  printf("%s\n",pStud->pName);
}
