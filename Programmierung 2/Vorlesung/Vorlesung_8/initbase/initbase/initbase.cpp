#include <iostream>
using namespace std;

// Beispiel fuer das Durchreichen von Werten fuer Konstruktoren
// von Basisklassen
//
class X { 
	public:		X(int w):wert(w){ cout<<"Konstruktor X"<<endl; }
			    virtual ~X(){ cout<<"Destruktor X, wert = "<<wert<<endl; }
	protected: int wert;
};

class Y : public X {
	public: 
		Y(int a) : X(a) { cout<<"Konstruktor Y"<<endl; }
		virtual ~Y(){ cout<<"Destruktor Y, wert = "<<wert<<endl; }
};

void main(){
	Y y(5);
	X x(3);       
	cin.get();
}

/*
Konstruktor X
Konstruktor Y
Konstruktor X

Destruktor X, wert = 3
Destruktor Y, wert = 5
Destruktor X, wert = 5
*/