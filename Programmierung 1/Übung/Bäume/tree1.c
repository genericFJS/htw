#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tLEAF
{
  struct tLEAF* pl;
  struct tLEAF* pr;
  void*  pData;
}tleaf;

int cmpstr(void* p1,void*p2)
{
  return strcmp((char*)p1,(char*)p2)>=0?1:0;
}

tleaf EmptyLeaf={0};

char* vdata[]=
{"Hans","Max","Moritz","Lempel","Bolte","Helene","Antonius"};

void addToTree(tleaf* tree, void*pdata, int (*fc)(void*,void*))
{
  if(tree->pData==NULL) tree->pData=pdata;
  else
  {
    if(fc(pdata,tree->pData))
      //rechts
    {
      if(tree->pr==NULL)
      {tree->pr=malloc(sizeof(tleaf));*tree->pr=EmptyLeaf;}
      addToTree(tree->pr,pdata,fc);
    }
    else
      //link
    { 
      if(tree->pl==NULL)
      {tree->pl=malloc(sizeof(tleaf));*tree->pl=EmptyLeaf;}
      addToTree(tree->pl,pdata,fc);
    }
  }
}

void printStr(void* pstr)
{
  puts((char*)pstr);
}

void dispTree (tleaf* tree, void (*pd)(void*))
{
  if(tree->pl) dispTree(tree->pl,pd);
  pd(tree->pData);
  if(tree->pr) dispTree(tree->pr,pd);
}

// {
//   if(tree)
//   {
//     dispTree(tree->pl);
//     pd(tree->pData);
//     dispTree(tree->pr);
//   }
// }


tleaf* ptree;
 char buf[128];
 char *p;
int main()
{
  int i;
  ptree=malloc(sizeof(tleaf));
  *ptree=EmptyLeaf;
  for (i=0;i<sizeof(vdata)/sizeof(char*);i++)
  {
    addToTree(ptree,vdata[i],cmpstr);
  }
  dispTree(ptree,printStr);
  while(1)
  {
    fgets(buf,128,stdin);
    buf[strlen(buf)-1]=0;
    p=malloc(strlen(buf)+1);
    strcpy(p,buf);
    addToTree(ptree,p,cmpstr);
    dispTree(ptree,printStr);
    puts("-------------------");
  }
  return 0;
}