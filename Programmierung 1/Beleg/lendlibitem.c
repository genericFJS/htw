#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lendlibitem.h"
#include "lendlibin.h"
#include "lendlibout.h"
#define _GNU_SOURCE

theLib *currLib = &myLib;
theLib myLib = {NULL, NULL, 0, 0};	///< Die Bibiliothek der ausgeliehenen Medien
unsigned int idc = 1;

/**
 * @ingroup LendLibItem
 * @brief Erstellt einen neuen Medieneintrag
 * @param ntype Typ des Mediums
 * @param ntitle Titel des Mediums
 * @param nauthor Autor/Interpret des Mediums
 * @param nlendee Person, dem das Medium ausgeliehen wurde
 * @return Gibt das erstellte ::medium zurück
 */
medium* createItem(int ntype, char* ntitle, char* nauthor, char* nlendee){
	libprint(status, "Eintrag für ausgeliehenes Medium wird angelegt");
	medium *nMedia = malloc (sizeof(medium));
	if ( nMedia == 0 ){
		libprint(error, MALLOCERR);
		exit(-1);
	}
	///- Type festlegen
	libprint(status, "Schreibe Typ: %d", ntype);
	nMedia->type = ntype;
	///- Titel festlegen
	libprint(status, "Schreibe Titel: %s", ntitle);
	nMedia->title = malloc (strlen(ntitle)+1);
	if ( nMedia->title == 0){
		libprint(error, MALLOCERR);
		exit(-1);
	}
	strcpy(nMedia->title, ntitle);
	///- Interpret/Autor festlegen
	libprint(status, "Schreibe Interpret/Autor: %s", nauthor);
	nMedia->author = malloc (strlen(nauthor)+1);
	if ( nMedia->author == 0){
		libprint(error, MALLOCERR);
		exit(-1);
	}
	strcpy(nMedia->author, nauthor);
	///- Leihendem festlegen
	libprint(status, "Schreibe Leihendem: %s", nlendee);
	nMedia->lendee = malloc (strlen(nlendee)+1);
	if ( nMedia->lendee == 0){
		libprint(error, MALLOCERR);
		exit(-1);
	}
	strcpy(nMedia->lendee, nlendee);
	
	return nMedia;
}

/**
 * @ingroup LendLibItem
 * @brief Erstellt neuen Medieneintrag aus Dateizeile
 * @param libitem Die Datei
 * @return Gibt das erstellte ::medium zurück
 */
medium* createItemF(FILE *libitem){	
	medium *nMedia = malloc (sizeof(medium));
	if ( nMedia == 0 ){
		libprint(error, MALLOCERR);
		exit(-1);
	}
	char *entry;
	if ( fgets(vbuf, 128, libitem)){
		///- ID festlegen
		libprint(status, "Setze ID:");
		nMedia->id = idc;
		idc++;
		///- Typ festlegen
		entry = strtok2(vbuf, ";\n");
		libprint(status, "Lese Typ aus: %d", atoi(entry));
		if (vbuf == NULL){
			nMedia->type = other;
		}else {
			nMedia->type = atoi(vbuf);
		}
		///- Titel festlegen
		entry = strtok2(NULL, ";\n");
		if (strlen(entry)==0){
			libprint(error, "Konnte Titel nicht lesen. Datei ungültig formatiert!");
			exit(-1);
		}
		libprint(status, "Lese Titel aus: %s", entry);
		nMedia->title = malloc (strlen(entry)+1);
		if ( nMedia->title == 0){
			libprint(error, MALLOCERR);
			exit(-1);
		}
		strcpy(nMedia->title, entry);
		///- Interpret/Autor festlegen
		entry = strtok2(NULL, ";\n");
		libprint(status, "Lese Interpret/Autor aus: %s", entry);
		nMedia->author = malloc (strlen(entry)+1);
		if ( nMedia->author == 0){
			libprint(error, MALLOCERR);
			exit(-1);
		}
		strcpy(nMedia->author, entry);
		///- Leihendem festlegen
		entry = strtok2(NULL, ";\n");
		if (strlen(entry)==0){
			libprint(error, "Konnte Leihenden nicht lesen. Datei ungültig formatiert!");
			exit(-1);
		}
		libprint(status, "Lese Leihendem aus: %s", entry);
		nMedia->lendee = malloc (strlen(entry)+1);
		if ( nMedia->lendee == 0){
			libprint(error, MALLOCERR);
			exit(-1);
		}
		strcpy(nMedia->lendee, entry);
	}
	
	return nMedia;
}

/**
 * @ingroup LendLibItem
 * @brief Fügt Medium in Liste ein
 * @param iMedium Das einzufügende Medium
 */
