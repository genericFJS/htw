// Beispiel zum Positionieren von Dateien: seektell.cpp

#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

int main() {
    ifstream einIfstream;
    if(!einIfstream.is_open())  // is_open ausprobieren
       einIfstream.open("seek.dat", ios::binary | ios::in);
	/*if(!einIfstream.bad()){
        cout<<einIfstream.rdbuf()<<endl;
		einIfstream.seekg(0);
	}*/
    einIfstream.seekg(9, ios::beg);              // absolute Leseposition
	cout<<"Position = "<<(long)(einIfstream.tellg())<<endl;
    int c='0';
    c =  einIfstream.get();                // get schaltet Pos. weiter
    cout << c << " an Position 9 gefunden\n";
    // 2 relativ zur aktuellen Position (10) weiterbewegen
    einIfstream.seekg(2, ios::cur);
    ios::pos_type position = einIfstream.tellg();
    c=einIfstream.get();
    cout << c << " an Position 12 gefunden\n";
    einIfstream.seekg(-4, ios::end);  // 4 Positionen vor dem Ende
    c= einIfstream.get();
    cout << c << " an der viertletzten Position gefunden\n";
    einIfstream.seekg(position, ios::beg);  // an alte Position (12) gehen
    c = einIfstream.get();
    cout << c << " an Position 12 gefunden\n";
	cin.get();
}
