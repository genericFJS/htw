#include <iostream>
#include <new>
#include <cstdlib>
using namespace std;
#include "fraction.h"

Fraction :: Fraction(long Num, long Den)
{
   if (Den < 0)
   {
      Num = -Num;
      Den = -Den;
   }
   Numerator   = Num;
   Denom       = Den ? Den : 1;
   int Factor  = gcf(Num,Den);
   if (Factor > 1)
   {
      Numerator /= Factor;
      Denom     /= Factor;
   }
}

void Fraction :: Display ()const
{
  cout << Numerator << '/' << Denom;
}

Fraction Fraction :: operator+ (const Fraction & Second)const
{
  long Factor = gcf (Denom,Second.Denom);
  long Mult1  = Denom / Factor;
  long Mult2  = Second.Denom / Factor;
  long NumRes = Numerator * Mult2 + Second.Numerator * Mult1;
  long DenRes = Denom * Mult2;
  return Fraction(NumRes, DenRes);
}

Fraction& Fraction :: operator+= (const Fraction & Second)
{
  long Factor = gcf (Denom,Second.Denom);
  long Mult1  = Denom / Factor;
  long Mult2  = Second.Denom / Factor;
  Numerator   = Numerator * Mult2 + Second.Numerator * Mult1;
  Denom       = Denom * Mult2;
  return *this;
}

long Fraction :: gcf (long First, long Second)
{
   if (First < 0)First=-First;
   if (Second< 0)Second=-Second;
   while (Second)
   {
      int tmp = First % Second;
      First   = Second;
      Second  = tmp;
   }
   return First;
}

ostream& operator<< (ostream& OS, Fraction& F)
{
  OS << F.Numerator << '/' << F.Denom;
  return OS;
}
