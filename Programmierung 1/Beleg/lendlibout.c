#include "lendlibout.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/ioctl.h>
#include <unistd.h>

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
	if (pType == 0){
		printf("\e[33m");
	}else if (pType == 1){
		printf("\e[32m");
	}else{
		// Falls Fehlerausgabe deaktiviert ist, keine Fehler ausgeben!
#ifndef DEBUG
		return;
#endif
		printf("\e[31m");
	}
#endif
	vprintf(printable, args);
	va_end(args);
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
	libprint(out,"%s",intro);
	printTLine('-', rightI);
	printf("\n");
	
	leftI = (termw-sizeof(detail)+1)/2+1;
	rightI = leftI + ((termw-sizeof(detail)+1) % 2);
	printTLine('-', leftI);
	libprint(out,detail, task,vis);
	printTLine('-', rightI);
	printf("\n");
	
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
	for (i=0; i<length; i++){
		libprint(out, "%c", type);
	}
}