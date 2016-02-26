#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tLEAF
{
  struct tLEAF* p[2];
  void*  pData;
}tleaf;

int cmpstr(void* p1,void*p2)
{
  return strcmp((char*)p1,(char*)p2)>=0?1:0;
}

tleaf EmptyLeaf;

char* vdata[]=
{"Hans","Max","Moritz","Lempel","Bolte","Helene","Antonius"};

void addToTree(tleaf* tree, void*pdata, int (*fc)(void*,void*))
{
  if(tree->pData==NULL) tree->pData=pdata;
  else
  {
    int lr=fc(pdata,tree->pData);
    if(tree->p[lr]==NULL)
    {tree->p[lr]=malloc(sizeof(tleaf));*tree->p[lr]=EmptyLeaf;}
    addToTree(tree->p[lr],pdata,fc);
  }
}

void printStr(void* pstr)
{
  puts((char*)pstr);
}

void dispTree (tleaf* tree, void (*pd)(void*))
{
  if(tree->p[0]) dispTree(tree->p[0],pd);
  pd(tree->pData);
  if(tree->p[1]) dispTree(tree->p[1],pd);
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