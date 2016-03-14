/* list.h */

#define OK 1
#define FAIL 0
/*-------------------------------------------------------------------------*/
/* Prototypen fuer die Funktionen                                          */


typedef struct 
{
  tcnct* phead;
  tcnct* ptail;
  tcnct* pcurr;
}tlist;


tlist * CreateList(void);                           /* erzeuge leere Liste */
int     DeleteList(tlist* pList);                   /* loesche leere Liste */

int    insertBehind  (tlist* pList, void *pItemIns);/* fuege ein hinter %  */
int    insertBefore  (tlist* pList, void *pItemIns);/* fuege ein vor    %  */
int    insertHead    (tlist* pList, void *pItemIns);/* fuege vorn ein      */
int    insertTail    (tlist* pList, void *pItemIns);/* fuege hinten ein    */
int    removeItem    (tlist* pList);                /* loesche %           */

void*  getSelected   (tlist* pList);                /* gib aktuellen DS    */
void*  getFirst      (tlist* pList);                /* gib ersten DS       */
void*  getLast       (tlist* pList);                /* gib letzten DS      */
void*  getNext       (tlist* pList);                /* gib naechsten DS    */
void*  getPrev       (tlist* pList);                /* gib vorigen DS      */
void*  getIndexed    (tlist* pList,int Idx);        /* gib DS lt. Index    */

int    addItemToList (tlist* pList, 
                     void * pItem,
                     int(*fcmp)(void*pItlist,void*pItNew));

/* % steht fuer aktuellen Satz                                             */


