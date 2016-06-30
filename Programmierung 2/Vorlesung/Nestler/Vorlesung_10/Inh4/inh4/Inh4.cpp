#include <iostream>

using namespace std;

class base{ int a;
   public:  base(int i=0):a(i){}
		   
			virtual void give(){ cout<<"base give a = "<<a<<endl; } // spaete Bindung
};

class derived : public base {
			 double a;
	public:  derived(int i=0, double j=0.0):base(int(i)), a(j){};
			
			 virtual void give(){  cout<<"derived give  a = "<<a<<endl; }; // spaete Bindung			
};

void main(){ base b1(1), *pb=&b1;
			 pb->give();    // base give(), Zeiger auf base-Objekt

			 derived d1(2, 4.0); pb=&d1;
			 pb->give();    // derived give(), Zeiger auf derived-Objekt

			 cin.get();
}
/*
base give  a = 1
derived give  a = 4.0
*/
