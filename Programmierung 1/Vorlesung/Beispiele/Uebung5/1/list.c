#include <stdlib.h>

#include "list.h"



tlist * createList(void)
{
  tlist * plist=malloc(sizeof (tlist));
  if(plist)
  plist->phead=plist->ptail=plist->pcurr=NULL;
  return plist;
}
int insertHead(tlist* plist, void *pitem)/* fuege vorn ein      */
{
  tcnct* pcnct=malloc(sizeof (tcnct));
  if (pcnct)
  {
    pcnct->pnxt =plist->phead; //1
    plist->phead=pcnct;        //2
    if(plist->ptail==NULL) plist->ptail=pcnct;
    pcnct->pdata=pitem;
  }
  return (int)pcnct;
}

void* getFirst(tlist* plist)                /* gib ersten DS       */
{
  plist->pcurr=plist->phead;
  if (plist->phead==NULL)return NULL;
  return plist->phead->pdata;
}
void* getNext (tlist* plist)               /* gib ersten DS       */
{
  tcnct *pcnct;
  if(plist->pcurr)
  {
    plist->pcurr=plist->pcurr->pnxt;
    if (plist->pcurr) return plist->pcurr->pdata;
  }
  return NULL;
}