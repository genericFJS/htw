#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lendlibitem.h"
#include "lendlibin.h"
#include "lendlibout.h"

theLib myLib = {NULL, NULL, 0, 0};	///< Die Bibiliothek der ausgeliehenen Medien
lItem *myItems = NULL, *myItemst;
int myItemsCount = 0;
medium *myMedia = NULL, *myMediat;
int myMediaCount = 0;

void initLib(){	
	myLib.first = malloc (sizeof(lItem));
	myLib.curr = malloc (sizeof(lItem));
}

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
	if ( myMedia == NULL ){
		myMedia = malloc (sizeof(medium));
		if ( myMedia == 0 ){
			libprint(error, MALLOCERR);
			exit(-1);
		}
	} else{
		myMediat = realloc (myMedia, (myMediaCount+1)*sizeof(medium));
		if (myMediat){
			myMedia = myMediat;
		} else{
			libprint(error, MALLOCERR);
			exit(-1);
		}
	}
	medium nMedia = {};
	///- Type festlegen
	libprint(status, "Schreibe Typ: %d", ntype);
	nMedia.type = ntype;
	///- Titel festlegen
	libprint(status, "Schreibe Titel: %s", ntitle);
	nMedia.title = malloc (strlen(ntitle)+1);
	if ( nMedia.title == 0){
		libprint(error, MALLOCERR);
		exit(-1);
	}
	strcpy(nMedia.title, ntitle);
	///- Interpret/Autor festlegen
	libprint(status, "Schreibe Interpret/Autor: %s", nauthor);
	nMedia.author = malloc (strlen(nauthor)+1);
	if ( nMedia.author == 0){
		libprint(error, MALLOCERR);
		exit(-1);
	}
	strcpy(nMedia.author, nauthor);
	///- Leihendem festlegen
	libprint(status, "Schreibe Leihendem: %s", nlendee);
	nMedia.lendee = malloc (strlen(nlendee)+1);
	if ( nMedia.lendee == 0){
		libprint(error, MALLOCERR);
		exit(-1);
	}
	strcpy(nMedia.lendee, nlendee);
	
	*(myMedia+myMediaCount) = nMedia;
	medium *retMedia = myMedia+myMediaCount;
	
	myMediaCount++;	
	return retMedia;
}

/**
 * @ingroup LendLibItem
 * @brief Erstellt neuen Medieneintrag aus Dateizeile
 * @param libitem Die Datei
 * @return Gibt das erstellte ::medium zurück
 */
medium* createItemF(FILE *libitem){	
	if ( myMedia == NULL ){
		myMedia = malloc (sizeof(medium));
		if ( myMedia == 0 ){
			libprint(error, MALLOCERR);
			exit(-1);
		}
	} else{
		myMediat = realloc (myMedia, (myMediaCount+1)*sizeof(medium));
		if (myMediat){
			myMedia = myMediat;
		} else{
			libprint(error, MALLOCERR);
			exit(-1);
		}
	}
	medium nMedia = {};
	char *entry;
	if ( fgets(vbuf, 128, libitem)){
		///- Type festlegen
		entry = strtok2(vbuf, ";\n");
		libprint(status, "Lese Typ aus: %d", atoi(entry));
		if (vbuf == NULL){
			nMedia.type = other;
		}else {
			nMedia.type = atoi(vbuf);
		}
		///- Titel festlegen
		entry = strtok2(NULL, ";\n");
		libprint(status, "Lese Titel aus: %s", entry);
		if (entry == NULL){
			libprint(error, "Datei ungültig formatiert");
			exit(-1);
		}
		nMedia.title = malloc (strlen(entry)+1);
		if ( nMedia.title == 0){
			libprint(error, MALLOCERR);
			exit(-1);
		}
		strcpy(nMedia.title, entry);
		///- Interpret/Autor festlegen
		entry = strtok2(NULL, ";\n");
		libprint(status, "Lese Interpret/Autor aus: %s", entry);
		nMedia.author = malloc (strlen(entry)+1);
		if ( nMedia.author == 0){
			libprint(error, MALLOCERR);
			exit(-1);
		}
		strcpy(nMedia.author, entry);
		///- Leihendem festlegen
		entry = strtok2(NULL, ";\n");
		libprint(status, "Lese Leihendem aus: %s", entry);
		if (entry == NULL){
			libprint(error, "Datei ungültig formatiert");
			exit(-1);
		}
		nMedia.lendee = malloc (strlen(entry)+1);
		if ( nMedia.lendee == 0){
			libprint(error, MALLOCERR);
			exit(-1);
		}
		strcpy(nMedia.lendee, entry);
	}
	*(myMedia+myMediaCount) = nMedia;
	medium *retMedia = myMedia+myMediaCount;
	
	myMediaCount++;	
	
	int i;
	for (i = 0; i < myMediaCount; i++)
	libprint(extra, "%1.1d  %33.33s  %20.20s  %20.20s", (myMedia+i)->type, (myMedia+i)->title, (myMedia+i)->author, (myMedia+i)->lendee);
	
	return retMedia;
}

