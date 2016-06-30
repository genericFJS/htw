#include <iostream>
using namespace std;

// abstrakte Schnittstelle:       abstractbase_late.cpp

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

void main(void){
     abstrakt *k1=new konkret1;
	 abstrakt *k2=new konkret2;
	 k1->f();                    // late binding
	 k2->f();                    // late binding
	 cin.get();
}

/*
Konstruktor abstract
Konstruktor abstract
f_imp() aus imp1
f_imp() aus imp2
*/