#include <iostream>        // ohmref.cpp

using namespace std;

class ohm {
         double u,i; // [v], [A], private
  public:
         ohm(double pu=0.0, double pi=1.0):u(pu),i(pi){};

//     Kopierkonstruktor, waere hier nicht explizit notwendig:
	 ohm(ohm &o):u(o.u),i(o.i){
				cout<<"Kopierkonstruktor\n";
	 } 
	 ~ohm(){cout<<"Instanz Typ ohm geloescht"<<endl;}
	 
     double get_r(){ return i?u/i:1.7E+308; } 
	 double get_u(){ return u;}         
	 double get_i(){ return i;}         
	 void set_u(double pu=0.0){u=pu;}   
	 void set_i(double pi=1.0){i=pi;} 
	  
	 ohm &kopieren(ohm &o){      //ohne & ???
	 //	this->u=o.u;  this->i=o.i; 
		*this=o;
		return *this;
	 }
};

void main(){
     ohm &o1=*new ohm(220.0,5.0),o2=o1;   //Init. Referenz
//                            ohm o2(o1); //Aequivalent
     (o1).set_u(240.0);
     o1.set_i(20.0);
     
     cout<<"o1.R = "<<o1.get_r()<<" o1.U = "<<o1.get_u()
	 <<" o1.I = "<<o1.get_i()<<'\n';

     ohm *o3 = new ohm; o3->kopieren(o2.kopieren(o1));
     
     cout<<"o3.R = "<<o3->get_r()<<" o3.U = "<<o3->get_u()
		 <<" o3.I = "<<o3->get_i()<<'\n';
		 
     delete &o1; delete o3;
     cin.get();
}
/*
Kopierkonstruktor
o1.R = 12 o1.U = 240 o1.I = 20
o3.R = 12 o3.U = 240 o3.I = 20
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
*/