#include <iostream>
#include <iomanip>
#include <cstring>
#include "fraction.h"

using namespace std;

Fraction::Fraction(long num, long den)
{
  if (den<0)
  { den=-den; num=-num;}
  numerator=num;
  denom    =den;
  int fact=gcf(num,den);
  if (fact>1)
  {
    numerator/=fact; denom/=fact;
  }
}

void Fraction::display()
{
  cout<<numerator<<'/'<<denom;
}

Fraction Fraction::add(Fraction & other)
{
  long fact=gcf(denom, other.denom);
  cout<< fact<<endl;
  long mult1=denom/fact;
  long mult2=other.denom/fact;
  long num=numerator*mult2+other.numerator*mult1;
  long den=denom*mult2;
  return Fraction(num,den);
}
long Fraction::gcf(long first, long second)
{
  if (first <0)first =- first;
  if (second<0)second=-second;
  while (second)
  {
    int tmp=first % second;
    first  =second;
    second =tmp;
  }
  return first;
} 
