// Les3_1.cpp
#include <iostream>
#include <iomanip>
#define N 10

using namespace std;

auto main() -> void
{
 char Eingabepuffer[N];
 cin.getline(Eingabepuffer,N,'\n');
 while(strlen(Eingabepuffer))
 {
   auto *Zstr=new char[strlen(Eingabepuffer)+1];
   strcpy(Zstr,Eingabepuffer);
   cout<<"Zstr:"<<Zstr<<endl;
   delete [] Zstr; // bei Vektoren: []
   Zstr=nullptr;   // Zeigerwert nullptr bzw. 0
   delete [] Zstr; // wiederholt bei nullptr bzw. 0 zulaessig
   cin.getline(Eingabepuffer,N,'\n');
 }
 cin.get();
}
 
/*
abcdefghijklmnopqrstuvwxyz
Zstr:abcdefghi
Zstr:jklmnopqr
Zstr:stuvwxyz
*/
