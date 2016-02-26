// A. Beck 2014

// gcc list.c stud.c listTest.c 
//
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "stud.h"
#include "list.h"

char vbuf[128];

char quit()
{
  printf("Ende?(y/n)[n]:");
  fgets(vbuf,128,stdin);
  return 'Y'!=toupper(vbuf[0]);
}

int main(int argc, char*argv[])
{
  char * p;
  int i;
  tStud* ptmp;
  tlist* pl=createList();
  if (pl==NULL){printf("no mem, no fun\n");exit(-1);}
  while(quit)
  {
    ptmp=getStud();
    putStud(ptmp);
    insertHead(pl, ptmp);
    puts("-------------------------");
    for(ptmp=getFirst(pl);ptmp;ptmp=getNext(pl))putStud(ptmp);
  }

  return 0;
}