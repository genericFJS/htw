#include "lendlibout.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "lendlibitem.h"
#include "lendlibin.h"

#define SLEEPDURATION 250

FILE *htmlF;
int termw = 55; ///< Breite des Terminals (falls Terminalausgabe)

/**
 * @ingroup LendLibOut
 * @brief Bereitet Variablen für den Output vor
 */
void prepareOut(){
	///- Berechnung der Terminalbreite (Quelle: http://stackoverflow.com/a/1022961)
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (w.ws_col > 55)
		termw = w.ws_col;
}

/**
 * @ingroup LendLibOut
 * @brief Gibt die Liste der ausgeliehenen Medien aus
 */
void printItems(){
	int i, size = 0;
	currLib->curr = currLib->first;
	size = currLib->size;
#ifdef CGI	/// Im CGI durch eine Tabelle (in der auch schon Bedienelemente fürs löschen, sortieren usw. eingeschlossen sind)
	if (size == 0){
		libprint(error, "Keine Medien gefunden!");
		currLib = &myLib;
		printItems();
		return;
	}
	printf("<table class='media'>\n");
	printf("<tr>\n<th>\n</th> \n<th>Typ</th>\n <th>");
	printf("<form name='stitle' id='stitle' action='lendlib.cgi' METHOD='POST'>Titel\n\
	<input style='display: none' name='sti' type='text' value='0'></input>\n\
	<a href=\"javascript: document.forms['stitle'].submit();\"><i class='fa fa-sort-alpha-asc'></i></a> \n</form>\n</th>\n");
	printf("<th>Interpret/Autor</th>\n <th>");
	printf("<form name='slendee' id='slendee' action='lendlib.cgi' METHOD='POST'>Ausgeliehen an\n\
	<input style='display: none' name='sle' type='text' value='1'></input>\n\
	<a href=\"javascript: document.forms['slendee'].submit();\"><i class='fa fa-sort-alpha-asc'></i></a> \n</form>\n</th>\n");
	for (i = 0; i < size; i++){
		printf("<tr>\n<td>\n<form  name='delete%d' action='lendlib.cgi' METHOD='POST'>\n<input style='display: none' name='del' type='text' value='%d'></input>\n<a href=\"javascript: document.forms['delete%d'].submit();\"><i class='fa fa-trash-o'></i></a>\n</form>\n</td> \n", currLib->curr->item->id, currLib->curr->item->id, currLib->curr->item->id);
		printf("<td>%s</td>\n <td>%s</td>\n <td>%s</td>\n <td>%s</td>\n",
			getmType(currLib->curr->item->type),
			currLib->curr->item->title,
			(strcmp(currLib->curr->item->author, "")==40 ? " " : currLib->curr->item->author),
			currLib->curr->item->lendee);
		printf("</tr>");
		currLib->curr = currLib->curr->next;
	}
	if (currLib == &myLib){
		printf("<form name='create' action='lendlib.cgi' METHOD='POST'>\n\
			<tr>\n\
			<td><a href=\"javascript: document.forms['create'].submit();\"><i class='fa fa-plus-circle fa-lg'></i></a></td>\
			<td><input name='cty' type='radio' value='bu'>Buch</input><br>\n\
			<input name='cty' type='radio' value='cd'>CD</input><br>\n\
			<input name='cty' type='radio' value='dv'>DVD</input><br>\n\
			<input name='cty' type='radio' value='ot' checked>Anderes</input></td>\n\
			<td><input name='cti' type='text' maxlength='75' placeholder='Titel'></input></td>\n\
			<td><input name='cau' type='text' maxlength='75' placeholder='Autor/Interpret'></input></td>\n\
			<td><input name='cle' type='text' maxlength='75' placeholder='Ausgeliehen an'></input></td>\n\
			</tr></form>");
		printf("</table>\n");
	} else {
		printf("</table>\n");		
		printf("<a href="">Alle Medien anzeigen</a>");
	}
#else	/// Im Terminal in einer Tabellenimitation
	char sortedT = ' ', sortedL = ' ';
	if (currLib->sort == 0){
		sortedT = 'v';
	} else {
		sortedL = 'v';
	}
	libprint(out, "\n\e[4mAusgeliehene Medien:\e[0m\n");
	libprint(out, "%2s | %5s   %26c  %5s  %20s  %4c  %s","ID", "Typ", sortedT, "Titel", "Autor/Interpret", sortedL, "Ausgeliehen an");
	printTLine('-', 90);
	printf("\n");
	for (i = 0; i < size; i++){
		libprint(out, "%2d | %5.5s   %33.33s  %20.20s  %20.20s", 
			currLib->curr->item->id, 
			getmType(currLib->curr->item->type),
			currLib->curr->item->title,
			(strcmp(currLib->curr->item->author, "")==40 ? " " : currLib->curr->item->author),
			currLib->curr->item->lendee);
		currLib->curr = currLib->curr->next;
	}
	printTLine('~', 0);
	printf("\n");
#endif
}

