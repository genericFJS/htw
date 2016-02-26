#include "lendlib.h"
#include "lendlibout.h"

/**
 * @ingroup LendLib
 * @brief Die Main-Funktion.
 */
int main(int argc, char* argv[]){
	prepareOut();	///- Ausgabevariablen vorbereiten
	printHead();	///- Kopfzeilen ausgeben
	//readfile(lendlib.csv);	///- Einträge aus Datei einlesen (falls sie existiert)
	
	return 0;
}