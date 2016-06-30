#include <string>
#include <iostream>	  // Les2_9.cpp
#define N 10

using namespace std;

auto f() -> void;     // Prototyp

auto main() -> void
{ f();        // Achtung bei Aufruf   f;
  f();        // Repeated call
  cin.get();
}

auto f() -> void     // Funktion zum sicheren Einlesen
{ string s;
  cout<<"s = ";
  getline(cin, s);
  cout<<"s = "<<s<<endl;
}

/*
s = 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
s = 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
s = ABC
s = ABC
*/