/**
 * @ingroup LendLibOut
 * @brief Terminalausgabe abhängig von (beim kompilieren) definierten Paramtern.
 * @param type Ausgabetyp (::ptype)
 * 
 * Quelle: http://www.ozzu.com/cpp-tutorials/tutorial-writing-custom-printf-wrapper-function-t89166.html
 */
void libprint(ptype type, const char* printable, ...){
	va_list args;
	va_start(args, printable);
	int pType = type;
#ifdef CGI	/// - Im Falle CGI werden die Ausgaben in verschieden Formatierte divs gefüllt
	if(pType != 3) {
		if (pType==2)
			printf("<div class='error'>");
		if (pType==1)
			printf("<div class='out'>");
			vprintf(printable, args);
			va_end(args);		
		if (pType==2 || pType ==1){
			printf("</div>");
		} else {
			printf("<br>\n");
		}
	}
#else	///- Im Terminal wird je nach definierten Strings etwas mit oder Farbe ausgegeben - oder nicht
#ifdef DCOLOR
	setColor(type);
#endif
#ifndef DEBUG
	if (pType == 2)
		/// Falls Fehlerausgabe deaktiviert ist, keine Fehler ausgeben!
		return;
#endif
	printf("%c[2K", 27);
	vprintf(printable, args);
	va_end(args);
	resetColor();
	
#ifdef DPRES
	if (pType == 3){
		/// Statusmeldungen bei Bedarf mit Verzögerung
		fflush(0);
		sleep_ms(SLEEPDURATION);
	}
#endif
	
	if (pType == 3){
		printf("\r");
	} else if (pType != 0) {
		printf("\n");
	}
#endif
}

/**
 * @ingroup LendLibOut
 * @brief Setzt die Terminal-Schriftfarbe abhängig vom Typ.
 * @param pType Ausgabetyp (::ptype)
 * 
 * Nur, falls beim Compilieren DCOLOR definiert wurde.
 */
void setColor(int pType){	
#ifdef DCOLOR
	if (pType == 3){
		printf("\e[33m");
	}else if (pType == 4){
		printf("\e[34m");
	}else if (pType == 2){
		printf("\e[31m");
	}else{
		printf("\e[32m");
	}
#endif
}

/**
 * @ingroup LendLibOut
 * @brief Setzt die Terminal-Schriftfarbe zurück auf den Standard.
 * 
 * Nur, falls beim Compilieren DCOLOR definiert wurde.
 */
void resetColor(){	
#ifdef DCOLOR
	printf("\e[39m");
#endif
}

/**
 * @ingroup LendLibOut
 * @brief Gibt einen Header aus
 * 
 * Im Terminal ein paar erste Zeilen, im CGI den HTML-Header
 */
