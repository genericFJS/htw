// A. Beck
// Beispiel zur Vorlesung PSP II


#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
#include "date.h"
int main()
{
  date D1;
  cout<<"heute:";
  D1.display();
  cout<<endl;

  const date D2=date(01,04,2010);
  D2.display();
  //D2.setDay(5);
  cout<<endl;

  date& rD=D1;
  rD.display();
  cout<<endl;
  D1.setDate(29,3,2010);
  D1.display();
  cout<<endl;
  
  return 0;
}



















