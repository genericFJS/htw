#include <iostream>    // cin42.cpp
using namespace std;

auto max(int, int) -> int;

char prompt[]="Geben Sie zwei verschiedene Ganzzahlen ein: \n";

auto main() -> int
{
 int zahl1=0, zahl2=0;

 // --- ohne Fehlerbehandlung: --- 
 cout<<prompt;
 cin>>zahl1; cin>>zahl2; cin.clear(); cin.ignore(INT_MAX,'\n');
 cout<<"Die groessere Zahl ist: "<<max(zahl1,zahl2)<<"\n";
 
 // --- nochmals mit Fehlerbehandlung: ---
 cout<<prompt;
 if(cin >> zahl1 && cin >> zahl2)
 {
	cin.clear(); cin.ignore(INT_MAX,'\n');
    cout << "Die groessere Zahl ist: " << max(zahl1, zahl2) << "\n";
	cin.get();
	return 0;
 }
 cin.clear(); cin.ignore(INT_MAX,'\n');
 cerr << "Fehlerhafte Eingabe ! \n";
 cin.get();
 return 1;
}

auto max(int a, int b) -> int
{
  return (a > b ? a : b);
}
/*
Geben Sie zwei verschiedene Ganzzahlen ein:
1 2
Die groessere Zahl ist: 2
Geben Sie zwei verschiedene Ganzzahlen ein:
33 44
Die groessere Zahl ist: 44
*/