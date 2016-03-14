#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct leaf
{
  void* pdata;
  struct leaf* pl;
  struct leaf* pr;
}ttree;

int mycompare(void*p1, void*p2)
{
  return strcmp(p1,p2);
}


ttree treeInit={NULL,NULL,NULL};

void addToTree(ttree* pTree, void* pdata, int (*fcmp)(void*,void*))
{
  if (pTree->pdata==NULL)pTree->pdata=pdata;
  else
  if (fcmp(pTree->pdata,pdata)>0)
  {
    if(pTree->pl==NULL){pTree->pl=malloc(sizeof(ttree));*(pTree->pl)=treeInit;}
    addToTree(pTree->pl,pdata,fcmp);
  }
  else
  {
    if(pTree->pr==NULL){pTree->pr=malloc(sizeof(ttree));*(pTree->pr)=treeInit;}
    addToTree(pTree->pr,pdata,fcmp);
  }
}

void mydisp(void*pdata)
{
  puts(pdata);
}

void dispTree(ttree*ptree, void (*disp)(void*))
{
  if (ptree)
  {
    dispTree(ptree->pl,disp);
    puts(ptree->pdata);
    dispTree(ptree->pr,disp);
  }
}

char *vTest[]={"MAX","MORITZ","HANS","HANS","PETER","PETER","HUCKEBEIN","ALBERT","JOHANN","JAMES",NULL};

int main()
{
  int i;
  ttree* pt=malloc(sizeof(ttree));
  *pt=treeInit;

  for (i=0; vTest[i];i++)addToTree(pt,vTest[i],mycompare);

  dispTree(pt,mydisp);

  return 0;
}