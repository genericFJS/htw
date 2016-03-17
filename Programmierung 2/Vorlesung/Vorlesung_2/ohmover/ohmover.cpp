#include <iostream>     // ohmover.cpp
using namespace std;

class ohm {
             double u,i;  // private: u[v], i[A]
      public:
             ohm();                      // default - Konstr.
			 ohm(double pu);             // Ueberlad. Konstr.
             ohm(double pu, double pi);  // Ueberlad. Konstr.
			 ~ohm(){cout<<"Instanz Typ ohm geloescht"<<endl;}
             auto get_r() -> double { return i?u/i:1.7E+308;} 
			 auto get_u() -> double { return u;}         
			 auto get_i() -> double { return i;}         
			 auto set_u(double pu=0.0) -> void {u=pu;}   
			 auto set_i(double pi=1.0) -> void {i=pi;}  
};

// Explizite Definition
ohm::ohm():u(0.0), i(1.0){};          
ohm::ohm(double pu):u(pu), i(1.0){};
ohm::ohm(double pu, double pi):u(pu), i(pi){};

void main(){
     ohm o1,          
		 o2(240.0),
		 o3(220.0, 10.0);

	 cout<<"o1.R = "<<o1.get_r()<<" o1.U = "<<o1.get_u()
		 <<" o1.I = "<<o1.get_i()<<'\n';
	 cout<<"o2.R = "<<o2.get_r()<<" o2.U = "<<o2.get_u()
		 <<" o2.I = "<<o2.get_i()<<'\n';
     cout<<"o3.R = "<<o3.get_r()<<" o3.U = "<<o3.get_u()
		 <<" o3.I = "<<o3.get_i()<<'\n';
	 cin.get();
}

/*
o1.R = 0 o1.U = 0 o1.I = 1
o2.R = 240 o2.U = 240 o2.I = 1
o3.R = 22 o3.U = 220 o3.I = 10

Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
*/