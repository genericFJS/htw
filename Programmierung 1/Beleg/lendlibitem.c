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
	medium nItem = {};
	nItem.type = ntype;
	nItem.title = ntitle;
	nItem.author = nauthor;
	nItem.lendee = nlendee;
	medium *rItem = &nItem;
	return rItem;
}

/**
 * @ingroup LendLibItem
 * @brief Erstellt neuen Medieneintrag aus Dateizeile
 * @param libitem Die Datei
 * @return Gibt das erstellte ::medium zurück
 */
medium* createItemF(FILE *libitem){				
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
		if ( nMedia.title == NULL){
			libprint(error, MALLOCERR);
			exit(-1);
		}
// 		libprint(status, "Kurz vorm Kopieren des Titels: %d", strlen(entry));
		strcpy(nMedia.title, entry);
// 		libprint(out, "Titel eingetragen: %s ", nMedia.title);
		///- Interpret/Autor festlegen
		entry = strtok2(NULL, ";\n");
		libprint(status, "Lese Interpret/Autor aus: %s", entry);
		nMedia.author = malloc (strlen(entry)+1);
		if ( nMedia.author == NULL){
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
		if ( nMedia.lendee == NULL){
			libprint(error, MALLOCERR);
			exit(-1);
		}
		strcpy(nMedia.lendee, entry);
// 		libprint(out, "Leihender eingetragen: %s ", nMedia.lendee);
	}
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
	*(myMedia+myMediaCount) = nMedia;
	myMediaCount++;
	int i;
	return myMedia+myMediaCount;
}

/**
 * @ingroup LendLibItem
 * @brief Fügt Medium in Liste ein
 * @param iMedium Das einzufügende Medium
 */
void insertItem(medium *nMedium){
// 	///- Listenobjekt erstellen und Inhalt zuweisen
// 	if ( myItems == NULL ){
// 		myItems = malloc (sizeof(lItem));
// 		if ( myItems == 0 ){
// 			libprint(error, MALLOCERR);
// 			exit(-1);
// 		}
// 	} else{
// 		myItemst = realloc (myItems, (myItemsCount+1)*sizeof(lItem));
// 		if (myItemst){
// 			myItems = myItemst;
// 		} else{
// 			libprint(error, MALLOCERR);
// 			exit(-1);
// 		}
// 	}
// 	lItem nItem = {};
// 	nItem.item = nMedium;
// 	*(myItems+myItemsCount) = nItem;
// 	myItemsCount++;
// 	
// 	///- Falls Liste noch leer, Bibliothek initialisieren
// 	if (myLib.size == 0){
// 		nItem.prev = nItem.next = &nItem;
// 		myLib.size = 1;
// 		myLib.first = &nItem;
// 		myLib.curr = &nItem;
// 		nItem.next = &nItem;
// 		nItem.prev = &nItem;
// 	} else {///- Ansonsten neues Objekt in Liste einfügen
// 		int i;
// // 		libprint(error, "%s < %s", myLib.first->item->title, nMedium.title);
// 		myLib.curr = myLib.first;
// 		for (i = 0; i < myLib.size; i++){
// 			if ( myLib.sort == 0){
// 				if ( strcmp(myLib.curr->item->title, nMedium->title) <= 0){
// 					libprint(error, "nein");
// 				} else {
// 					libprint(error, "ja");
// 					if (myLib.size == 1){
// 						libprint(error, "einfügen");
// 						myLib.curr->next = &nItem;
// 						myLib.curr->prev = &nItem;
// 						nItem.next = nItem.prev = myLib.curr;
// 					}else {
// 						nItem.prev = myLib.curr;
// 						nItem.next = myLib.curr->next;
// 						myLib.curr->next->prev = &nItem;
// 						myLib.curr->next = &nItem;
// 					}
// 					break;
// 				}
// 			}
// 			libprint(error, "weiter");
// 			myLib.curr = myLib.curr->next->next;
// 		}
// 		myLib.size++;
// 	}
// // 	libprint(error, "next: %s | prev: %s", myLib.curr->next->item->lendee, myLib.curr->prev->item->lendee);
// 	printItems();
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