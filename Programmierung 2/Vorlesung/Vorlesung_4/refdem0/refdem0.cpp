#include <iostream> // refdemo.cpp

using namespace std;

auto main() -> int 
{ auto ivar = 123;      // int
  auto &iref1 = ivar;   // int
  int  &iref2 = ivar;
  int  &iref3 = iref1;
  cout <<"ivar="<<ivar<<"  iref1="<<iref1<<"  iref2="<<iref2;
  cout<<"  iref3="<<iref3<<endl;
  cin.get();
  return 0;
}

/*
ivar=123  iref1=123  iref2=123  iref3=123
Press any key to continue
*/
