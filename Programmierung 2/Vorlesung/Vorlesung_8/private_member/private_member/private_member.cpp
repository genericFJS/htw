#include <iostream>

using namespace std;

// Alle Methoden einer Klasse haben uneingeschraenkten
// Zugriff auf alle privaten Member bzw. Methoden derselben
// Klasse
// D.h. alle Methoden eines Objektes einer Klasse koennen
// auch auf die privaten Member bzw. Methoden anderer
// Objekte der gleichen Klasse uneingeschraenkt zugreifen.
//
class A { int i;
	public:
		A(int i=0):i(i){}
		int get_i(const A &ra){ return ra.i;}
		void set_i(A &ra, int i=0){ ra.i = i; }
};

void main(){
	A a(5), b(7);
	cout<<"b.i = "<<a.get_i(b)<<endl;
	a.set_i(b, 17);
	cout<<"b.i = "<<a.get_i(b)<<endl;
	cin.get();
}

/*
b.i = 7
b.i = 17
*/