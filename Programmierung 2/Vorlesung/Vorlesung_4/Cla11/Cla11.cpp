#include <iostream>    // cla11.cpp
using namespace std;

class X {    mutable int m;  
     public: 
		     X(int m=0):m(m){};
			 ~X(){};

			 int read_m() const {
				 return m; 
			 }
	         void write_m(int i) const { 
				 m = i; //OK, weil mutable
			 }
};

void f(X &, const X &);

void f(X &mutant, const X &constant){
	        mutant.write_m(7);    // OK

			cout<<"mutant.m = "
				<<mutant.read_m() // OK
				<<endl;
			
// OK, weil class X { mutable int m; ...}:
			constant.write_m(8); 

			cout<<"constant.m = "
				<<constant.read_m()  // OK
				<<endl;
}

void main(){ 
	     X a, b;
	     f(a, b); 
		 cin.get();
};

/*  mutant.m = 7
  constant.m = 8
*/

