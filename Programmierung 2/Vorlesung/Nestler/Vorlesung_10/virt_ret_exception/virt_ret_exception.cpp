#include <iostream>
using namespace std;

class X {};

class Y: public X {};

class A { public: virtual X &f(X &x){ cout<<"A.f\n"; return x; }};

class B: public A { private: virtual Y &f(X &x){ cout<<"B.f\n"; return (Y &)x; }};

void main(){
			 Y y;
	         X &x = y;      // Referenz x mit y initialisieren
             B b;
             A &a = b;      // Referenz a mit b initialisieren
             a.f((Y &)x);   // spaete Bindung, Aufruf b.f, obwohl private
		//	 b.f(y);	    // Compile-Error wg. spaeter Bindung
			 cin.ignore();
}