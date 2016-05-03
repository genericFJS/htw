#include <iostream>    // inh0.cpp
using namespace std;

class b { long l;
        public:
	      long p;
		  b(long l=0, long p=0):l(l), p(p){};
		  ~b(){};
		  long get_l() const { return l; }
};

class d : public b { 
        public:
	      d(long l=0, long p=0):b(l,p){};

	   // Fehler, l,p keine Member von class d:
	   // d(long l=0, long p=0):l(l),p(p){}; 

		  ~d(){};

	   // long get_l(){ return l; } // Fehler, weil private

	   // long get_l(){             // nicht erforderlich
	   //	       return b::get_l(); 
	   // } 

		  void display() const { cout<<"   p = "<<p
									 <<"      l = "
									 <<get_l()<<'\n';
		  }
};

void main(){
	d d0(5,7);
	d0.display();
	cout<<"d0.p = "<<d0.b::p<<",  d0.l = "<<d0.b::get_l()<<endl;
    cout<<"d0.p = "<<d0.p<<",  d0.l = "<<d0.get_l()<<endl;
	cin.get();
}