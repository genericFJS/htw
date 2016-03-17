#include <iostream>        // cla6.cpp

using namespace std;

class count {
	  static unsigned zahl;
  public: 
	  count(){ ++zahl; 
			   cout<<"zahl="<<zahl<<endl; 
	  }

	      
	  ~count(){ --zahl; 
				cout<<"zahl="<<zahl<<endl; 
	  }
	      
	  unsigned anz(){ return zahl;}
};

unsigned count::zahl = 0U; // Definit. und Initial. 

void main(){ 
	     class count a, b, *c=new class count, *d(new class count);

	     cout<<"Wert von anz()="<<a.anz()<<endl;
	     delete c;
	     delete d;
	     cout<<"Wert von anz()="<<a.anz()<<endl;
		 cin.get();
	   }
/*
zahl=1
zahl=2
zahl=3
zahl=4
Wert von anz()=4
zahl=3
zahl=2
Wert von anz()=2
zahl=1
zahl=0
*/
