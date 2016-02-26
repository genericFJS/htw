#include <stdlib.h>

#include "list.h"

tlist * createList(void)
{
  tlist* plist=malloc(sizeof(tlist));
  if (plist)plist->phead=plist->ptail=plist->pcurr=NULL;
  return plist;
}

int    insertTail    (tlist* plist, void *pItemIns)
{
  tcnct *ptmp=malloc(sizeof(tcnct));
  if(ptmp)
  {
    ptmp->pdata=pItemIns;
    ptmp->pnxt =NULL;
    if(plist->ptail) plist->ptail->pnxt=ptmp;
    else             plist->phead=ptmp;
    plist->ptail=ptmp;
    plist->pcurr=ptmp;
  }
  return (int)(long)ptmp;
}

void*  getFirst      (tlist* plist)
{
  tcnct* ptmp;
  if(plist->phead)
  {
    ptmp=plist->phead;
    plist->pcurr=ptmp;
    return ptmp->pdata;
  }
  return NULL;
}

void*  getNext       (tlist* plist)
{
  if(plist->pcurr)
  {
    plist->pcurr=plist->pcurr->pnxt;   
    if (plist->pcurr)
      return plist->pcurr->pdata;
  }
  return NULL;
}