#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lendlibin.h"
#include "lendlibout.h"
#include "lendlibitem.h"

const char *filename = "lendlib.csv";

/**
 * @ingroup LendLibIn
 * @brief Liest Verleihmediendaten aus Datei aus
 */
void readfile(){
	libprint(status, "Datei '%s' wird geöffnet.", filename);
	libdb = fopen(filename,"rt");
	if (libdb){
 		int listSize = getSize(libdb);
		int i;
		for (i=0 ; i < listSize; i++){
// 			libprint(out, "Lese Zeile: %d ", i);
			medium *newMedium = createItemF(libdb);
			insertItem( newMedium, &myLib );
		}
		printItems();
	} else{
		libprint(status, "Datei konnte nicht geöffnet werden.");
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
	int c = EOF, c2, n = 0;
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
	rewind(libdb);
	return n;
}

/**
 * @ingroup LendLibIn
 * @brief Verarbeitet Nutzerinput im Terminal
 */
void getInput(){
	libprint(in, "Wähle Funktion (h für Hilfe): ");
	fgets(vbuf, 128, stdin);
	switch (vbuf[0]){
		case 'h':
			libprint(out, "  Mögliche Funktionen:");
			libprint(out, "l - Ausleihmedien erneut auflisten");
			libprint(out, "c - Ausleihmedium hinzufügen");
			libprint(out, "d - Ausleihmedium löschen");
			libprint(out, "s - Ausleihmedien sortieren");
			libprint(out, "f - Ausleihmedien finden");
			libprint(out, "alle anderen Eingaben beenden das Programm");
			printTLine('~',0); printf("\n");
			getInput();
			break;
		case 'l':
			printItems();
			getInput();
			break;
		case 'c':	/// Ausleihmedium hinzufügen
			libprint(in, "%16s: ", "Medienart");	///- Eingabe Medienart
			fgets(vbuf, 128, stdin);
			int type = vbuf[0];
			mType ntype;
			char *ntitle, *nauthor, *nlendee;
			/// (Festlegung der Medienart durch entsprechende Zahl aus mType oder Anfangsbuchstabe: Buch, Cd, Dvd)
			switch (type){
				case 'b':
				case 'B':
				case 1:
					libprint(out, "Medium ist Buch.");
					ntype = book;
					break;
				case 'c':
				case 'C':
				case 2:
					libprint(out, "Medium ist CD.");
					ntype = cd;
					break;
				case 'd':
				case 'D':
				case 3:
					libprint(out, "Medium ist DVD.");
					ntype = dvd;
					break;
				default:
					libprint(out, "Medium ist anderer oder unbestimmt.");
					ntype = other;
					break;
			}
			libprint(in, "%16s: ", "Medientitel");
			fgets(vbuf, 128, stdin);
			while (strlen(vbuf) < 2){
				libprint(out, "Bitte einen Medientitel angeben!");
				libprint(in, "%16s: ", "Medientitel");
				fgets(vbuf, 128, stdin);				
			}	
			vbuf[strlen(vbuf)-1]=0;
			ntitle = malloc (strlen(vbuf)+1);
			if ( ntitle == NULL){
				libprint(error, MALLOCERR);
				exit(-1);
			}
			strcpy(ntitle, vbuf);
			libprint(out, "Titel ist '%s'.", ntitle);
			libprint(in, "%16s: ", "Interpret/Autor");
			fgets(vbuf, 128, stdin);	
			vbuf[strlen(vbuf)-1]=0;
			nauthor = malloc (strlen(vbuf)+1);
			if ( nauthor == NULL){
				libprint(error, MALLOCERR);
				exit(-1);
			}
			strcpy(nauthor, vbuf);
			if (strlen(vbuf) != 0)
				libprint(out, "Interpret/Autor ist '%s'.", nauthor);
			libprint(in, "%16s: ", "Ausgeliehen an");
			fgets(vbuf, 128, stdin);
			while (strlen(vbuf) < 2){
				libprint(out, "Bitte Person angeben, an die das Medium ausgeliehen wurde!");
				libprint(in, "%16s: ", "Ausgeliehen an");
				fgets(vbuf, 128, stdin);				
			}
			vbuf[strlen(vbuf)-1]=0;
			nlendee = malloc (strlen(vbuf)+1);
			if ( nlendee == NULL){
				libprint(error, MALLOCERR);
				exit(-1);
			}
			strcpy(nlendee, vbuf);
			libprint(out, "Ausgeliehen an '%s'.", nlendee);
			
			
			medium *newMedium = createItem(ntype, ntitle, nauthor, nlendee);
			insertItem( newMedium, &myLib );
			printTLine('~',0); printf("\n");			
			printItems();
			
			getInput();
			break;
		case 's':	/// Medien sortieren
			libprint(in, "Sortieren nach (\e[1mT\e[0m\e[32mitel=0, \e[1mA\e[0m\e[32mus\e[1mL\e[0m\e[32meihender=1): ");
			fgets(vbuf, 128, stdin);
			int sortingBy = vbuf[0];
			printTLine('~',0); printf("\n");
			switch (sortingBy){
				case 'a':
				case 'A':
				case 'l':
				case 'L':
				case '1':
					sortItems(1, &myLib);
					break;
				case 't':
				case 'T':
				case '0':
					sortItems(0, &myLib);
				default:
					break;				
			}
			getInput();
			break;
		case 'd':
			libprint(in, "Medium löschen (ID): ");
			fgets(vbuf, 128, stdin);
			deleteItem(atoi(vbuf), &myLib);
			printTLine('~',0); printf("\n");
			printItems();
			getInput();
			break;
		case 'f':
			libprint(in, "Medium suchen nach (\e[1mT\e[0m\e[32mitel=0, \e[1mA\e[0m\e[32mus\e[1mL\e[0m\e[32meihender=1): ");
			fgets(vbuf, 128, stdin);
			int fBy = vbuf[0];
			libprint(in, "Nach dieser Zeichenkette durchsuchen: ");
			char* fItem = fgets(vbuf, 128, stdin);
			printTLine('~',0); printf("\n");
			switch (fBy){
				case 'a':
				case 'A':
				case 'l':
				case 'L':
				case '1':
					findItem(fItem, 1, &myLib);
					break;
				case 't':
				case 'T':
				case '0':
					findItem(fItem, 0, &myLib);
				default:
					break;				
			}
			getInput();
			break;
		default:
			break;
	}
}

/**
 * @ingroup LendLibIn
 * @brief Eigenes strtok, welches auch leere Einträge ausgibt.
 * @param str Der String
 * @param delims Die Trennzeichen
 * Quelle: http://stackoverflow.com/a/8706031
 */
char* strtok2 (char * str, char const * delims){
  static char  * src = NULL;
  char  *  p,  * ret = 0;

  if (str != NULL)
    src = str;

  if (src == NULL)
    return NULL;

  if ((p = strpbrk (src, delims)) != NULL) {
    *p  = 0;
    ret = src;
    src = ++p;

  } else if (*src) {
    ret = src;
    src = NULL;
  }

  return ret;
}