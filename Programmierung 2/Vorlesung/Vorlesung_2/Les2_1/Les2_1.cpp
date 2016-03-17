#include <iostream>  // Les2_1.cpp
#include <iomanip>

using namespace std;

auto main() -> void
{
  cout<<"double "<<22.0/7.0<<endl;       // double
  cout<<"char "<<'x'<<endl;              // char
  cout<<"short "<<short('x')<<endl;      // 120
  cout<<"float "<<(float)22.0/7.0<<endl; // float
                                         
  cout<<"long double "<<(long double)(22.0/7.0)<<endl; 
  cout<<"int "<<(5 & 6)<<endl;           // int
  
  cout<<"true = "<<true<<"  false = "<<false<<'\n';//bool
  cout<<boolalpha;
  cout<<"true = "<<true<<"  false = "<<false<<'\n';//bool
	
  char *s="HTW Dresden"; 
  cout<<s<<endl;         // Wert von s
  cout<<(int *)s<<endl;    // Adresse von s 
  char *t = s; cout<<"T = "<<t<<endl;
  cin.get();
}

/*
double 3.14286
char x
short 120
float 3.14286
long double 3.14286
int 4
true = 1  false = 0
true = true  false = false
HTW Dresden
00417838
T = HTW Dresden
*/