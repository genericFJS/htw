#include <iostream>	  // Les2_8.cpp
#define N 10

using namespace std;

auto f() -> void;     // Prototyp

auto main() -> void
{ f();        // Achtung bei Aufruf f;
  f();        // Repeated call
  cin.get();
}

auto f() -> void     // Funktion zum sicheren Einlesen
{ char buf[N];
  cout<<"s = ";
  do {      cin.clear();
			if(cin.peek()=='\n') return;
		    cin.getline(buf,sizeof(buf),'\n');  // '/n' wird gelesen, nicht gespeichert !
			if(strlen(buf)) cout<<"buf="<<buf<<endl;
  }
  while(strlen(buf)==sizeof(buf)-1);
}

/*
s = 0123
buf=0123
s = 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
buf=012345678
buf=9ABCDEFGH
buf=IJKLMNOPQ
buf=RSTUVWXYZ
*/
