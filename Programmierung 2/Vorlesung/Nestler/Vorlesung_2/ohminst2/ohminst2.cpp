#include <iostream>        // ohminst2.cpp

using namespace std;

auto main() -> void {
	 
     class {		 // ohne Namen
         double u,i; // [v], [A] (private member)
	 public:
         auto get_r() -> double { return i?u/i:1.7E+308; }   //impl.
	     auto get_u() -> double { return u; }           //impl.
	     auto get_i() -> double { return i; }           //impl.
	     auto set_u(double pu=0.0) -> void {u=pu; }     //impl.
	     auto set_i(double i=1.0) -> void {this->i=i; } //impl.
	 } o1, o2; // Instantiierung

     o2.set_u(220.0);	    
     o2.set_i(10.0);

	 //o1.u und o1.i wurden nicht initialisiert !
     cout<<"o1.R = "<<o1.get_r()<<" o1.U = "<<o1.get_u()
         <<" o1.I = "<<o1.get_i()<<'\n';

     cout<<"o2.R = "<<o2.get_r()<<" o2.U = "<<o2.get_u()
	 <<" o2.I = "<<o2.get_i()<<'\n';

     o2 = o1;  // komponentenweise Zuweisung

     cin.get();
}					 // impl. Destruktoraufruf

/*
o1.R = 50123.8 o1.U = 3.07406e-313 o1.I = 6.13294e-318 (nicht initialisiert !)
o2.R = 22 o2.U = 220 o2.I = 10
*/