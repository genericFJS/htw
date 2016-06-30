#include <iostream>    //refdem7.cpp

using namespace std;

int MyNum;             //globale Variable ( 0 )

int &Num()             //Referenz auf MyNum
{
  return MyNum;
}

auto main() -> void
{ 
	int i(Num());     // int i=MyNum;

    Num()=5,          // MyNum = 5,

  cout<<"i     = "
	  <<i             // i    = 0  
	  <<"\nMyNum = "
	  <<Num()         // MyNum= 5
	  <<endl, 

  cin.get();
}

/*
i     = 0
MyNum = 5
*/