#include <iostream>    // inh0p.cpp
using namespace std;

class b { long l;
        protected: 
	      long r;
        public:
	      long p;
		  b(long l=0, long p=0, long r=0):l(l), p(p), r(r){};
		  ~b(){};
		  long get_l() const { return l; }
};

class d : public b { 
	      long p;
        public:
		  d(long l=0, long p=0, long r=0, long pd=0):b(l,p,r), 
			                                         p(pd){};
		  ~d(){};

		  void display() const { 
			              cout<<"    l = "<<get_l()<<'\n';
		                  cout<<" b::p = "<<b::p<<'\n';
						  cout<<"    r = "<<r<<'\n';
						  cout<<"    p = "<<p<<'\n';
		  }
};

void main(){
	d d0(3,5,7,9);
	d0.display();
//	cout<<"b.r = "<<d0.r<<endl;  // Fehler, weil protected !
	cin.get();
}