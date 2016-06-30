#include <iostream>	  // inh4dyncast.cpp
using namespace std;  // Ersatz fuer virtual mittels Nutzung des
                      // dynamic_cast<derived *>(pb)
class base{ public:  
             base(int i=0);
		     ~base();
		     void print();        
             void give();        
		     int geta(){ return a; }
			 virtual void dummy(){}; //notw. wegen dynamic_cast
	private: int a;
	  };

class derived : public base {
		public:  
		     derived(int i=0);
			 ~derived();
			 void print(); // override
			 void give();  // override
	      };

base::base(int i):a(i){ cout<<"Konstruktor base\n"; };

base::~base(){ cout<<"Destruktor base\n"; }

void base::print(){ cout<<"base print a = "<<a<<endl; }

void base::give(){  cout<<"base give  a = "<<a<<endl; }

derived::derived(int i):base(i){cout<<"Konstruktor derived\n"; }

derived::~derived(){ cout<<"Destruktor derived\n"; }

void derived::print(){ cout<<"derived print a = "<<geta()<<endl; }
void derived::give(){  cout<<"derived give  a = "<<geta()<<endl; }

void main(){ 
	     base b1(1), *pb=&b1;
	     
	     pb->print();   // base print(), Zeiger auf base-Objekt, 1

		 //Ersatz fuer late binding: Testen des dynamic_cast<derived *>(pb)
		 dynamic_cast<derived *>(pb)?(dynamic_cast<derived *>(pb))->give():
			                         (dynamic_cast<base *>(pb))->give();  
		 derived d1(2);
	     pb=&d1;
	     pb->print();   // base print(), Zeiger auf derived-Objekt, 2
	 
		 //Ersatz fuer late binding: Testen des dynamic_cast<derived *>(pb)
		 if(dynamic_cast<derived *>(pb))
			  ((derived *)pb)->give();
		 else pb->give();
}