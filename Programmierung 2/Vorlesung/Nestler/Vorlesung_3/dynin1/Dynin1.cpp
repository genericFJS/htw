// dynin1.cpp - dynamische Initialisierung von Variablen

#include <iostream>
#include <string>

using namespace std;

auto dest(void) -> int;

const auto size=dest()-20; // OK, nur in C++

// char ca[size];      // error: expected constant expression

char cb[8*5];          // OK

void main()
{
    cout<<"size = "<<size<<endl;
    const auto m=4*5;
    char feld[m]; feld[0]=0;
    cout<<"Groesse von feld = "<<sizeof feld<<endl;
	cout<<"Laenge  von feld = "<<strlen(feld)<<endl;
	cin.get();
}

int dest(void)			// Funktion zur Berechnung Anzahl Vektorelemente
{ return 8*5; }

