#include <iostream>     // enth1.cpp

using namespace std;

class X { 
		int i;
	public:
		X(int n):i(n){ // Konstruktor
				  cout<<"Konstruktor X, i = "<<i<<endl;
		}
		~X(){ cout<<"Destruktor X, i = "<<i<<endl; }
		void display(){ cout<<"class X, i = "<<i<<endl; }
		// ...
};
	
class C {	X a;              // Komposition
			X* p;             // Aggregation
			X& r;             // Aggregation
			char *s;
public:
	C(int i, int j, int k, char *s):a(i), p(new X(j)), r(*new X(k)),
		s(s?strcpy(new char[strlen(s)+1],s):0){
		cout<<"Konstruktor C"<<endl;
		show();
	}

	C(X x, X * xp, X & xr, char s[]):a(x), p(new X(*xp)), r(*new X(xr)),
		s(s?strcpy(new char[strlen(s)+1],s):0){
		cout<<"Konstruktor C"<<endl;
		show();
	}

	~C(){ cout<<"Destruktor C"<<endl;
		  show();
		  delete p; p=0; delete &r; delete [] s; s=0;
	}

	void show(){ cout<<"class C,  show\n";
		         cout<<(s?s:"0")<<endl;
		//		 cout<<a.i<<endl;    // kein Zugriff !
		         a.display();
				 p->display();
				 r.display();
	}
	// ...
};

void main(){
  //	    C *c=new C(1,2,3,0);    // auch moeglich !!
            C *c=new C(1,2,3,"HTW Dresden");
			c->show();
			delete c; c = 0;

			X x = 1;			// X x(1);
			X *xp = new X(2);
			X &xr = *new X(3);
			C c1(x,xp,xr,"Versuch 2");
			c1.show();
			delete xp; xp = 0;
			delete &xr; //&xr = 0;
			cin.get();
}

