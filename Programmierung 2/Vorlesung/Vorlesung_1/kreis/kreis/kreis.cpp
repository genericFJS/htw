#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

class kreis {           // auch struct moeglich
			double r;   // private - Member
  public:	static auto pi() -> double { return 4.0*atan(1.0); }

  public:
	kreis(double r=0.0):r(r){ // Konstruktor initialisert
	//	cout.setf(ios::fixed, ios::floatfield);
	//	cout.precision(8);
		cout<<"\nkreis mit r  = "
		    <<setw(14)<<this->r<<endl; 
	}
	
	~kreis(){ cout<<"\nDestruktor r = "  // Destruktor
		          <<setw(14)<<(*this).r<<endl<<endl; 
			  r = 0.0;
	}

	double get_r(){ return r; }
	void set_r(double r = 0.0){ this->r = r; }
	auto u() -> double { return  2*pi()*r; }
	double A(){ return pi()*r*r; }
	double V(){ return 4.0/3.0*r*r*r*pi(); }
	double O(){ return 4.0*r*r*pi(); }
};

void main(){
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(8);
	cout<<"\nPi           = "<<setw(14)
		<<kreis::pi()<<endl;
	kreis k1(10.0), 
		  k2(k1), 
		  * k3 = new kreis(10.0);
	auto r = 0.0;
	cout<<"\nRadius     r = "; cin>>r; 
	cin.clear(); cin.ignore(INT_MAX, '\n');
	k2.set_r(r);
	cout<<"Umfang       = "<<setw(14)<<k1.u()<<endl;
	cout<<"Flaeche      = "<<setw(14)<<k1.A()<<endl;
	cout<<"Volumen      = "<<setw(14)<<k1.V()<<endl;
	cout<<"Oberflaeche  = "<<setw(14)<<k1.O()<<endl;
	
	k1 = k2;             // Zuweisung
	k2.~kreis();         // Destruktor explizit rufen
	
	cout<<"Umfang k3    = "<<setw(14)<<k3->u()<<endl;
	cout<<"Flaeche k2   = "<<setw(14)<<k2.A()<<endl;
	cout<<"Volumen k3   = "<<setw(14)<<(*k3).V()<<endl;
	cout<<"Oberflaeche  = "<<setw(14)<<k3[0].O()<<endl;
	delete k3; k3 = 0;
	cin.get();
}

/*
Pi           =     3.14159265

kreis mit r  =    10.00000000

kreis mit r  =    10.00000000

Radius     r = 1
Umfang       =    62.83185307
Flaeche      =   314.15926536
Volumen      =  4188.79020479
Oberflaeche  =  1256.63706144

Destruktor r =     1.00000000

Umfang k3    =    62.83185307
Flaeche k2   =     0.00000000
Volumen k3   =  4188.79020479
Oberflaeche  =  1256.63706144

Destruktor r =    10.00000000

Destruktor kreis r =0
Destruktor kreis r =1
*/