//HAUPTPROGRAMM
#include <iostream>
#include <iomanip>
#include <new>
#include <cstdlib>
using namespace std;

#include "intarr.h"
#include "fraction.h"
void MemError ()
{
   cout << "Not enough memory\n";
    exit (1);
}
int main()
{
  set_new_handler(&MemError);
  IntArr<int> IA (10);
  try
  {
    for (int i = 0; i < IA.getNum() ; ++i) IA[i]=i;
    for (int i = 0; i < IA.getNum() ; ++i) cout << IA[i] <<", ";
    cout << '\n';
    IA.resize(16);
    for (int i = 0; i < IA.getNum() ; ++i) cout<< setprecision(2) << IA[i] <<", ";
    cout << '\n';
    cout << IA[100] <<'\n';
  }
  catch (IntArr<int>::Range){cerr<<"Indexerror"<<endl;}
  cout<<"============================"<<endl;
  {
    try
    {
      IntArr<Fraction> IA (10);
      for (int i = 0; i < IA.getNum() ; ++i) IA[i]=Fraction(i,2);
      for (int i = 0; i < IA.getNum() ; ++i) cout << IA[i] <<", ";
      cout << '\n';
      IA.resize(16);
      for (int i = 0; i < IA.getNum() ; ++i) cout<< IA[i] <<", ";
      cout << '\n';
      cout << IA[100] <<'\n';
    }catch (IntArr<Fraction>::Range){cerr<<"Indexerror"<<endl;}
  }
  return 0;
}


