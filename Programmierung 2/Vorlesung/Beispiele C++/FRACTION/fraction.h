#ifndef _H_FRACTION_
#define _H_FRACTION_

#include <iostream>
#include <iomanip>
#include <cstring>


using namespace std;

class Fraction
{
  private: long denom, numerator;
  public:
  Fraction(long num=0, long den=1);
  void display();
  Fraction add(Fraction & other);
  private:
  long gcf(long first, long second);  
};

#endif