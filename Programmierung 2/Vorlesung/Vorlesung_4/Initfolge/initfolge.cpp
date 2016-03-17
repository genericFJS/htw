// initfolge.cpp

#include <iostream>

using namespace std;

// Deklarationsreihenfolge der Komponenten in X
// bestimmt die Initialisierungsreihenfolge 
// beim Konstruktoraufruf von X

class X {
		double flaeche, hoehe, breite; // undef. Ergebnis

	 // double hoehe, breite, flaeche; // korrektes Ergebnis

	public:

	 // Reihenfolge in Initialisierungsliste ist 
	 // fuer Initialisierung nicht relevant !

		X(double b, double h):
								breite(b), 
								hoehe(h),
	//							flaeche(breite*hoehe)
	  flaeche(b*h)
		{ 
					cout<<"Flaeche = "<<flaeche<<'\n';
		}
};

void main(){
     X x(1.0, 2.0);
	 cin.get();
}

/*

Flaeche = 8.56729e+123

*/