void insertItem(medium *nMedium, theLib *inLib){
	libprint(status, "Füge Medieneintrag ein: %s", nMedium->title);
	///- Listenobjekt erstellen und Inhalt zuweisen
	lItem *nItem = malloc (sizeof(lItem));
	if ( nItem == 0 ){
		libprint(error, MALLOCERR);
		exit(-1);
	}
	nItem->item = nMedium;		
	if ( inLib->sort == (sBy) title){
		if (inLib->size == 0){	///- Falls Liste noch leer, diese initialisieren
			libprint(status, "1. Element einfügen.");
			nItem->prev = nItem->next = nItem;
			inLib->first = nItem;
			inLib->curr = nItem;
		} else if (inLib->size == 1){	///- Falls Liste einelementig ist, das nächste Element einfach einfügen
			libprint(status,"2. Element einfügen.");
			inLib->curr->next = nItem;
			inLib->curr->prev = nItem;
			nItem->next = nItem->prev = inLib->curr;
			if ( strcicmp(inLib->curr->item->title, nMedium->title) > 0 )
				inLib->first = nItem;
		} else{///- Alle anderen Elemente sortiert in Liste einfügen
			int i;
			inLib->curr = inLib->first;
			for (i = 0; i < inLib->size; i++){
				if ( strcicmp(inLib->curr->item->title, nMedium->title) <= 0 && i < inLib->size-1){	///- - Nach einem Element suchen, welches größer ist, damit man das einzufügende Element vor diesem einfügen kann.
					libprint(status,"%10.10s kleiner %10.10s -> weiter nach größerem Suchen.",inLib->curr->item->title, nMedium->title);
					inLib->curr = inLib->curr->next;
				} else if(i < inLib->size-1) {	///- - Wenn größeres vorm Listenende gefunden wurde, Element davor einfügen
					libprint(status,"%10.10s größer %10.10s, also vorher einfügen.",inLib->curr->item->title, nMedium->title);
					nItem->prev = inLib->curr->prev;
					nItem->next = inLib->curr;
					inLib->curr->prev->next = nItem;
					inLib->curr->prev = nItem;
					if (inLib->curr == inLib->first){
						libprint(status,"Eingefügtes Element ist kleinste, wird vorne angefügt. Also erstes Listenelement neu definieren!");
						inLib->first = nItem;
					}
					break;
				} else { ///- - Ansonsten Element am Listenende je nach größe davor oder danach einfügen.
					if (strcicmp(inLib->curr->item->title, nMedium->title) > 0){
						libprint(status,"%10.10s kleiner %10.10s, also davor einfügen.", nMedium->title,inLib->curr->item->title);
						nItem->prev = inLib->curr->prev;
						nItem->next = inLib->curr;
						inLib->curr->prev->next = nItem;
						inLib->curr->prev = nItem;
						
					} else {
						libprint(status,"%10.10s größer %10.10s, also danach einfügen.", nMedium->title,inLib->curr->item->title);
						nItem->prev = inLib->curr;
						nItem->next = inLib->curr->next;
						inLib->curr->next->prev = nItem;
						inLib->curr->next = nItem;
					}
					break;
				}
			}
		}
	} else {
		if (inLib->size == 0){	///- Falls Liste noch leer, diese initialisieren
			libprint(status, "1. Element einfügen.");
			nItem->prev = nItem->next = nItem;
			inLib->first = nItem;
			inLib->curr = nItem;
		} else if (inLib->size == 1){	///- Falls Liste einelementig ist, das nächste Element einfach einfügen
			libprint(status,"2. Element einfügen.");
			inLib->curr->next = nItem;
			inLib->curr->prev = nItem;
			nItem->next = nItem->prev = inLib->curr;
			if ( strcicmp(inLib->curr->item->lendee, nMedium->lendee) > 0 )
				inLib->first = nItem;
		} else{///- Alle anderen Elemente sortiert in Liste einfügen
			int i;
			inLib->curr = inLib->first;
			for (i = 0; i < inLib->size; i++){
				if ( strcicmp(inLib->curr->item->lendee, nMedium->lendee) <= 0 && i < inLib->size-1){	///- - Nach einem Element suchen, welches größer ist, damit man das einzufügende Element vor diesem einfügen kann.
					libprint(status,"%10.10s kleiner %10.10s -> weiter nach größerem Suchen.",inLib->curr->item->lendee, nMedium->lendee);
					inLib->curr = inLib->curr->next;
				} else if(i < inLib->size-1) {	///- - Wenn größeres vorm Listenende gefunden wurde, Element davor einfügen
					libprint(status,"%10.10s größer %10.10s, also vorher einfügen.",inLib->curr->item->lendee, nMedium->lendee);
					nItem->prev = inLib->curr->prev;
					nItem->next = inLib->curr;
					inLib->curr->prev->next = nItem;
					inLib->curr->prev = nItem;
					if (inLib->curr == inLib->first){
						libprint(status,"Eingefügtes Element ist kleinste, wird vorne angefügt. Also erstes Listenelement neu definieren!");
						inLib->first = nItem;
					}
					break;
				} else { ///- - Ansonsten Element am Listenende je nach größe davor oder danach einfügen.
					if (strcicmp(inLib->curr->item->lendee, nMedium->lendee) > 0){
						libprint(status,"%10.10s kleiner %10.10s, also davor einfügen.", nMedium->lendee,inLib->curr->item->lendee);
						nItem->prev = inLib->curr->prev;
						nItem->next = inLib->curr;
						inLib->curr->prev->next = nItem;
						inLib->curr->prev = nItem;
						
					} else {
						libprint(status,"%10.10s größer %10.10s, also danach einfügen.", nMedium->lendee,inLib->curr->item->lendee);
						nItem->prev = inLib->curr;
						nItem->next = inLib->curr->next;
						inLib->curr->next->prev = nItem;
						inLib->curr->next = nItem;
					}
					break;
				}
			}
		}
		
	}
	libprint(status, "%s eingefügt.", nMedium->title);	
	inLib->size++;
// 	printItems();
}

