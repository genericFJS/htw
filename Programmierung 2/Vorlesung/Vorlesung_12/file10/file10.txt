#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	if(argc !=3){ cout<<"falsche Anzahl an Argumenten\n";
				  exit(1);
	}

	ifstream von(argv[1]);	//File-Stream fuer Eingabe oeffnen
	if(!von){ cout<<"Eingabedatei: "<<argv[1]<<" kann nicht geoeffnet werden\n";
			  exit(1);
	}

	ofstream nach(argv[2]);	//File-Stream fuer die Ausgabe noeffnen
	if(!nach){ cout<<"Ausgabedatei: "<<argv[2]<<" kann nicht geoeffnet werden\n";
	           exit(1);
	}

	char ch;
	unsigned long i=0UL;
	while(von.get(ch)){ nach.put(ch); i++; }

	if(!von.eof() || !nach) cout<<"Fehler\n";
	cout<<"Datei "<<argv[1]<<" nach "<<argv[2]<<" kopiert, "<<i<<" Zeichen uebertragen\n";
	cin.ignore();
}