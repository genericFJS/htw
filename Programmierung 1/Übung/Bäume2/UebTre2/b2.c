#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* vdata[]={"Franz","Paul","Peter","Max","Tobias","Felix",
               "Eric","Alex","Nico","Tereza","Binja", "Alex"};
typedef struct LEAF
{
  struct LEAF* px[2];
  void*  pdata;
}tleaf;

tleaf leafNull={NULL,NULL,NULL};
int mystrcmp(void*p1,void*p2)
{
  return strcmp((char*)p1,(char*)p2)>0?0:1;
}

void addToTree(tleaf* tree, void*pdata, int (*fc)(void*,void*))
{
  if(tree->pdata==NULL)tree->pdata=pdata;
  else
  {
    int i=fc(tree->pdata,pdata);//0/1 links oder rechts
    {
      if(tree->px[i]==NULL)
        {tree->px[i]=malloc(sizeof (tleaf)); *(tree->px[i])=leafNull;}
      addToTree(tree->px[i],pdata,fc);
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
    dispTree(tree->px[0],pd);
    pd(tree->pdata);
    dispTree(tree->px[1],pd);
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