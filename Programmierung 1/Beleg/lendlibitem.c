#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lendlibitem.h"
#include "lendlibin.h"
#include "lendlibout.h"

theLib myLib = {NULL, NULL, 0, 0};	///< Die Bibiliothek der ausgeliehenen Medien

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
		///- Type festlegen
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
	if ( myLib.sort == (sBy) title){
		if (myLib.size == 0){	///- Falls Liste noch leer, diese initialisieren
			libprint(status, "1. Element einfügen.");
			nItem->prev = nItem->next = nItem;
			myLib.first = nItem;
			myLib.curr = nItem;
		} else if (myLib.size == 1){	///- Falls Liste einelementig ist, das nächste Element einfach einfügen
			libprint(status,"2. Element einfügen.");
			myLib.curr->next = nItem;
			myLib.curr->prev = nItem;
			nItem->next = nItem->prev = myLib.curr;
			if ( strcmp(myLib.curr->item->title, nMedium->title) > 0 )
				myLib.first = nItem;
		} else{///- Alle anderen Elemente sortiert in Liste einfügen
			int i;
			myLib.curr = myLib.first;
			for (i = 0; i < myLib.size; i++){
				if ( strcmp(myLib.curr->item->title, nMedium->title) <= 0 && i < myLib.size-1){	///- - Nach einem Element suchen, welches größer ist, damit man das einzufügende Element vor diesem einfügen kann.
					libprint(status,"%10.10s kleiner %10.10s -> weiter nach größerem Suchen.",myLib.curr->item->title, nMedium->title);
					myLib.curr = myLib.curr->next;
				} else if(i < myLib.size-1) {	///- - Wenn größeres vorm Listenende gefunden wurde, Element davor einfügen
					libprint(status,"%10.10s größer %10.10s, also vorher einfügen.",myLib.curr->item->title, nMedium->title);
					nItem->prev = myLib.curr->prev;
					nItem->next = myLib.curr;
					myLib.curr->prev->next = nItem;
					myLib.curr->prev = nItem;
					if (myLib.curr == myLib.first){
						libprint(status,"Eingefügtes Element ist kleinste, wird vorne angefügt. Also erstes Listenelement neu definieren!");
						myLib.first = nItem;
					}
					break;
				} else { ///- - Ansonsten Element am Listenende je nach größe davor oder danach einfügen.
					if (strcmp(myLib.curr->item->title, nMedium->title) > 0){
						libprint(status,"%10.10s kleiner %10.10s, also davor einfügen.", nMedium->title,myLib.curr->item->title);
						nItem->prev = myLib.curr->prev;
						nItem->next = myLib.curr;
						myLib.curr->prev->next = nItem;
						myLib.curr->prev = nItem;
						
					} else {
						libprint(status,"%10.10s größer %10.10s, also danach einfügen.", nMedium->title,myLib.curr->item->title);
						nItem->prev = myLib.curr;
						nItem->next = myLib.curr->next;
						myLib.curr->next->prev = nItem;
						myLib.curr->next = nItem;
					}
					break;
				}
			}
		}
	} else {
		if (myLib.size == 0){	///- Falls Liste noch leer, diese initialisieren
			libprint(status, "1. Element einfügen.");
			nItem->prev = nItem->next = nItem;
			myLib.first = nItem;
			myLib.curr = nItem;
		} else if (myLib.size == 1){	///- Falls Liste einelementig ist, das nächste Element einfach einfügen
			libprint(status,"2. Element einfügen.");
			myLib.curr->next = nItem;
			myLib.curr->prev = nItem;
			nItem->next = nItem->prev = myLib.curr;
			if ( strcmp(myLib.curr->item->lendee, nMedium->lendee) > 0 )
				myLib.first = nItem;
		} else{///- Alle anderen Elemente sortiert in Liste einfügen
			int i;
			myLib.curr = myLib.first;
			for (i = 0; i < myLib.size; i++){
				if ( strcmp(myLib.curr->item->lendee, nMedium->lendee) <= 0 && i < myLib.size-1){	///- - Nach einem Element suchen, welches größer ist, damit man das einzufügende Element vor diesem einfügen kann.
					libprint(status,"%10.10s kleiner %10.10s -> weiter nach größerem Suchen.",myLib.curr->item->lendee, nMedium->lendee);
					myLib.curr = myLib.curr->next;
				} else if(i < myLib.size-1) {	///- - Wenn größeres vorm Listenende gefunden wurde, Element davor einfügen
					libprint(status,"%10.10s größer %10.10s, also vorher einfügen.",myLib.curr->item->lendee, nMedium->lendee);
					nItem->prev = myLib.curr->prev;
					nItem->next = myLib.curr;
					myLib.curr->prev->next = nItem;
					myLib.curr->prev = nItem;
					if (myLib.curr == myLib.first){
						libprint(status,"Eingefügtes Element ist kleinste, wird vorne angefügt. Also erstes Listenelement neu definieren!");
						myLib.first = nItem;
					}
					break;
				} else { ///- - Ansonsten Element am Listenende je nach größe davor oder danach einfügen.
					if (strcmp(myLib.curr->item->lendee, nMedium->lendee) > 0){
						libprint(status,"%10.10s kleiner %10.10s, also davor einfügen.", nMedium->lendee,myLib.curr->item->lendee);
						nItem->prev = myLib.curr->prev;
						nItem->next = myLib.curr;
						myLib.curr->prev->next = nItem;
						myLib.curr->prev = nItem;
						
					} else {
						libprint(status,"%10.10s größer %10.10s, also danach einfügen.", nMedium->lendee,myLib.curr->item->lendee);
						nItem->prev = myLib.curr;
						nItem->next = myLib.curr->next;
						myLib.curr->next->prev = nItem;
						myLib.curr->next = nItem;
					}
					break;
				}
			}
		}
		
	}
	libprint(status, "%s eingefügt.", nMedium->title);	
	myLib.size++;
