#include <stdio.h>    // C I/O Library Header
#include <iostream>   // C++ I/O Library Header

using namespace std;

void  main(){
//iostream works with stdio
    ios::sync_with_stdio(); 
//
// ohne die vorhergehende Anweisung
// erfolgen die Ausgaben hier in
// umgekehrter Reihenfolge 
//   
  cout<<"now use iostream\n";
  printf("and stdio\n");
  cin.get();
}
