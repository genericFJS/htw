#include <iostream>        // ohmnew.cpp
#include <iomanip>
using namespace std;

class ohm {
             double u,i; // [v], [A]
      public:
             ohm(double pu=0.0, double pi=1.0);
			~ohm(){cout<<"Instanz Typ ohm geloescht"<<endl;}
             double get_r(){ return i?u/i:0.0;}
			 double get_u(){ return u;}        
			 double get_i(){ return i;}        
			 void set_u(double pu=0.0){u=pu;} 
			 void set_i(double pi=1.0){i=pi;} 
};

// Explizite Definition
ohm::ohm(double pu, double pi):u(pu),i(pi){
	cout<<"Konstruktor ohm, u = "<<fixed<<setw(10)<<setprecision(2)<<this->u
		<<"  i = "<<fixed<<setw(10)<<setprecision(2)<<this->i<<endl;
}

auto main() -> void {
     auto *o1=new ohm, *o2=new ohm(220.0, 10.0);
     (*o1).set_u(240.0);
     o1[0].set_u(230.0);
     o1->set_i(20.0);
     cout<<"o1.R = "<<o1->get_r()<<" o1.U = "<<o1->get_u()
	 <<" o1.I = "<<o1->get_i()<<'\n';
     cout<<"o2.R = "<<o2->get_r()<<" o2.U = "<<o2->get_u()
	 <<" o2.I = "<<o2->get_i()<<'\n';
     *o2=*o1;  //Zuweisung erfolgt komponentenweise
     delete o1; o1 = nullptr; delete o2; o2 = nullptr;	// delete o1, o2; falsch !!
//	 cout<<"*o2="<<o2->get_u()<<endl; // hier falsche Ergebnisse !!
     cin.get();
}
/*
Konstruktor ohm, u =       0.00  i =       1.00
Konstruktor ohm, u =     220.00  i =      10.00
o1.R = 11.50 o1.U = 230.00 o1.I = 20.00
o2.R = 22.00 o2.U = 220.00 o2.I = 10.00
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
*/