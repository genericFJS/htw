#include<iostream>
#include"sinus.h"
using namespace std;

void sinusAnzeigen(double arg, const Sinus& funktor) {
    cout << "        Funktor   = "<<funktor(arg) << endl;
}

int main() {
    Sinus sinrad;
    Sinus sinGrad(Sinus::grad);
    Sinus sinNeuGrad(Sinus::neugrad);

    // Aufruf der Objekte wie eine Funktion
    cout << "sin(" << M_PI/4.0 <<" rad) = "         //  pi/4
         << sinrad(M_PI/4.0)   << endl;
    cout << "sin(45 Grad)      = " << sinGrad(45.0)    << endl;
	cout << "sin(45 Grad)      = " << sinGrad.operator()(45.0) 
		 << endl;
    cout << "sin(50 Neugrad)   = " << sinNeuGrad(50.0) << endl;

    // Übergabe eines Funktors an eine Funktion
    sinusAnzeigen(50.0, sinNeuGrad);

    cin.get();
}
/*
sin(0.785398 rad) = 0.707107
sin(45 Grad)      = 0.707107
sin(45 Grad)      = 0.707107
sin(50 Neugrad)   = 0.707107
        Funktor   = 0.707107
*/