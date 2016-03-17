// REFDEM5.CPP: Wert-, Zeiger- und Referenzparameter
#include <iostream>

using namespace std;

struct bigone
{ int serno;
  char text[1000];        // gewaltig gross !!
};

bigone bo = { 123, "Das ist eine grosse Struktur !" };

void valfunc( bigone );         // Wertuebergabe
void ptrfunc( bigone * ); // Uebergabe via Zeiger
void reffunc( bigone & ); // Ubergabe via Referenz

void main()
{valfunc(bo);           // Variable als Wert
 cout<<bo.serno<<endl;
 ptrfunc(&bo);          // Adresse der Variablen
 cout<<bo.serno<<endl;
 reffunc(bo);           // Referenz zur Variablen
 cout<<bo.serno<<endl;
 cin.get();
}

void valfunc(bigone val) // Uebergabe des Wertes, Kopien der
{                        // Werte der aktuellen Parameter 
 cout<<val.serno<<endl;
 cout<<val.text<<endl;
 val.serno=120; // Aenderungen sind ausserhalb nicht wirksam !!
}

void ptrfunc( bigone *ptr) // Uebergabe der Zeiger
{
 cout<<ptr->serno<<endl;
 cout<<(*ptr).text<<endl;
 ptr->serno=124; // Aenderungen auch ausserhalb wirksam !!
}

void reffunc( bigone &ref) // Uebergabe via Referenz
{ // Kein Kopieren von Parameterwerten !!!
 cout<<ref.serno<<endl; // Keine Dereferenzierung notw.
 cout<<ref.text<<endl;
 ref.serno=125;  // Aenderungen auch ausserhalb wirksam !!
}

/*  123
    Das ist eine grosse Struktur !
    123
    123
    Das ist eine grosse Struktur !
    124
    124
    Das ist eine grosse Struktur !
    125                                         */