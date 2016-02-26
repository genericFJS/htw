#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "list.h"

typedef struct
{
  char *pName;
}tStud;

char vbuf[128];

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

char quit()
{
  printf("Ende?(y/n)[n]:");
  fgets(vbuf,128,stdin);
  return 'Y'==toupper(vbuf[0]);
}

void printAll(tlist* plist)
{
  tStud* ptmp;
  for(ptmp=getFirst(plist);
      ptmp;
      ptmp=getNext(plist))putStud(ptmp);
}

int main()
{
  tStud* ptmp;
  tlist* plist;
  plist=CreateList();
  if (plist==NULL) { puts("Fehler"); exit(1);}
  while(!quit())
  {
    ptmp=getStud();
    insertHead(plist,ptmp);
    printAll(plist);
  }
  return 0;
}