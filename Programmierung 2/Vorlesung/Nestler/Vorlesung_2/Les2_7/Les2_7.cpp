#include <iostream>
#include <iomanip>
#define N 10
using namespace std;

auto f() -> void;     // Prototyp

auto main() -> void
{ f();        // Achtung bei Aufruf   f;
  f();        // Repeated call
  cin.get();
}

auto f() -> void
{ char buf[N], c; 
  do { cin>>setw(sizeof buf)>>buf; // sicher, jedoch begrenzen whitespace-Zeichen die EIngabe
       cout<<"buf="<<buf<<endl;
       if(cin.get(c) && c=='\n') return;
//	   if(cin.eof()) return;
       cin.putback(c);
     }
  while(strlen(buf)==sizeof(buf)-1);
}

/*
0123456789abcdefghijklmnopqrstuvwxyz
buf=012345678
buf=9abcdefgh
buf=ijklmnopq
buf=rstuvwxyz
abcdefghijklmnop
buf=abcdefghi
buf=jklmnop
Press any key to continue
*/