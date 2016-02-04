//#include "xalloc.h"
/* list.h */
/*------------------------------------------------------------------------*/
/* Datenstruktur eines Listenverbindungselementes                         */

typedef struct Cnctr
{
  struct Cnctr *pNxt;    /* Pointer auf naechstes Verbindungselement      */
  struct Cnctr *pPrv;    /* Pointer auf vorheriges Verbindungselement     */
  void         *pItem;   /* Pointer auf Daten                             */
}tCnct;

typedef tCnct tList;

#define pCurr pItem
#define pHead pNxt
#define pTail pPrv
#define OK 1
#define FAIL 0
/*-------------------------------------------------------------------------*/
/* Prototypen fuer die Funktionen                                          */

tList * CreateList(void);                           /* erzeuge leere Liste */
int     DeleteList(tList* pList);                   /* loesche leere Liste */

int    InsertBehind  (tList* pList, void *pItemIns);/* fuege ein hinter %  */
int    InsertBefore  (tList* pList, void *pItemIns);/* fuege ein vor    %  */
int    InsertHead    (tList* pList, void *pItemIns);/* fuege vorn ein      */
int    InsertTail    (tList* pList, void *pItemIns);/* fuege hinten ein    */
void   RemoveItem    (tList* pList);                /* loesche %           */

void* chgItemInList  (tList* pList,void*pItem);
void* GetSelected    (tList* pList);                /* gib aktuellen DS    */
void* GetFirst       (tList* pList);                /* gib ersten DS       */
void* GetLast        (tList* pList);                /* gib letzten DS      */
void* GetNext        (tList* pList);                /* gib naechsten DS    */
void* GetPrev        (tList* pList);                /* gib vorigen DS      */
void* GetIndexed   (tList* pList,int Idx);          /* gib DS lt. Index    */

void* addItemToList (tList* pList, 
                     void * pItem,
                     int(*fcmp)(void*pItList,void*pItNew));

/* % steht fuer aktuellen Satz                                             */


