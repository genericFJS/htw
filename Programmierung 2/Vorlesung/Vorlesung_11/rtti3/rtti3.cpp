// rtti3.cpp,   compile with: /GR /EHsc
#include <iostream>
#include <typeinfo.h>

class Base {
public:
   virtual void vvfunc() {}
};

class Derived : public Base {};

using namespace std;
int main()
{
   Derived* pd = new Derived;
   Base* pb = pd;
   cout << typeid( pb ).name() << endl;    // prints "class Base *"
   cout << typeid( *pb ).name() << endl;   // prints "class Derived"
   cout << typeid( pd ).name() << endl;    // prints "class Derived *"
   cout << typeid( *pd ).name() << endl;   // prints "class Derived"
   delete pd; pd = 0;
   cin.get();
}
