#include <iostream>	     // cla7.cpp

using namespace std;

class ratio
{ public: 
	ratio(){ ausgabeart=FLOAT;
			 cout<<"Konstruktor, ausgabeart "
				 <<ausgabeart<<'\n'; 
	}
	  
	~ratio(){ cout<<"Destruktor"<<endl; }

	static int ausgabeart;   // Deklaration
	enum {BRUCH, FLOAT};     // static
  // ...
};

// Initialisierung vor main():
int ratio::ausgabeart=ratio::BRUCH;

void main(){
	cout<<"vor Objektdefinition a  "
		<<ratio::ausgabeart<<endl;
	ratio a;                 // Objekt a
	cout<<"nach Objektdefinition a "
		<<a.ausgabeart<<endl;
	ratio::ausgabeart=ratio::BRUCH; //Wertzuweisung
	a.ausgabeart=a.BRUCH;           //alternativ
	cout<<"nach Initialisierung    "
		<<ratio::ausgabeart<<endl;
	cin.get();
}

/*
vor Objektdefinition a  0
Konstruktor, ausgabeart 1
nach Objektdefinition a 1
nach Initialisierung    0
*/

