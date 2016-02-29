#include <stdlib.h>
#include <stdio.h>
#include "lendlib.h"
#include "lendlibout.h"
#include "lendlibin.h"
#include "lendlibitem.h"


/**
 * @ingroup LendLib
 * @brief Die Main-Funktion.
 */
int main(int argc, char* argv[]){
	prepareOut();	///- Ausgabevariablen vorbereiten
	printHead();	///- Kopfzeilen ausgeben
	readfile();	///- Einträge aus Datei einlesen (falls sie existiert)
#ifdef CGI	/// CGI-Ausgabe:
	
#else	/// Terminalausgabe:
// 	printItems();	///- aus Datei erhaltene Medien anzeigen
	getInput();		///- Nutzerinput verarbeiten
#endif	/// beide:	
	saveDBtoFile();
	freeAll(&myLib);
	printFoot();	///- Fußzeilen ausgeben
	return 1;
}