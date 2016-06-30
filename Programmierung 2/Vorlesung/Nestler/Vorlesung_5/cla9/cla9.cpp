#include <iostream>    // cla9.cpp
using namespace std;

class s { static unsigned long y;
  public:  
	    s(unsigned long z=0UL){ y=z;
			cout<<"Konstruktor von s\n";
		}

		~s(){ cout<<"Destruktor von s\n"; }

	    static void summe(unsigned long x=0UL){ y+=x; }

	    static unsigned long give(void){ return y; }
};

unsigned long s::y=10; //Definition, obwohl s::y private

class t { unsigned long y; // ohne static 
  public:  
		   t(unsigned long z=0UL):y(z){             
				   cout<<"Konstruktor Klasse t\n";
		   }

	       ~t(){ cout<<"Destruktor Klasse t\n"; }

	       void summe(unsigned long x=0UL){ y+=x; }

	       unsigned long give(void){ return y; }
};

s a(100);   // Objekt vom Typ s , s::y ueberschreiben

void main()
{ cout<<"main() beginnt\n";
  cout<<"s::y="<<s::give()<<endl; // vor erstem Objekt
  a.s::summe(5);                  // besser: s::summe(5)
  s::summe(10);                   // wie:    a.s::summe(10)
  cout<<"s::y="<<a.give()<<endl;  // besser: s::give()
  t b(20);                        // Objekt b vom Typ t
  b.summe(25);                    // Aufruf Memberfkt. von b
  cout<<"b.y="<<b.give()<<endl;   // Aufruf Memberfkt. von b
  cout<<"main() beendet"<<endl;
  cin.get();
}

/*
Konstruktor von s
main() beginnt
s::y=100
s::y=115
Konstruktor Klasse t
b.y=45
main() beendet
Destruktor Klasse t
Destruktor von s
*/