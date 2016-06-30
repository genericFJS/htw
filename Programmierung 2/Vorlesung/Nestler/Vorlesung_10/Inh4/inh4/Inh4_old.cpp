#include <iostream>

using namespace std;

class base{ public:  base(int i=0);
		     ~base();
		     void print();        // fruehe Bindung
			 virtual void give(); // spaete Bindung
		     int geta(){ return a; }
	     private: int a;
	  };

class derived : public base {
		public:  
		     derived(double i=0.0);
			 ~derived();
			 void print(); //Ueberschreiben
			 void give(); // spaete Bindung
			 double a;
	      };

base::base(int i):a(i){ cout<<"Konstruktor base\n"; };

base::~base(){ cout<<"Destruktor base\n"; }

void base::print(){ cout<<"base print a = "<<a<<endl; }
void base::give(){  cout<<"base give  a = "<<a<<endl; }

derived::derived(double i):base(int(i)){cout<<"Konstruktor derived\n"; }

derived::~derived(){ cout<<"Destruktor derived\n"; }

//void derived::print(){ cout<<"derived print a = "<<geta()<<endl; }
void derived::print(){ cout<<"derived print a = "<<a<<endl; }
void derived::give(){  cout<<"derived give  a = "<<geta()<<endl; }

void main(){ base b1(1), *pb=&b1;
	     derived d1(2);
	     pb->print();   // base print(), Zeiger auf base-Objekt, 1
		 pb->give();    // base give(), Zeiger auf base-Objekt,  1
	     pb=&d1;
	     pb->print();   // base print(), Zeiger auf derived-Objekt, 2
		 pb->give();    // derived give(), Zeiger auf derived-Objekt, 2
	   }
/*
Konstruktor base
Konstruktor base
Konstruktor derived
base print a = 1
base give  a = 1
base print a = 2
derived give  a = 2
Destruktor derived
Destruktor base
Destruktor base
Press any key to continue
*/