/**
 * @ingroup LendLibItem
 * @brief Fügt Medium in Liste ein
 * @param iMedium Das einzufügende Medium
 */
void insertItem(medium *nMedium){
	libprint(error, "===== Füge ein: %x =====", nMedium);
// 	libprint(error, "Aufruf insert");
	///- Listenobjekt erstellen und Inhalt zuweisen
	if ( myItems == NULL ){
		myItems = malloc (sizeof(lItem));
		if ( myItems == 0 ){
			libprint(error, MALLOCERR);
			exit(-1);
		}
	} else{
		myItemst = realloc (myItems, (myItemsCount+1)*sizeof(lItem));
		if (myItemst){
			myItems = myItemst;
		} else{
			libprint(error, MALLOCERR);
			exit(-1);
		}
	}
// 	libprint(error, "malloc fertig");
	lItem nItem = {};	
	nItem.item = nMedium;
	*(myItems+myItemsCount) = nItem;
	lItem *pItem = myItems+myItemsCount;
	libprint(error, "Zuweisung fertig");
	libprint(error, "%d", myLib.size);
	libprint(error, "%s", (myItems->item)->lendee);
	libprint(error, "%s", (myItems+myItemsCount)->item->lendee);
	
// 	int i;
// 	for (i = 0; i < myItemsCount; i++)
// 	libprint(out, "%1.1d  %40.40s  %20.20s  %20.20s" /*\n prev:%10s next:%10s"*/, (myItems+i)->item->type, (myItems+i)->item->title, (myItems+i)->item->author, (myItems+i)->item->lendee);//, (myItems+i)->prev->item->lendee, (myItems+i)->next->item->lendee);
	
	///- Falls Liste noch leer, Bibliothek initialisieren
	if (myLib.size == 0){
		nItem.prev = nItem.next = pItem;
		myLib.size = 1;
		myLib.first = pItem;
		myLib.curr = pItem;
		libprint(error, "1st lendee: %s", myLib.curr->item->lendee);
		libprint(error, "1st size: %d", myLib.size);
	} else {///- Ansonsten neues Objekt in Liste einfügen
		exit(1);
		int i;
// 		libprint(error, "%s < %s", myLib.first->item->title, nMedium.title);
		libprint(error, "hier size %d", myLib.size);
		libprint(error, "hier first %s", myLib.first->item->lendee);
		libprint(error, "hier curr  %s", myLib.curr->item->lendee);
		myLib.curr = myLib.first;
		for (i = 0; i < myLib.size; i++){
			if ( myLib.sort == 0){
				if ( strcmp(myLib.curr->item->title, nMedium->title) <= 0){
					libprint(error, "nein");
				} else {
					libprint(error, "ja");
					if (myLib.size == 1){
						libprint(error, "einfügen");
						myLib.curr->next = pItem;
						myLib.curr->prev = pItem;
						nItem.next = nItem.prev = myLib.curr;
					}else {
						nItem.prev = myLib.curr;
						nItem.next = myLib.curr->next;
						myLib.curr->next->prev = pItem;
						myLib.curr->next = pItem;
					}
					break;
				}
			}
			libprint(error, "weiter");
			myLib.curr = myLib.curr->next->next;
		}
		myLib.size++;
	}
// 	libprint(error, "next: %s | prev: %s", myLib.curr->next->item->lendee, myLib.curr->prev->item->lendee);	
		
	*(myItems+myItemsCount) = nItem;
	pItem = myItems+myItemsCount;
	myItemsCount++;
	
	printItems();
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
void sortItems(sBy sortBy){}

/**
 * @ingroup LendLibItem
 * @brief Suche, bzw. finde ein ausgeliehenes Medium
 * @param sItem Nach dieser Zeichenkette soll gesucht werden
 * @param findBy Die Zeichenkette soll in diesem Eintrag des ausgeliehen Mediums gesucht werden (::sBy)
 * @return Gibt das gefundene Medium zurück
 */
medium findItem(char *sItem, sBy findBy){}

/**
 * @ingroup LendLibItem
 * @brief Den gesamten Speicher freigeben
 */
void freeAll(){}