#include <iostream>	  // inh4dyncast.cpp
using namespace std;  // Ersatz fuer virtual mittels Nutzung des
                      // dynamic_cast<derived *>(pb)
class base{  int a;
		public:  
			 base(int i=0):a(i){}
             void give(){ cout<<"base give a = "<<a<<endl; }  
			 virtual void _(){}  // dummy-Methode wegen dynamic_cast
};

class derived : public base {
			 double a;
		public:  
		     derived(int i=0, double j=0.0):base(i),a(j){}
			 void give(){ cout<<"derived give a = "<<a<<endl; };  // override
};

void main(){ 
	     base b1(1), *pb=&b1;
	     
		 //Ersatz fuer late binding: Testen des dynamic_cast<derived *>(pb)
		 dynamic_cast<derived *>(pb)?(dynamic_cast<derived *>(pb))->give():
			                         (dynamic_cast<base *>(pb))->give();  
		 derived d1(2, 4.0);
	     pb=&d1;
	 
		 //Ersatz fuer late binding: Testen des dynamic_cast<derived *>(pb)
		 if(dynamic_cast<derived *>(pb))
			  ((derived *)pb)->give();
		 else pb->give();

		 cin.get();
}
/*
base give a = 1
derived give a = 4
*/