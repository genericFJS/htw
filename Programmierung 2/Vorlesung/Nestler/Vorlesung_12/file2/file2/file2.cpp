// Textdatei seitenweise (je 20 Zeilen) anzeigen

#include <iostream>
#include <fstream>

#define DL 255

using namespace std;

int main(){
 char dateiname[DL], zeile[512];
 ifstream datei;

 cout<<"Eine Textdatei anzeigen.\n"<<"Dateiname: ";
 cin.getline(dateiname, DL);

 datei.open(dateiname,ios::in);
 if(!datei){
             cerr<<"\nDatei "<< dateiname
			     << " kann nicht geoeffnet werden\n";
			 cin.get();
			 return 1;
 }
 
 int zeilenNr = 0;
 while(datei.getline(zeile, sizeof(zeile))){
       cout.width(5);
	   cout<<++zeilenNr <<": "<<zeile << endl;
	   if(zeilenNr % 20 == 0){
	     cout<< "\n\n\t --- weiter mit Eingabetaste --- ";
		 cin.get();
	   }
 }

 if(!datei.eof()){
    cerr<< "\nLesefehler !\n";
	cin.get();
	return 2;
 }
 cin.get();
 return 0;
}

/*
Eine Textdatei anzeigen.
Dateiname: ..\file2.cpp
    1: // Textdatei seitenweise (je 20 Zeilen) anzeigen
    2:
    3: #include <iostream>
    4: #include <fstream>
    5:
    6: #define DL 255
    7:
    8: using namespace std;
    9:
   10: int main(){
   11:  char dateiname[DL], zeile[512];
   12:  ifstream datei;
   13:
   14:  cout<<"Eine Textdatei anzeigen.\n"<<"Dateiname: ";
   15:  cin.getline(dateiname, DL);
   16:
   17:  datei.open(dateiname,ios::in);
   18:  if(!datei){
   19:              cerr<<"\nDatei "<< dateiname
   20:                       << " kann nicht geoeffnet werden\n";
         --- weiter mit Eingabetaste ---
   21:                   cin.get();
   22:                   return 1;
   23:  }
   24:
   25:  int zeilenNr = 0;
   26:  while(datei.getline(zeile, sizeof(zeile))){
   27:        cout.width(5);
   28:     cout<<++zeilenNr <<": "<<zeile << endl;
   29:     if(zeilenNr % 20 == 0){
   30:       cout<< "\n\n\t --- weiter mit Eingabetaste --- ";
   31:           cin.get();
   32:     }
   33:  }
   34:
   35:  if(!datei.eof()){
   36:     cerr<< "\nLesefehler !\n";
   37:  cin.get();
   38:  return 2;
   39:  }
   40:  cin.get();
         --- weiter mit Eingabetaste ---
   41:  return 0;
   42: }
*/
