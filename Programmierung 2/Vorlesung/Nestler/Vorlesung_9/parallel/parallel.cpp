#include <iostream>    // parallel.cpp

using namespace std;

class X { public: int wert;
                  X(int i=0):wert(i){}; 
};

class Y { public: int wert;
                  Y(int i=0):wert(i){};
};

class Z: public Y { public: Z(int i=0):Y(i){};
};

class A: public X, public Z { public: A(int i=0):X(i),Z(i){};
};

void main(){

   A a(1);

// cout<<"a.wert="<<a.wert<<endl;       // Error: 'A::wert' ist mehrdeutig
// cout<<"a.A::wert="<<a.A::wert<<endl; // Error: 'A::wert' ist mehrdeutig

   cout<<"a.X::wert="<<a.X::wert<<endl;

   cout<<"a.Y::wert="<<a.Y::wert<<endl;

   cout<<"a.Z::wert="<<a.Z::wert<<endl;

   cin.get();
}