// zeigop.cpp    hier wird der Operator -> ueberladen
#include <iostream>   
using namespace std;

class A {  char* str;
	public:
		   A(char *s):str(s){}
		   int lng(){ return str?(int)strlen(str):0;}
};

class X {  A& a;
	public:
		   X(A& pa):a(pa){}
		   A* operator->(){ cout<<"Aufruf operator->()\n" ;
		                    return &a; // Adresse von a
		   }
};

void main(){
     A a("HTW");
     X x(a);

     int l=x->lng(); // class X hat kein lng() , 
		             // class X erhaelt mit operator->() 
	                 // Zugriff auf alle Methoden von class A
	
//   int l=(x.operator->())->lng();  // int l=x->lng();

//   int l=(&x.a)->lng();        // Fehler, wegen private a

     cout<<"l = "<<l<<endl;  // l=3
     cin.get();
}

/*
Aufruf operator->()
l = 3
*/
