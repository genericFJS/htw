#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

class demo
{
  char Name[30+1];
  public:
  demo(const char*str)
   {strncpy(Name,str,30);cout<<"Constructor "<<Name<<endl;}
 ~demo(){cout<<"Destructor  "<<Name<<endl;}
};

void func()
{
  demo localObject("localObject");
  static demo staticObject("staticObject");
  cout<< "end of func"<<endl;
}

demo globalObject("globalObject");

int main()
{
  demo localMainObject("localMainObject");
  cout<<"in main 1"<<endl;
  func();
  cout<<"in main 2"<<endl;
  func();
  cout<< "end of main"<< endl;
  return 0;
}