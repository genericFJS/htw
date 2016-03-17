#include <iostream>        // ohmvek.cpp

using namespace std;

class ohm {
             double u,i; // [v], [A]
      public:
         ohm(double pu=0.0, double pi=1.0):u(pu),i(pi){
			cout<<"Konstruktor ohm, u = "<<u<<"  i = "<<i<<endl;
		 }
	     ~ohm(){cout<<"Instanz Typ ohm geloescht"<<endl;}
         double get_r(){ return i?u/i:0.0;} //inline
	     double get_u(){ return u;}         //inline
	     double get_i(){ return i;}         //inline
	     void set_u(double pu=0.0){u=pu;}   //inline
	     void set_i(double pi=1.0){i=pi;}   //inline
};

auto main() -> void {
	 size_t n=20;
     auto *o1=new ohm[n]; //n=20 Objekte, Standardkonstruktor
	 for(size_t j=0;j<n;j++){
        o1[j].set_u(240.0+double(j));
        o1[j].set_i(20.0+double(j));
	    cout<<"o1["<<j<<"].R = "<<o1[j].get_r()
		 <<" o1["<<j<<"].U = "<<o1[j].get_u()
		 <<" o1["<<j<<"].I = "<<o1[j].get_i()<<'\n';
	 };
	 delete [] o1; o1=nullptr; delete [] o1; // OK
	 cin.get();
}

/*
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
Konstruktor ohm, u = 0  i = 1
o1[0].R = 12 o1[0].U = 240 o1[0].I = 20
o1[1].R = 11.4762 o1[1].U = 241 o1[1].I = 21
o1[2].R = 11 o1[2].U = 242 o1[2].I = 22
o1[3].R = 10.5652 o1[3].U = 243 o1[3].I = 23
o1[4].R = 10.1667 o1[4].U = 244 o1[4].I = 24
o1[5].R = 9.8 o1[5].U = 245 o1[5].I = 25
o1[6].R = 9.46154 o1[6].U = 246 o1[6].I = 26
o1[7].R = 9.14815 o1[7].U = 247 o1[7].I = 27
o1[8].R = 8.85714 o1[8].U = 248 o1[8].I = 28
o1[9].R = 8.58621 o1[9].U = 249 o1[9].I = 29
o1[10].R = 8.33333 o1[10].U = 250 o1[10].I = 30
o1[11].R = 8.09677 o1[11].U = 251 o1[11].I = 31
o1[12].R = 7.875 o1[12].U = 252 o1[12].I = 32
o1[13].R = 7.66667 o1[13].U = 253 o1[13].I = 33
o1[14].R = 7.47059 o1[14].U = 254 o1[14].I = 34
o1[15].R = 7.28571 o1[15].U = 255 o1[15].I = 35
o1[16].R = 7.11111 o1[16].U = 256 o1[16].I = 36
o1[17].R = 6.94595 o1[17].U = 257 o1[17].I = 37
o1[18].R = 6.78947 o1[18].U = 258 o1[18].I = 38
o1[19].R = 6.64103 o1[19].U = 259 o1[19].I = 39
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
Instanz Typ ohm geloescht
*/