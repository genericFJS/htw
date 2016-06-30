#include <iostream>
using namespace std;

class base{     
  friend  void outf();
  public:     void pubB(){ cout<<"pubB() called"<<endl; }
  private:    void privB(){ cout<<"privB() called"<<endl; }
  protected: 	void protB(){ cout<<"protB() called"<<endl; }
};

class derived : public base { 
 public: void pubD(){ 
	       privD();
	       pubB();
	       protB();
	    // privB(); // Error, Zugriff auf private-Komponente
         }
 private: void privD(){ cout<<"privD() called"<<endl; }
};

void outs(){ 
 // base b;
	derived d;
 // b.protB();    // Error, Zugriff auf protected-Komponente von außen
	d.pubB();
	d.pubD();
 // d.protB();   // s.o.
}

void outf(){ 
	 base b;
	 derived d;
	 d.protB();
	 b.privB();
	 d.pubB();
	 d.pubD();
  // d.privD(); // Error, Freundschaft wird nicht vererbt !
}

void main(){ cout<<"output of outs():"<<endl;
	         outs();
		     cout<<"\noutput of outf():"<<endl;
	         outf();
}
