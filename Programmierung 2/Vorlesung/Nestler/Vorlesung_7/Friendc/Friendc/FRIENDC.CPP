#include <iostream> // friendc.cpp, Methode einer anderen Klasse als friend

using namespace std;

class y;

class x { public:
			int f(y &);
			int f(){ return priv; }
			x(int i=0):priv(i){ 
			            cout<<"Konstruktor x"<<endl; }
			~x(){ cout<<"Destruktor x"<<endl; }
		  private:
			int priv;
	};

class y { 
	  friend int x::f(y& z); // Memberfkt. als friend
	  public:  
		  y(int i=0):priv(i){ 
		               cout<<"Konstruktor y"<<endl;};
		  ~y(){ cout<<"Destruktor y"<<endl; };
	  private:
		   int priv;
};

void main(){ 
		 x a(10);
	     y b(20);
	     cout<<"a.priv = "<<a.f()<<endl;
	     cout<<"b.priv = "<<a.f(b)<<endl;
		 cin.get();
};

int x::f(y& z){ return z.priv; } // Private Daten Klasse y

/*
Konstruktor x
Konstruktor y
a.priv = 10
b.priv = 20

Destruktor y
Destruktor x
*/
