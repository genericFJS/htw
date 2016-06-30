// refdem6
#include <iostream>
using namespace std;

auto print(int &par) -> void
{ cout<<"print:  par = "<<par<<endl;
  par=0;
}

auto printc(const int &par) -> void
{ cout<<"printc: par = "<<par<<endl;
  // par=0; // error, cannot modify a const object
}

auto main() -> void
{ auto a=123, b=123;
  print(a);
  printc(b);
  cout<<"a = "<<a<<endl; // 0
  cout<<"b = "<<b<<endl; // 123
  cin.get();
}

/*
print:  par = 123
printc: par = 123
a = 0
b = 123
*/