#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TLEAF
{
  struct TLEAF* pl;
  struct TLEAF* pr;
  void *pdata;
}tleaf;
tleaf leafempty={NULL,NULL,NULL};

int mycmp(void* p1, void*p2)
{
  return (strcmp((char*)p1,(char*)p2)<0)?0:1;
}

void addToTree(tleaf*ptree,void*pdata,int(*fcmp)(void*,void*))
{
  if (ptree->pdata==NULL) ptree->pdata=pdata;
  else
  {
    if(!fcmp(ptree->pdata,pdata))
    {
      if (ptree->pr==NULL)
      {
	ptree->pr=malloc(sizeof(tleaf));
        *(ptree->pr)=leafempty;
      }
      addToTree(ptree->pr,pdata,fcmp);
    }
    else
    {
      if (ptree->pl==NULL)
      {
	ptree->pl=malloc(sizeof(tleaf));
        *(ptree->pl)=leafempty;
      }
      addToTree(ptree->pl,pdata,fcmp);
    }
  }
}

void disptree(tleaf*ptree,void (*printdata)(void*))
{
  if (ptree->pl) disptree(ptree->pl,printdata);
  printdata(ptree->pdata);
  if (ptree->pr) disptree(ptree->pr,printdata);
}

void printstr(void*pdata)
{
   puts((char*)pdata);
}

char* vdata[]=
{"Hans","Max","Moritz","Lempel","Bolte","Helene","Antonius"};

tleaf* ptree;

int main()
{
  int i;
  ptree=malloc(sizeof(tleaf));
  *ptree=leafempty;
  for(i=0; i< sizeof(vdata)/sizeof(char*);i++)
    addToTree(ptree,vdata[i],mycmp);
  
  disptree(ptree,printstr);
  return 0;
}