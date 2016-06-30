#include <iostream>
#include <fstream>

using namespace std;	// fstream2.cpp

int main()	// Lesen und Schreiben in eine Datei
{
    // Datei anlegen
    fstream FS("fstream2.dat", ios::out | ios::trunc);
    FS.close();            // leere Datei existiert jetzt
    int i;                 // Hilfsvariable

    // Datei zum Lesen und Schreiben öffnen
    FS.open("fstream2.dat", ios::in | ios::out);
    // schreiben
    for(i = 0; i < 20; ++i)
      FS << i << ' ';
    FS << endl;

    // lesen
    FS.seekg(0);               // Anfang suchen
    while(!FS.eof())
    {
       FS >> i;                // lesen
       if(!FS.eof())
          cout << i << ' ';    // Kontrollausgabe
    }
    cout << endl;
    FS.clear();                // EOF-Status löschen
    FS.seekp(5);               // Position 5 suchen

    FS << "neuer Text ";       // ab Pos. 5 überschreiben
    FS.seekg(0);               // Anfang suchen
    char buf[100];
    FS.getline(buf,100);       // Zeile lesen
    cout << buf << endl;       // Kontrollausgabe
	cin.ignore();
}

//  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
//  0 1 2neuer Text 8 9 10 11 12 13 14 15 16 17 18 19