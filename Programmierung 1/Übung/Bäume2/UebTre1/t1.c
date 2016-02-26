#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tLEAF
{
  struct tLEAF* pl;
  struct tLEAF* pr;
  void*  pdata;
}tleaf;

char *vData[]={"Peter","Marcus","Christian","Harry","Alex","Liesa",
               "Claus","Ronny","Horst","Marie","Tom","Nobody"};

tleaf LeafNULL={NULL,NULL,NULL};
int cmpStr(void*p1,void*p2)
{
  return strcmp((char*)p1,(char*)p2);
}
void addToTree(tleaf *pTree, void * pItem, int (*fcmp)(void*,void*))
{
  if (pTree->pdata==NULL)pTree->pdata=pItem;
  else
  {
    if(fcmp(pTree->pdata,pItem)>0)//Links
    {
      if(pTree->pl==NULL) {pTree->pl=malloc(sizeof (tleaf));
                                     *(pTree->pl)=LeafNULL;}
      addToTree(pTree->pl,pItem,cmpStr);     
    }
    else                            //Rechts
    {
      if(pTree->pr==NULL) {pTree->pr=malloc(sizeof (tleaf));
                                     *(pTree->pr)=LeafNULL;}
      addToTree(pTree->pr,pItem,cmpStr);
    }
  }
    
}

void printStr(void*pdata)
{
  puts((char*)pdata);
}

void dispTree(tleaf*pTree, void(*pprint)(void*))
{
  if(pTree)
  {
    dispTree(pTree->pl,pprint);
    pprint((char*)pTree->pdata);
    dispTree(pTree->pr,pprint);
  }
}

tleaf* pTree;

int main()
{
   int i;
   pTree=malloc(sizeof (tleaf));
  *pTree=LeafNULL; 
   for (i=0; i<sizeof(vData)/sizeof(void*); i++)
    addToTree(pTree,vData[i],cmpStr);
   dispTree(pTree,printStr);
}