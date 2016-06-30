#include <iostream>		// virt12.cpp
using namespace std;

// probeweise /* virtual */ setzen:
class A { public: virtual void aus() const { 
				cout<<"A"<<endl; 
		  }
		  		  
		  A(){ aus(); }
};

class B: public A { public: void aus() const { 																
				cout<<"B"<<endl; 
			    }
			    
			    void test() const { 
				     aus(); 
			    }
			    
			    B(){ aus(); }
};

class C: public B { public: void aus() const {
				cout<<"C"<<endl;
			    }
};

void main(){
	B *bp = new C;                                                                                                                             // A  B
	bp->test();                                                                                                                                // C
	delete bp;
	/*C c;
	B b(c);
	b.test();*/
	cin.ignore();
}










/*
   A
   B
   C
*/
