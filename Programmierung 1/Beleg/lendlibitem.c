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
medium createItem(int ntype, char* ntitle, char* nauthor, char* nlendee){
	libprint(status, "Eintrag für ausgeliehenes Medium wird angelegt");
	medium nItem = {};
	nItem.type = ntype;
	nItem.title = ntitle;
	nItem.author = nauthor;
	nItem.lendee = nlendee;
// 	medium *rItem = &nItem;
	return nItem;
}

/**
 * @ingroup LendLibItem
 * @brief Erstellt neuen Medieneintrag aus Dateizeile
 * @param libitem Die Datei
 * @return Gibt das erstellte ::medium zurück
 */
medium createItemF(FILE *libitem){				
	medium nItem = {};
	char *entry;
	if ( fgets(vbuf, 128, libitem)){
		///- Type festlegen
		entry = strtok2(vbuf, ";\n");
		libprint(status, "Lese Typ aus: %d", atoi(entry));
		if (vbuf == NULL){
			nItem.type = other;
		}else {
			nItem.type = atoi(vbuf);
		}
		///- Titel festlegen
		entry = strtok2(NULL, ";\n");
		libprint(status, "Lese Titel aus: %s", entry);
		if (entry == NULL){
			libprint(error, "Datei ungültig formatiert");
			exit(-1);
		}
		nItem.title = malloc (sizeof(entry)+1);
		if ( nItem.title == NULL){
			libprint(error, MALLOCERR);
			exit(-1);
		}
		strcpy(nItem.title, entry);
// 		libprint(out, "Titel eingetragen: %s ", nItem.title);
		///- Interpret/Autor festlegen
		entry = strtok2(NULL, ";\n");
		libprint(status, "Lese Interpret/Autor aus: %s", entry);
		nItem.author = malloc (sizeof(entry)+1);
		if ( nItem.author == NULL){
			libprint(error, MALLOCERR);
			exit(-1);
		}
		strcpy(nItem.author, entry);
		///- Leihendem festlegen
		entry = strtok2(NULL, ";\n");
		libprint(status, "Lese Leihendem aus: %s", entry);
		if (entry == NULL){
			libprint(error, "Datei ungültig formatiert");
			exit(-1);
		}
		nItem.lendee = malloc (sizeof(entry)+1);
		if ( nItem.lendee == NULL){
			libprint(error, MALLOCERR);
			exit(-1);
		}
		strcpy(nItem.lendee, entry);
// 		libprint(out, "Leihender eingetragen: %s ", nItem.lendee);
	}
	if ( myMedia == NULL ){
		myMedia = malloc (sizeof(medium));
		if ( myMedia == 0 ){
			libprint(error, MALLOCERR);
			exit(-1);
		}
	} else{
		libprint(out, "%s %d", nItem.lendee, myMediaCount);
// 		myMediat = realloc (myMedia, (myMediaCount+1)*sizeof(medium));
		if (myMediat = realloc (myMedia, (myMediaCount+1)*sizeof(medium))){
			myMedia = myMediat;
		} else{
			libprint(error, MALLOCERR);
			exit(-1);
		}
	}
	*(myMedia+myMediaCount) = nItem;
	myMediaCount++;
	return *(myMedia+myMediaCount-1);
}

/**
 * @ingroup LendLibItem
 * @brief Fügt Medium in Liste ein
 * @param iMedium Das einzufügende Medium
 */
void insertItem(medium nMedium){
	/*
	///- Listenobjekt erstellen und Inhalt zuweisen
	libprint(out, "inserting Item");
	lItem *nItem = malloc(sizeof(lItem));
	if ( nItem == NULL){
		libprint(error, MALLOCERR);
		exit(-1);
	}
	nItem->item = &nMedium;
	///- Falls Liste noch leer, Bibliothek initialisieren
	if (myLib.size == 0){
		nItem->prev = nItem->next = nItem;
		myLib.size = 1;
		myLib.first = nItem;
		myLib.curr = nItem;
		libprint(out, "%s", nMedium.title);
	} else {///- Ansonsten neues Objekt in Liste einfügen
		int i;
		myLib.curr = myLib.first;
		for (i = 0; i < myLib.size; i++){
			libprint(out, "%s", nMedium.title);
// 			if (stcrcmp((myLib.curr)., 
		}
	}*/
}

/**
 * @ingroup LendLibItem
 * @brief Löscht Medium aus der Liste
 * @param iMedium Das zu löschende Medium
 */
void deleteItem(medium nMedium){}

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