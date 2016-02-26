#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* vdata[]={"Franz","Paul","Peter","Max","Tobias","Felix",
               "Eric","Alex","Nico","Tereza","Binja"};
typedef struct LEAF
{
  struct LEAF* pl;
  struct LEAF* pr;
  void*  pdata;
}tleaf;

tleaf leafNull={NULL,NULL,NULL};
int mystrcmp(void*p1,void*p2)
{
  return strcmp((char*)p1,(char*)p2);
}

void addToTree(tleaf* tree, void*pdata, int (*fc)(void*,void*))
{
  if(tree->pdata==NULL)tree->pdata=pdata;
  else
  {
    if(fc(tree->pdata,pdata)<0)//rechts
    {
      if(tree->pr==NULL)
        {tree->pr=malloc(sizeof (tleaf)); *(tree->pr)=leafNull;}
      addToTree(tree->pr,pdata,fc);
    }
    else				   // links
    {
      if(tree->pl==NULL)
        {tree->pl=malloc(sizeof (tleaf)); *(tree->pl)=leafNull;}
      addToTree(tree->pl,pdata,fc);
    }
  }
}

void dispStr(void* pdata)
{
  puts((char*)pdata);
}

void dispTree(tleaf* tree, void (*pd)(void*))
{
  if (tree)
  {
    dispTree(tree->pl,pd);
    pd(tree->pdata);
    dispTree(tree->pr,pd);
  }
}

tleaf *root;
int main()
{
  int i;
  root=malloc(sizeof(tleaf));
 *root=leafNull;
  for (i=0;i<sizeof vdata/sizeof (void*);i++)
    addToTree(root,vdata[i],mystrcmp);
  dispTree(root,dispStr);
}