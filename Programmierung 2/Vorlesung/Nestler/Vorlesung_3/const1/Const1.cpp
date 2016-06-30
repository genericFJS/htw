// const1.cpp - Nutzung von Konstanten zur
//              Dimensionierung und
//              Instantiierung von Feldern

#include <iostream>
#include <string.h>

using namespace std;

auto main() -> void
{ const auto SIZE=5; // const notwendig !
  char ca[SIZE];    // nicht in C moeglich !
  ca[0]='\0';
  cout<<"Groesse von ca= "<<sizeof ca<<endl;
  cout<<"Laenge  von ca= "<<strlen(ca)<<endl;
  cin.get();
}

/*
Groesse von ca= 5
Laenge  von ca= 0

*/