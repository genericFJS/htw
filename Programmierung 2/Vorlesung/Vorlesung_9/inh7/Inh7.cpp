#include <iostream>
using namespace std;

// inh7.cpp
class base { public:    void pubB();
	         protected: void protB();
	         private:   void privB();
	   };

// protected - Ableitung:
class derived:protected base { public:  void pubD();
			                   private: void privD();
			   };

void derived::pubD(){ cout<<"derived pubD()"<<endl;
	                  privD(); //OK
		              pubB();  //OK
		              protB(); //OK
		    //  privB(); //Error, Zugriff auf private Komponente
		    }

void derived::privD(){ cout<<"derived privD()"<<endl; }

void base::pubB(){  cout<<"base pubB()"<<endl;  }

void base::protB(){ cout<<"base protB()"<<endl; }

void base::privB(){ cout<<"base privB()"<<endl; }

void main(){ derived d1;
	    d1.pubD();  //OK
	//  d1.pubB();  //Error
	//  d1.protB()  //Error
	    base b1;
	    b1.pubB();  //OK
	//  b1.protB(); //Error
	// ...
}

/*
derived pubD()
derived privD()
base pubB()
base protB()
base pubB()
*/