#include <iostream>
using namespace std;

class A { public: virtual void f(void){ cout<<"f A"<<endl; }};

class B { public: void f(void){ cout<<"f B"<<endl; }};

// Redefinition von f() aus class A mittels f() aus class B

class AA : public A, public B { void f(void){ B::f(); }};

void main(){
	AA x;	
//	x.f();  //Compile-Error: private-Zugriff, wegen frueher Bindung
	AA aa;
	A &a=aa; //OK 
	a.f();   //Aufruf redefinierter Fkt. f(), late binding
	B &b=aa; //OK, 
	b.f();   //Aufruf von B::f(), early binding, weil virtual fehlt
//	((AA &)b).f(); //Compile-Error: kein Zugriff auf private
	cin.get();
}
/*
f B
f B
*/
