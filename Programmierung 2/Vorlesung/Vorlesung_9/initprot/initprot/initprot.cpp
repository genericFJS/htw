#include <iostream>
using namespace std;

// Beispiel fuer einen protected - Konstruktor der Basisklasse, damit
// sind keine Instanzen der Basisklasse instantiierbar !
//
class X { 
	protected: X(int w):wert(w){ cout<<"Konstruktor X"<<endl; }
			   ~X(void){ cout<<"Destruktor X, wert = "<<wert<<endl; }
			   int wert;
};

class Y : public X {
	public: 
		Y(int a) : X(a) { cout<<"Konstruktor Y"<<endl; }
		~Y(void){ cout<<"Destruktor Y, wert = "<<wert<<endl; }
};

void main(){
	Y y(5);
//	X x(3);       // keine Instanzen vom Typ X moeglich !
	cin.get();
}

/*
Konstruktor X
Konstruktor Y
Destruktor Y, wert = 5
Destruktor X, wert = 5
*/