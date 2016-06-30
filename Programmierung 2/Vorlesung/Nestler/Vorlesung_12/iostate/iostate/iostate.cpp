/* iostate.cpp */
#include<iostream>

using namespace std;

int main() {
    int i;
    ios::iostate status;
    while (true) {         // Schleifenabbruch mit break
         cout << "Zahl (Ctrl+D oder Ctrl+Z = Ende):";
         cin >> i;
         status = cin.rdstate();
         // Ausgabe der Statusbits
         cout << "status = " << status << endl;
         cout << "good() = " << cin.good() << endl;
         cout << "eof()  = " << cin.eof() << endl;
         cout << "fail() = " << cin.fail() << endl;
         cout << "bad()  = " << cin.bad() << endl;
         if (cin.eof())
             break;               // Abbruch
         // Fehlerbehandlung bzw. Ausgabe
         if (status) {
              cin.clear();      // Fehlerbits zurücksetzen
              cin.get();        // ggf. fehlerhaftes Zeichen entfernen
         }
         else cout << "*** " << i << endl;
    }
}
