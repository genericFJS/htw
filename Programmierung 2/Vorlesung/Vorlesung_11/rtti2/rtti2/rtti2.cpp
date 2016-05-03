// Projekteigenschaften | C/C++ | Sprache | 
// Laufzeit-Typinformationen aktivieren | Ja (/GR)
#include <iostream>			//rtti2.cpp
#include <typeinfo>	       
using namespace std;

class Basis{public: 
//Die folgende Methode ist notwendig fuer die
//korrekte Ausführung der Anweisung
//cout<<typeid(*p).name()<<endl; (siehe unten),
//ohne eine virtual-Methode wird bei der
//genannten Anweisung nur "class Basis"
//ausgegeben, obwohl "class Abgeleitet" korrekt
//ist !
			virtual void f(){} 
};

class Abgeleitet:public Basis{};

void main(){
	Abgeleitet *d=new Abgeleitet;
	Basis *p = d, *pNull=0;
	Abgeleitet Objekt1, Objekt2;

	cout<<typeid(p).name()<<endl;  // class Basis *
	cout<<typeid(*p).name()<<endl; // class Abgeleitet
	cout<<typeid(d).name()<<endl;  // class Abgeleitet *
	cout<<typeid(*d).name()<<endl; // class Abgeleitet

	if(typeid(*d)==typeid(*p))		     // true
		cout<<"true\n";
	else cout<<"false\n";

	if(typeid(Objekt2)==typeid(Objekt1)) // true
		cout<<"true\n";
	else cout<<"false\n";

	cout<<typeid(pNull).name()<<endl;   // class Basis
	
	if(typeid(&Objekt2)==typeid(pNull)) // false
		cout<<"true\n";
	else cout<<"false\n";

	try{
		cout<<typeid(*pNull).name()<<endl; //error
	}
	catch(...){
		cout<<"Error: typeid(*pNull).name()\n";
	}
	try{
		if(typeid(Objekt2)==typeid(*pNull)) //error
		cout<<"true\n";
		else cout<<"false\n";
	}
	catch(...){
		cout<<"Error: typeid(*pNull)\n";
	}
	cin.get();
}
/*
class Basis *
class Abgeleitet
class Abgeleitet *
class Abgeleitet
true
true
class Basis *
false
Error: typeid(*pNull).name()
Error: typeid(*pNull)
*/