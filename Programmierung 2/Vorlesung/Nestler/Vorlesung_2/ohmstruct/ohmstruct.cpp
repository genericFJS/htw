#include <iostream>        // ohmstruct.cpp

using namespace std;

struct ohm {
      private:
         double u,i; // [v], [A] (private member)
      public:
		 //Defaultkonstruktor
         ohm(double pu=0.0, double pi=1.0); 
	     ~ohm(){ cout<<"Destruktor fuer Instanz vom Typ ohm"
			 <<endl;
	     }			// implizite Definition
         double get_r(){ return i?u/i:1.7E+308; }   //impl.
	     double get_u(){ return u; }           //impl.
	     double get_i(){ return i; }           //impl.
	     void set_u(double pu=0.0){u=pu; }     //impl.
	     void set_i(double i=1.0){this->i=i; } //impl.
};

// Explizite Definition (alternativ zu impliziter Def.)
ohm::ohm(double u, double i):u(u),i(i){         
	 cout<<"ohm instantiiert"<<endl; 
};

int global;		// globale Variable global

void main(){
	 std::cout<<"globales global="<<::global<<endl;

     int global=100;  // lokale Variable global
     cout<<"lokales global="<<global<<endl;

     struct ohm o1, o2(220.0, 10.0); // Instantiierung

     o1.ohm::ohm();  // redundant, explizit, kein Fehler
     o1.ohm::set_u(240.0);	// unuebliche Notation
     o1.set_i(20.0);		// uebliche Notation
     cout<<"o1.R = "<<o1.get_r()<<" o1.U = "<<o1.get_u()
         <<" o1.I = "<<o1.get_i()<<'\n';

     cout<<"o2.R = "<<o2.get_r()<<" o2.U = "<<o2.get_u()
	 <<" o2.I = "<<o2.get_i()<<'\n';

     o2 = o1;  // komponentenweise Zuweisung

     o1.ohm::~ohm(); // expl. Destruktoraufruf
     o1.~ohm();      // expl. Destruktoraufruf
     cin.get();
}					 // impl. Destruktoraufruf

/*
globales global=0
lokales global=100
ohm instantiiert
ohm instantiiert
ohm instantiiert
o1.R = 12 o1.U = 240 o1.I = 20
o2.R = 22 o2.U = 220 o2.I = 10
Destruktor fuer Instanz vom Typ ohm
Destruktor fuer Instanz vom Typ ohm

Destruktor fuer Instanz vom Typ ohm
Destruktor fuer Instanz vom Typ ohm
*/