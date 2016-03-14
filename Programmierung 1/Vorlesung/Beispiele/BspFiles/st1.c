/*
 * Verwendung von malloc/realloc:
 * Speicher nach Bedarf aus dem heap
 * void* generische Pointer
 * - nicht dereferenzierbar
 * - zuweisungskompatibel zu jedem getypten Pointer
 * - keine Arithmetik 
 * */

#include <stdio.h>
#include <stdlib.h>
#include "st1f.h"
#include "st1io.h"

FILE* pf;
int anz=0;
char vbuf[128];
char weiter='y';

tStud s;

int main()
{
   int i;
   tStud* ps=NULL, *psx;
   // Einlesen aus Datei
   pf=fopen("Studs.csv","rt");
   if (pf)
   {
     anz=getAnz(pf);
     ps=malloc(anz*sizeof(tStud));
     if(ps==0){puts("malloc hat nicht geklappt"); exit(-1);}
     for (i=0;i<anz;i++)*(ps+i)=readStud(pf);
   }
   
   while (weiter=='y')
   {
     s=getStud2();
     if(ps==NULL)
     {
       ps=malloc(sizeof(tStud)); // Malloc Speicher aus dem heap
       if (ps==NULL){puts("malloc hat nicht geklappt"); exit(-1);}
     }
     else
     {
       psx=realloc(ps,(anz+1)*sizeof(tStud));
       if(psx)
       {
	 ps=psx;
       }else {puts("realloc hat nicht geklappt"); exit(-1);}
     }
     *(ps+anz)=s; anz++;
     for (i=0; i<anz;i++)
     {
       putStudp(ps+i);
//        printf("i: %d, ps+i; %p sizeof: %lu %02lx\n",i,ps +i,sizeof(tStud),sizeof(tStud));
     }
     printf("next (y/n): ");
     fgets(vbuf,128,stdin);weiter=vbuf[0];
   }
   pf=fopen("Studs.csv","wt");
   if(pf)
    for (i=0; i<anz;i++)
    {
      writeStud(pf,ps+i);
    }    for (i=0; i<anz;i++)
   for (i=0; i<anz;i++)
   {
     free((ps+i)->name);
   }
   free(ps);
  return 0;
}