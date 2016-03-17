#include <iostream>        // ohminst.cpp

using namespace std;

auto main() -> void {
	 
     class ohm{
         double u,i; // [v], [A] (private member)
      public:
		 //Defaultkonstruktor
         ohm(double pu=0.0, double pi=1.0):u(u),i(i){         
					cout<<"ohm instantiiert"<<endl; 
		 }; 
	     ~ohm(){ cout<<"Destruktor fuer Instanz vom Typ ohm"
			 <<endl;
	     }			// implizite Definition
         auto get_r() -> double { return i?u/i:1.7E+308; }   //impl.
	     auto get_u() -> double { return u; }           //impl.
	     auto get_i() -> double { return i; }           //impl.
	     auto set_u(double pu=0.0) -> void {u=pu; }     //impl.
	     auto set_i(double i=1.0) -> void {this->i=i; } //impl.
	 } o1, o2(220.0, 10.0); // Instantiierung

     o1.set_u(240.0);	    
     o1.set_i(20.0);		
     cout<<"o1.R = "<<o1.get_r()<<" o1.U = "<<o1.get_u()
         <<" o1.I = "<<o1.get_i()<<'\n';

     cout<<"o2.R = "<<o2.get_r()<<" o2.U = "<<o2.get_u()
	 <<" o2.I = "<<o2.get_i()<<'\n';

     o2 = o1;  // komponentenweise Zuweisung

     o1.~ohm();      // expl. Destruktoraufruf
     cin.get();
}					 // impl. Destruktoraufruf

/*
ohm instantiiert
ohm instantiiert
o1.R = 12 o1.U = 240 o1.I = 20
o2.R = 0 o2.U = 0 o2.I = 0
Destruktor fuer Instanz vom Typ ohm

Destruktor fuer Instanz vom Typ ohm
Destruktor fuer Instanz vom Typ ohm
*/