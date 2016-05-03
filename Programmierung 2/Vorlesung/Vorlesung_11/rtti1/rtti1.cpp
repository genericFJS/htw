#include <iostream>
#include <typeinfo.h>
using namespace std;

// Beispiel fuer die Bestimmung der Typinformation zur Laufzeit
//
// Eigenschaften | C,C++ | Sprache | Laufzeit- u. Typinformationen 
// aktivieren:   Ja (/GR)

class X { 
	protected: int wert;
	public:	
	X(int w):wert(w){ cout<<"Konstruktor X"<<endl; }
	virtual ~X(void){ cout<<"Destruktor X, wert = "<<wert<<endl; }
	virtual void out(){ 
		cout<<"type = "<<typeid(*this).name()<<endl; 
	}	
};

class Y : public X {
	public: 
	Y(int a) : X(a) { cout<<"Konstruktor Y"<<endl; }
	virtual ~Y(void){ cout<<"Destruktor Y, wert = "<<wert<<endl; }
	virtual void out(){ /*cout<<"type = "<<typeid(*this).name()<<endl;*/ 
		                X::out();
	}
};

void main(){
	X *py = new Y(5);
	cout<<typeid(*py).name()<<endl;
	X *px = new X(3);
	cout<<typeid(*px).name()<<endl;
	px->out();
	py->out();
	delete px; delete py; 
	cin.get();
}

/*
Konstruktor X
Konstruktor Y
class Y
Konstruktor X
class X
type = class X
type = class Y

Destruktor X, wert = 3
Destruktor Y, wert = 5
Destruktor X, wert = 5
*/