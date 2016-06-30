#include <iostream>  // virt8.cpp

using namespace std;

class A { 
	public: 
		virtual void f(){ 
		  cout<<"f from A"<<endl; 
		} 
};

class A1 : virtual public A { 
	public:
		virtual void f(){
		  cout<<"f from A1"<<endl; 
		}
};

class A2 : virtual public A {};

//Warnung C4250: 'A12': Erbt 'A1::A1::f' via Dominanz :
class A12 : public A1, public A2 {}; 


void main(){
	A12 a12;
	A2  *pa2=&a12;
	A2 a2;
	a2.f();         // f from A  (fruehe Bindung)
	pa2->f();	    // f from A1 (spaete Bindung)
	A1 *pa1=&a12;
	pa1->f();       // f from A1 (spaete Bindung)
	(&a12)->f();    // f from A1 (spaete Bindung)
	a12.A::f();     // f from A  (fruehe Bindung)
	a12.f();        // f from A1 (fruehe Bindung)
	cin.get();
}
