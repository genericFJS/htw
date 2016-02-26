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
  tlist *plist=createList();
  if(plist==NULL)
  {
    puts("Kein Speicher"); exit(-1);
  }
  int i;
  tStud* ptmp;
  while(!quit())
  {
    ptmp=getStud();
    
    insertTail(plist,ptmp);
    puts("-------------------------");
    for(ptmp=getFirst(plist);ptmp;ptmp=getNext(plist))
      putStud(ptmp);
  }

  return 0;
}