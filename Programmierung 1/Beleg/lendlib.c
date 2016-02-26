#include "lendlib.h"
#include "lendlibout.h"

/**
 * @ingroup LendLib
 * @brief Die Main-Funktion.
 */
int main(int argc, char* argv[]){
	prepareOut();	///- Ausgabevariablen vorbereiten
	printHead();	///- Kopfzeilen ausgeben
	readfile();	///- Einträge aus Datei einlesen (falls sie existiert)
#ifdef CGI
	
#else
	

#endif
// 	int i;
// 	for (i=0; i<10; i++){	
// 		libprint(status, "test%d", i);
// 	}
// 	libprint(out, "xxx\n");
	printFoot();
	return 1;
}