/**
 * @ingroup LendLibItem
 * @brief Gibt String für enum ::mType aus
 * @param type Zahl von ::mType
 * @return ::mType als String
 */
char* getmType(int type){
	switch (type){
		case 1:
			return "Buch";
		case 2:
			return "CD";
		case 3:
			return "DVD";
		default:
			return "-";
	}
}

/**
 * @ingroup LendLibItem
 * @brief Löscht Medium aus der Liste
 * @param theID Das zu löschende Medium (ID)
 * @param inLib in dieser Liste
 */
void deleteItem(int theID, theLib *inLib){
	int i, succ = 0;
	inLib->curr = inLib->first;
	for (i = 0; i < inLib->size; i++){
		if ( inLib->curr->item->id == theID){
			libprint(status, "Eintrag gefunden.");
			succ = 1;
			break;
		} else{
			inLib->curr = inLib->curr->next;
		}
	}
	if (succ){
		lItem *dItem = inLib->curr;
		if (inLib->first == dItem){
			inLib->first = dItem->next;
		}
		inLib->curr = inLib->first;
		inLib->size--;
		dItem->prev->next = dItem->next;
		dItem->next->prev = dItem->prev;
		free(dItem->item->title);
		free(dItem->item->author);
		free(dItem->item->lendee);
		free(dItem->item);
// 		inLib.curr = inLib.first
		libprint(out, "Eintrag gelöscht.");
	} else {
		libprint(extra, "ID nicht gefunden.");
	}
}

/**
 * @ingroup LendLibItem
 * @brief Sortiert die Liste nach Mediumtitel/Leihendem
 * @param sortBy Nach was sortiert werden soll (::sBy)
 * @param inLib in dieser Liste
 */
void sortItems(sBy sortBy, theLib *inLib){
	int i, size;
	size = inLib->size;
	medium *allMedia[size];
	inLib->curr = inLib->first;
	
	for ( i = 0; i < size; i++){
		allMedia[i] = inLib->curr->item;
		if (i < size-1){
			inLib->curr = inLib->curr->next;
			free(inLib->curr->prev);
		} else {
			free(inLib->curr);
		}
	}
	inLib->curr = NULL;
	inLib->first = NULL;
	inLib->sort = sortBy;
	inLib->size = 0;
	for (i = 0; i < size; i++){
		insertItem(allMedia[i], &myLib);
	}
	printItems();
}

/**
 * @ingroup LendLibItem
 * @brief Suche, bzw. finde ein ausgeliehenes Medium
 * @param sItem Nach dieser Zeichenkette soll gesucht werden
 * @param findBy Die Zeichenkette soll in diesem Eintrag des ausgeliehen Mediums gesucht werden (::sBy)
 * @param inLib in dieser Liste
 * @return Gibt das gefundene Medium zurück
 */
void findItem(char *sItem, sBy findBy, theLib *inLib){
	theLib foundLib = {NULL, NULL, 0, findBy};
	sItem = strtok(sItem, "\n");
	int i, size;
	size = inLib->size;
	inLib->curr = inLib->first;
	if (findBy == (sBy)title){
		for (i = 0; i< size; i++){
			if (strcasestr(inLib->curr->item->title, sItem)!=0){
				libprint(status, "%s enthält %s", inLib->curr->item->title, sItem);
				insertItem( inLib->curr->item, &foundLib );
			}
			inLib->curr = inLib->curr->next;
		}
	}
	currLib = &foundLib;
	printItems();
	currLib = &myLib;
}

/**
 * @ingroup LendLibItem
 * @brief Den gesamten Speicher freigeben
 * @param inLib in dieser Liste
 */
void freeAll(theLib *inLib){
	int i, size;
	size = inLib->size;
	inLib->curr = inLib->first;
	for (i=0; i<size; i++){
		free(inLib->curr->item->title);
		free(inLib->curr->item->author);
		free(inLib->curr->item->lendee);
		free(inLib->curr->item);
		if (i < size-1){
			inLib->curr = inLib->curr->next;
			free(inLib->curr->prev);
		} else {
			free(inLib->curr);
		}
	}
#ifndef CGI
	libprint(out, "Speicher freigegeben");
#endif
}

/**
 * @ingroup LendLibItem
 * @brief Vergleicht zwei "Strings" unabhängig von Groß- oder Kleinbuchstaben
 * Quelle: http://stackoverflow.com/a/5820991
 */
int strcicmp(char const *a, char const *b){
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}