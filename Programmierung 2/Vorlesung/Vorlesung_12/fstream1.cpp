/* fstream1.cpp */
#include<fstream>
#include<iostream>

using namespace std;

// Benutzen *eines* Datei-Objekts nacheinander zum schreiben und lesen
int main() {
    fstream fileStream;
    int i;

    // schreiben
    fileStream.open("fstream1.dat", ios::out);
    // fileStream << "X" << endl;  // Lesefehler provozieren
    for(i = 0; i < 9; ++i)
      fileStream << i << endl;
    fileStream.close();

    // lesen
    fileStream.open("fstream1.dat", ios::in);
    while(fileStream.good()) {
       fileStream >> i;
       if(fileStream.good())
          cout << i << ' ';
       else
          cout << endl << "Dateiende erreicht oder Lesefehler";
    }
    cout << endl;
}

