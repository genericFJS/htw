// const3.cpp - Versuch des Umgehens des const - 
//              Inhaltes einer Variablen mittels
//              Zeigervariablen

#include <iostream>

using namespace std;

auto main() -> void
{ const auto laenge = 1024;    // int
//int     *a = &laenge;        // Fehler !!  
  auto    *a = (int *)&laenge; // OK, wegen cast
//laenge = 0L;                 // Fehler !!
  *a=4711;  // aendern des Inhaltes von a !!
  cout<<"*a        = "<<*a<<endl;
  cout<<"laenge    = "<<laenge<<endl;
  cout<<"a         = "<<a<<"\nsizeof(a) = "
      <<sizeof(a)<<endl;
  a=0L; // 0 - Zeiger
  cout<<"*a        = "<<a<<endl;
  cin.get();
}

/*
*a        = 4711
laenge    = 1024
a         = 0x0012FF78
sizeof(a) = 4
*a        = 0x00000000
*/