void printHead(){
#ifdef CGI
// 	puts("Content Type: text/html\n\n");
	htmlF = fopen("../cgi/index_head.html", "rt");
	if (htmlF) {
		while (fgets(vbuf,256,htmlF))
			printf("%s",vbuf);	
	} else {
		puts("<h1>Vorlagendatei konnte nicht geoeffnet werden<h1>");
	}
#else
	setColor(1);
	printTLine('=', 0);
	printf("\n");
	char intro[]=" Beleg von Falk-Jonatan Strube, Matrikelnr.: 39467 ";
	char detail[]=" Aufgabe: %d | Darstellungsform: %d (CGI) ";
	int task= (39467 % 4)+1;
	int vis= (39467 % 3)+1;
	unsigned int leftI, rightI;
	
	leftI = (termw-sizeof(intro)+1)/2;
	rightI = leftI + ((termw-sizeof(intro)+1) % 2);
	printTLine('-', leftI);
	setColor(1);
	printf("%s",intro);
	printTLine('-', rightI);
	printf("\n");
	
	leftI = (termw-sizeof(detail)+1)/2+1;
	rightI = leftI + ((termw-sizeof(detail)+1) % 2);
	printTLine('-', leftI);
	setColor(1);
	printf(detail, task,vis);
	printTLine('-', rightI);
	printf("\n");
	
	printTLine('=', 0);
	printf("\n");
	resetColor();
#endif
}

/**
 * @ingroup LendLibOut
 * @brief Gibt die HTML-Bedienelemente aus
 * 
 */
void printHTMLInter(){
	htmlF = fopen("../cgi/index_interf.html", "rt");
	if (htmlF) {
		while (fgets(vbuf,256,htmlF))
			printf("%s",vbuf);		
	} else {
		puts("<h1>Vorlagendatei konnte nicht geoeffnet werden<h1>");
	}
}

/**
 * @ingroup LendLibOut
 * @brief Gibt einen Footer aus
 * 
 * Im Terminal ein Abschlussstrich, im CGI den HTML-Footer
 */
void printFoot(){
#ifdef CGI
	htmlF = fopen("../cgi/index_foot.html", "rt");
	if (htmlF) {
		while (fgets(vbuf,256,htmlF))
			printf("%s",vbuf);		
	} else {
		puts("<h1>Vorlagendatei konnte nicht geoeffnet werden<h1>");
		exit(-1);
	}
#else
	printTLine('=', 0);
	printf("\n");
#endif
}

/**
 * @ingroup LendLibOut
 * @brief Gibt eine Linie im Terminal aus
 * @param type Ein char, der die Linie visuell bestimmt
 * @param length Die Länge der Linie, bei der Länge 0 wird die Breite des Terminals
 */
void printTLine(char type, int length){
	int i;
	if (length <= 0){
		length = termw;
	}
	if (type != '~') {
		setColor(1);
	}else {
		setColor(4);
	}
	for (i=0; i<length; i++){
		printf("%c", type);
	}
	resetColor();
}

/**
 * @ingroup LendLibOut
 * @brief Speichert Liste in Datei
 */
void saveDBtoFile(){
	libprint(status, "Schreibe in Datei.");
	sortItems(2, &myLib);
	libdb = fopen(filename,"wt");
	if (libdb){
		int i, size = 0;
		myLib.curr = myLib.first;
		size = myLib.size;
		for (i = 0; i < size; i++){
			fprintf(libdb, "%d;%d;%s;%s;%s\n", 
				myLib.curr->item->id,
				myLib.curr->item->type,
				myLib.curr->item->title,
				myLib.curr->item->author,
				myLib.curr->item->lendee);
			myLib.curr = myLib.curr->next;
		}
	} else {
		libprint(error, "Datei konnte nicht zum schreiben geöffnet werden");
		return;
	}
#ifndef CGI
	libprint(out, "Daten wurden in Datei gespeichert");
#endif
}

/**
 * @ingroup LendLibOut
 * @brief Cross-Platform Sleep Funktion in Millisekunden
 * 
 * Quelle: http://stackoverflow.com/a/28827188
 */
#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds){
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(milliseconds * 1000);
#endif
}