#include <iostream>  // Les2_6.cpp
#include <iomanip>
#define N 10

using namespace std;

auto f() -> void;     // Prototyp

auto main() -> void
{ f();        // Achtung bei Aufruf   f;
  f();        // Repeated Call
  cin.get();
}

auto f() -> void
{ char buf[N];
  cout<<"Eingabe = ";
  do { if(cin.peek()!='\n') {
	      cin.get(buf,sizeof(buf));      // '/n' bleibt im Eingabestrom !
	   // cin.get(buf,sizeof(buf),'\n'); // '/n' ist default-Parameter
          if(strlen(buf)) 
			  cout<<"buf="<<buf<<endl;
		}
        else break;
     }
  while(strlen(buf)==sizeof(buf)-1);
  cin.get();  //'\n' aus Eingabepuffer lesen
}

/*
Eingabe = 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
buf=012345678
buf=9ABCDEFGH
buf=IJKLMNOPQ
buf=RSTUVWXYZ
Eingabe = 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
buf=012345678
buf=9ABCDEFGH
buf=IJKLMNOPQ
buf=RSTUVWXYZ
*/