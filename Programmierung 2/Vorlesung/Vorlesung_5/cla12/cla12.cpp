#include <iostream>               // CLA12.CPP
using namespace std;

class s {   
		   static unsigned long y;
  public:  
	       s(unsigned long z=0UL){ 
               y=z; cout<<"Konstruktor von s\n"; 
		   }

		   ~s(){ cout<<"Destruktor von s\n"; }

	       static void summe(unsigned long x=0UL){ y+=x; }

	       static unsigned long give(){ return y; }
};

unsigned long s::y=10; //Definition, obwohl s::y private

s a(100);   // Objekt a vom Typ s , s::y ueberschreiben
s b(200);   // Objekt b vom Typ s , s::y ueberschreiben
	        // a und b sind zwei unterschiedliche Zeiger-
	        // variablen, die auf denselben Speicherplatz
	        // zeigen, d.h. auf Klasse s
void main(){
  cout<<"main() beginnt\n";
  cout<<"&a="<<&a<<"   &b="<<&b<<endl;
  cout<<"s::y="<<s::give()<<endl;  // vor erstem Objekt
  a.s::summe(5);                   // besser: s::summe(5)
  s::summe(10);                    // wie:    a.s::summe(10)
  cout<<"s::y="<<a.give()<<endl;   // besser: s::give()
  cout<<"main() beendet"<<endl;
  cin.get();
}

/*
Konstruktor von s
Konstruktor von s
main() beginnt
&a=0041B181   &b=0041B180
s::y=200
s::y=215
main() beendet

Destruktor von s
Destruktor von s
Press any key to continue
*/