// 	printItems();
}


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
 * @param iMedium Das zu löschende Medium
 */
void deleteItem(medium *nMedium){}

/**
 * @ingroup LendLibItem
 * @brief Sortiert die Liste nach Mediumtitel/Leihendem
 * @param sortBy Nach was sortiert werden soll (::sBy)
 */
void sortItems(sBy sortBy){
	int i, size;
	size = myLib.size;
	medium *allMedia[size];
	myLib.curr = myLib.first;
	
	for ( i = 0; i < size; i++){
		allMedia[i] = myLib.curr->item;
		if (i < size-1){
			myLib.curr = myLib.curr->next;
			free(myLib.curr->prev);
		} else {
			free(myLib.curr);
		}
	}
	myLib.curr = NULL;
	myLib.first = NULL;
	myLib.sort = sortBy;
	myLib.size = 0;
	for (i = 0; i < size; i++){
		insertItem(allMedia[i]);
	}
	printItems();
}

/**
 * @ingroup LendLibItem
 * @brief Suche, bzw. finde ein ausgeliehenes Medium
 * @param sItem Nach dieser Zeichenkette soll gesucht werden
 * @param findBy Die Zeichenkette soll in diesem Eintrag des ausgeliehen Mediums gesucht werden (::sBy)
 * @return Gibt das gefundene Medium zurück
 */
theLib findItem(char *sItem, sBy findBy){
// 	theLib foundLib = {NULL, NULL, 0, sBy);
}

/**
 * @ingroup LendLibItem
 * @brief Den gesamten Speicher freigeben
 */
void freeAll(){
	int i, size;
	size = myLib.size;
	myLib.curr = myLib.first;
	for (i=0; i<size; i++){
		free(myLib.curr->item->title);
		free(myLib.curr->item->author);
		free(myLib.curr->item->lendee);
		free(myLib.curr->item);
		if (i < size-1){
			myLib.curr = myLib.curr->next;
			free(myLib.curr->prev);
		} else {
			free(myLib.curr);
		}
	}
	libprint(out, "Speicher freigegeben");
}