#include <iostream>
#include <iomanip>
using namespace std;
#include "fraction.h"

int main()
{
  Fraction f1(4,3);
  Fraction f2(3,4);
  Fraction f3;
  f3=f1.add(f2);
  f1.display();
  cout<<" + ";
  f2.display();
  cout<<" : ";
  f3.display();
  cout<<endl;
}