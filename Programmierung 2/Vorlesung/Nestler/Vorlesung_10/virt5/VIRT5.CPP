#include <iostream>

using namespace std;

class musiker { public: virtual ~musiker();  // virtuell
			// ...
	      };

musiker::~musiker(){ cout<<"Musiker wird zerstoert\n"; }

class trompeter : public musiker { // virtuell, weil base-class
				   // Destruktor virtuell
				   public: virtual ~trompeter();
				 };

trompeter::~trompeter(){ cout<<"Trompeter wird zerstoert\n"; }

void main(){ trompeter *pt;
	musiker *pm;
	pt=new trompeter;
	delete pt;       //OK, beide Destruktoren im Aufruf
	pm=new trompeter;
	delete pm;       //OK, beide Destruktoren im Aufruf
	cin.get();
}
