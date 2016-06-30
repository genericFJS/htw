#include <iostream>

using namespace std;

// abstrakte Schnittstelle

class abstrakt { 
	public: abstrakt(){cout<<"Konstruktor abstract"<<endl;}
		virtual void f()=0; };

// Implementation 1
class imp1 { public: void f_imp(){
	                      cout<<"f_imp() aus imp1"<<endl;}
};

// Implementation 2
class imp2 { public: void f_imp(){
	                      cout<<"f_imp() aus imp2"<<endl;}
};

// Konkrete Klasse, Version 1
class konkret1 : public abstrakt, private imp1 {
	public:
		void f(){ f_imp(); }; // Redefintion virt. Fkt.
};

// Konkrete Klasse, Version 2
class konkret2 : public abstrakt, private imp2 {
	public:
		void f(){ f_imp(); };
};

void main(){
     konkret1 k1;
	 konkret2 k2;
	 k1.f();       // early binding
	 k2.f();       // early binding  
	 cin.get();
}

/*
Konstruktor abstract
Konstruktor abstract
f_imp() aus imp1
f_imp() aus imp2
*/