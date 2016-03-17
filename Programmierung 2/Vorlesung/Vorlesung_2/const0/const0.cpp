#include <iostream>			// const0.cpp
#include <iomanip>

using namespace std;

// auto higher(const int i) -> void { i++; }	// Fehler

auto main() -> void {
	const int SIZE = 10;	// const hier fuer C++ nicht notwendig
	char my[SIZE]="xyz";	// nicht in C
	char yours[4];

	char *const ptr = my;	// konstanter Zeiger
	*ptr = 'a'; ptr[1]='\0';// OK
	cout<<ptr<<endl;
//	ptr = yours;			// veraendert Zeiger, falsch !
//	ptr = "HTW";    		// veraendert Zeiger, falsch !

	const char *cp = "HTW"; // konstanter Inhalt
	cp = "TU";
//	cp[1]='T';			    // veraendert Inhalt, falsch !

	const auto *const adr ="Dresden"; // konstanter Inhalt und konstanter Zeiger
//	adr="Leipzig";			// veraendert Zeiger, falsch !
//	adr[0]='E';			    // veraendert Inhalt, falsch !

	const auto i = 2;
//	i++;				    // veraendert Inhalt, falsch !

	cin.get();
}