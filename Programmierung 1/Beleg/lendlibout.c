#include "lendlibout.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "lendlibitem.h"

#define SLEEPDURATION 10

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
		termw = w.ws_col-1;	// -1, damit es nicht so gequetscht aussieht
}

/**
 * @ingroup LendLibOut
 * @brief Gibt die Liste der ausgeliehenen Medien aus
 */
void printItems(){
	int i, size = 0;
	
	for (i = 0; i < myMediaCount; i++)
		libprint(out, "%1.1d  %20.20s  %20.20s  %20.20s", (myMedia+i)->type, (myMedia+i)->title, (myMedia+i)->author, (myMedia+i)->lendee);
	
	myLib.curr = myLib.first;
	size = myLib.size;
	libprint(out, "%3s  %18s  %20s  %20s", "Typ", "Titel", "Autor/Interpret", "Ausgeliehen an");
// 	printTLine('-', 67);
// 	printf("\n");
	libprint(error, "%s", myLib.curr->item->title);
	for (i = 0; i < size; i++){
		libprint(out, "%1.1d  %20.20s  %20.20s  %20.20s", myLib.curr->item->type, myLib.curr->item->title, myLib.curr->item->author, myLib.curr->item->lendee);
		myLib.curr = myLib.curr->next;
	}
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
	if (pType == 3){// Statusmeldungen bei Bedarf mit Verzögerung
		printf("\e[33m");
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
 * @brief Gibt einen Footer aus
 * 
 * Im Terminal ein Abschlussstrich, im CGI den HTML-Footer
 */
void printFoot(){
#ifdef CGI
	
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
	setColor(1);
	for (i=0; i<length; i++){
		printf("%c", type);
	}
	resetColor();
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