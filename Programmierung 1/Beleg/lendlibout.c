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
#ifdef CGI
	if (size == 0){
		printf("<h4> Keine Medien gefunden!</h4>");
		return;
	}
	printf("<table id='media'>\n");
	printf("<tr>\n<th>\nID</th> \n<th>Typ</th>\n <th>Titel</th>\n <th>Interpret/Autor</th>\n <th>Ausgeliehen an</th>\n</tr>\n");
	for (i = 0; i < size; i++){
		printf("<tr>\n<td>\n%d</td> \n<td>%s</td>\n <td>%s</td>\n <td>%s</td>\n <td>%s</td>\n</tr>\n", 
			/*currLib->curr->item->id*/((currLib > &myLib || currLib < &myLib)?0:i+1), 
			getmType(currLib->curr->item->type),
			currLib->curr->item->title,
			(strcmp(currLib->curr->item->author, "")==40 ? " " : currLib->curr->item->author),
			currLib->curr->item->lendee);
		currLib->curr = currLib->curr->next;
	}
	printf("</table>\n");
#else
	char sortedT = ' ', sortedL = ' ';
	if (currLib->sort == 0){
		sortedT = 'v';
	} else {
		sortedL = 'v';
	}
	libprint(out, "\n\e[4mAusgeliehene Medien:\e[0m\n");
	libprint(out, "%2s | %5s | %26c  %5s  %20s  %4c  %s","ID", "Typ", sortedT, "Titel", "Autor/Interpret", sortedL, "Ausgeliehen an");
	printTLine('-', 90);
	printf("\n");
	for (i = 0; i < size; i++){
		libprint(out, "%2d | %5.5s | %33.33s  %20.20s  %20.20s", 
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
#ifdef CGI
	if(pType != 3) {
		if (pType==2)
			printf("<div class='div error'>");
			vprintf(printable, args);
			va_end(args);		
		if (pType==2){
			printf("</div>");
		} else {
			printf("<br>\n");
		}
	}
#else
#ifdef DCOLOR
	setColor(type);
#endif
#ifndef DEBUG
	if (pType == 2)
		// Falls Fehlerausgabe deaktiviert ist, keine Fehler ausgeben!
		return;
#endif
	printf("%c[2K", 27);
	vprintf(printable, args);
	va_end(args);
	resetColor();
	
#ifdef DPRES
	if (pType == 3){
		// Statusmeldungen bei Bedarf mit Verzögerung
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
	puts("Content Type: text/html\n\n");
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
	printf("<h3>Aktion wählen:</h3>\n");
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
	libdb = fopen(filename,"wt");
	if (libdb){
		int i, size = 0;
		myLib.curr = myLib.first;
		size = myLib.size;
		for (i = 0; i < size; i++){
			fprintf(libdb, "%d;%s;%s;%s\n", 
				myLib.curr->item->type,
				myLib.curr->item->title,
				myLib.curr->item->author,
				myLib.curr->item->lendee);
			myLib.curr = myLib.curr->next;
		}
	} else {
		libprint(error, "Datei konnte nicht zum schreiben geöffnet werden");
		exit(-1);
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