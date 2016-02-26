#include <stdlib.h>
#include <stdio.h>
#include "lendlibin.h"
#include "lendlibout.h"

/**
 * @ingroup LendLibIn
 * @brief Liest Verleihmediendaten aus Datei aus
 */
void readfile(){
	libprint(status, "Datei wird geöffnet");
	libdb=fopen("CSVFILE","rt");
	if (libdb){
		libprint(status, "Datei wird gelesen");
 		listSize=getSize(libdb);
		ps=malloc(anz*sizeof(tStud));
		if(ps==0){puts("malloc hat nicht geklappt"); exit(-1);}
		for (i=0;i<anz;i++)*(ps+i)=readStud(pf);
	} else{
		libprint(status, "Datei wurde nicht gefunden");
	}
}

/**
 * @ingroup LendLibIn
 * @brief Gibt Größe der gespeicherten CSV-Datenbank aus
 * @param libdb Eine Datei
 * @return Anzahl von Linien (also Einträgen)
 * 
 * Quelle: http://stackoverflow.com/a/1910795
 */
int getSize(FILE *libdb){
	int c, c2, n = 0;
	do{	///- Anzahl der Zeilenumbrüche zählen
		c2 = c;
		c = fgetc(libdb);
		if(c == '\n')
			n++;
	} while (c != EOF);
	///- Im Fall, dass die letzte Zeile keinen Umbruch enthält oder leer ist (bis auf den Umbruch), wird diese dazu gezählt oder eben nicht
	if (c != '\n' && n != 0 && c2 != '\n'){
		n++;
	} 	
	return n;
}