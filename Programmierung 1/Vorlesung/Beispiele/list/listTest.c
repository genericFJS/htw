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

void printAll(tlist* pList)
{
  tStud* ptmp;
  for (ptmp=getFirst(pList);
       ptmp;
       ptmp=getNext(pList))
       putStud(ptmp);
}

char quit()
{
  printf("Ende?(y/n)[n]:");
  fgets(vbuf,128,stdin);
  return 'Y'==toupper(vbuf[0]);
}

int main(int argc, char*argv[])
{
  char * p;
  int i;
  tStud* ptmp;
  tlist *plist;
  plist=CreateList();
  while(!quit())
  {
    ptmp=getStud();
    if (ptmp) insertHead(plist,ptmp);
    printAll(plist);
  }
  while(ptmp=getFirst(plist)) 
  {
    free(ptmp->pName);
    free(ptmp);
    removeItem(plist);
  }
  return 0;
}